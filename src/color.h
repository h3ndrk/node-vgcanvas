/**
 * Copyright (C) 2015 NIPE-SYSTEMS
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

#ifndef __COLOR_H__
#define __COLOR_H__

#include <VG/openvg.h>

typedef enum
{
	PAINT_TYPE_COLOR = VG_PAINT_TYPE_COLOR,
	PAINT_TYPE_LINEAR_GRADIENT = VG_PAINT_TYPE_LINEAR_GRADIENT
} paint_type_t;

typedef struct
{
	paint_type_t paintType;
	VGPaint paint;
	VGint count;
	VGfloat *data;
} paint_t;

void paint_createColor(paint_t *paint, float red, float green, float blue, float alpha);
void paint_createLinearGradient(paint_t *paint, float x1, float y1, float x2, float y2);
void paint_destroy(paint_t *paint);
void paint_activate(paint_t *paint, VGbitfield mode);
void paint_setRGBA(paint_t *color, float red, float green, float blue, float alpha);
void paint_addColorStop(paint_t *paint, VGfloat pos, VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha);

#endif /* __COLOR_H__ */
