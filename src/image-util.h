/*
 * Copyright (C) 2015 NIPE-SYSTEMS
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

#ifndef __IMAGE_UTIL_H__
#define __IMAGE_UTIL_H__

#include <VG/openvg.h>
#include <FreeImage.h>

typedef struct image_t {
  VGImage image;
  VGuint width, height;
} image_t;

image_t *image_load(const char *path);
FIBITMAP* image_load_bitmap(const char *path);
image_t* image_create(FIBITMAP *bitmap);
void image_cleanup(image_t *image);
void image_free_bitmap(FIBITMAP *bitmap);
char *image_to_data_url(char *type, float encoder_options);
char *image_to_blob(char *type, float encoder_options, size_t *data_amount);

#endif /* __IMAGE_UTIL_H__ */
