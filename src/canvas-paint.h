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

#ifndef __CANVAS_PAINT_H__
#define __CANVAS_PAINT_H__

#include <VG/openvg.h>

typedef enum paint_type_t
{
	PAINT_TYPE_COLOR = VG_PAINT_TYPE_COLOR,
	PAINT_TYPE_LINEAR_GRADIENT = VG_PAINT_TYPE_LINEAR_GRADIENT,
	PAINT_TYPE_RADIAL_GRADIENT = VG_PAINT_TYPE_RADIAL_GRADIENT
} paint_type_t;

typedef struct paint_t
{
	paint_type_t paint_type;
	VGPaint paint;
	VGint count;
	VGfloat *data;
} paint_t;

void paint_createColor(paint_t *paint, VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha);
void paint_createLinearGradient(paint_t *paint, VGfloat x1, VGfloat y1, VGfloat x2, VGfloat y2);
void paint_createRadialGradient(paint_t *paint, VGfloat cx, VGfloat cy, VGfloat r, VGfloat fx, VGfloat fy);
void paint_cleanup(paint_t *paint);
void paint_activate(paint_t *paint, VGbitfield mode);
void paint_setRGBA(paint_t *color, VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha);
void paint_addColorStop(paint_t *paint, VGfloat pos, VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha);

#endif /* __CANVAS_PAINT_H__ */
