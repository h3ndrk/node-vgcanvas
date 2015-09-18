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

#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <VG/openvg.h>

typedef enum
{
	CANVAS_LINE_CAP_BUTT = VG_CAP_BUTT,
	CANVAS_LINE_CAP_ROUND = VG_CAP_ROUND,
	CANVAS_LINE_CAP_SQUARE = VG_CAP_SQUARE
} canvas_line_cap_t;

typedef enum
{
	CANVAS_LINE_JOIN_MITER = VG_JOIN_MITER,
	CANVAS_LINE_JOIN_ROUND = VG_JOIN_ROUND,
	CANVAS_LINE_JOIN_BEVEL = VG_JOIN_BEVEL
} canvas_line_join_t;

void canvas__init(void);
void canvas__cleanup(void);

void canvas_clearRect(VGfloat x, VGfloat y, VGfloat width, VGfloat height);
void canvas_fillRect(VGfloat x, VGfloat y, VGfloat width, VGfloat height);
void canvas_fillStyle_color(VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha);
void canvas_strokeRect(VGfloat x, VGfloat y, VGfloat width, VGfloat height);
void canvas_strokeStyle_color(VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha);
void canvas_lineWidth(VGfloat width);
void canvas_lineCap(canvas_line_cap_t line_cap);
void canvas_lineJoin(canvas_line_join_t line_join);
void canvas_globalAlpha(VGfloat alpha);
void canvas_setLineDash(VGint count, const VGfloat *data);
void canvas_lineDashOffset(VGfloat offset);

void canvas_beginPath(void);
void canvas_moveTo(VGfloat x, VGfloat y);
void canvas_lineTo(VGfloat x, VGfloat y);
void canvas_quadraticCurveTo(VGfloat cpx, VGfloat cpy, VGfloat x, VGfloat y);
void canvas_bezierCurveTo(VGfloat cp1x, VGfloat cp1y, VGfloat cp2x, VGfloat cp2y, VGfloat x, VGfloat y);
//void canvas_ellipse(VGfloat x, VGfloat y, VGfloat radius_x, VGfloat radius_y, VGfloat rotation, VGfloat start_angle, VGfloat end_angle, VGboolean anticlockwise);
void canvas_arc(VGfloat x, VGfloat y, VGfloat radius, VGfloat start_angle, VGfloat end_angle, VGboolean anticlockwise);
void canvas_rect(VGfloat x, VGfloat y, VGfloat width, VGfloat height);
void canvas_closePath(void);
void canvas_clip(void);
void canvas_save(void);
void canvas_restore(void);
void canvas_stroke(void);
void canvas_fill(void);

#endif /* __CANVAS_H__ */
