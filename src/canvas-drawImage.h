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

#ifndef __CANVAS_DRAW_IMAGE_H__
#define __CANVAS_DRAW_IMAGE_H__

#include "include-openvg.h"
#include "image-util.h"

void canvas_drawImage(image_t *image, VGfloat dx, VGfloat dy, VGfloat dw, VGfloat dh, VGfloat sx, VGfloat sy, VGfloat sw, VGfloat sh);

#endif
