/*
 * Copyright (C) 2015 Hauke Oldsen
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <FreeImage.h>

#include "include-core.h"
#include "include-openvg.h"
#include "image-util.h"
#include "log-util.h"

void image_cleanup(image_t *image)
{
  vgDestroyImage(image->image);
  free(image);
}

FIBITMAP *image_load_bitmap(const char *path)
{
  printf("Loading image %s\n", path);
  
  FIBITMAP *bitmap = FreeImage_Load(FreeImage_GetFileType(path, 0), path, 0);
  if(!bitmap)
  {
    eprintf("Failed to load bitmap.\n");
    return NULL;
  }
  
  //FreeImage_FlipVertical(bitmap);
  printf("w=%i h=%i\n", FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap));
  
  
  if(FreeImage_GetBPP(bitmap) != 32)
  {
    FIBITMAP *old = bitmap;
    bitmap = FreeImage_ConvertTo32Bits(bitmap);
    FreeImage_Unload(old);
  }
  
  return bitmap;
}

image_t *image_create(FIBITMAP *bitmap)
{
  image_t *image = malloc(sizeof(image_t));
  image->width = FreeImage_GetWidth(bitmap);
  image->height = FreeImage_GetHeight(bitmap);
  image->image = vgCreateImage(VG_sARGB_8888, image->width, image->height, VG_IMAGE_QUALITY_NONANTIALIASED);
  vgImageSubData(image->image, FreeImage_GetBits(bitmap), image->width * 4, VG_sARGB_8888, 0, 0, image->width, image->height);
  
  return image;
  
}

void image_free_bitmap(FIBITMAP *bitmap)
{
  FreeImage_Unload(bitmap);
}

image_t *image_load(const char *path)
{
  FIBITMAP *bitmap = image_load_bitmap(path);
  image_t *img = image_create(bitmap);
  image_free_bitmap(bitmap);
  return img;
}
