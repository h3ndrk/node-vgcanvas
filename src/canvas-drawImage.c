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

#include "egl-util.h"
#include "include-openvg.h"
#include "image-util.h"

void canvas_drawImage(image_t *image, VGfloat dx, VGfloat dy, VGfloat dw, VGfloat dh, VGfloat sx, VGfloat sy, VGfloat sw, VGfloat sh)
{
  VGint matrix = vgGeti(VG_MATRIX_MODE);
  vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
  
  vgLoadIdentity();
  vgTranslate(dx, egl_get_height() - dy - dh);
  vgScale(dw / sw, dh / sh);
  
  VGImage child = vgChildImage(image->image, sx, image->height - sy - sh, sw, sh);
  vgDrawImage(child);
  vgDestroyImage(child);
  
  vgSeti(VG_MATRIX_MODE, matrix);
}
