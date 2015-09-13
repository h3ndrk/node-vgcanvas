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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "EGL/egl.h"
#include "GLES/gl.h"
#include "bcm_host.h"
#include "VG/openvg.h"
#include "VG/vgu.h"
#include "VG/vgext.h"

#include "egl-util.h"
#include "canvas.h"
#include "color.h"

static color_t fill_color;
static color_t stroke_color;
static VGPath immediatePath = 0;
static VGPath currentPath = 0;
static VGfloat currentPath_sx = 0;
static VGfloat currentPath_sy = 0;

static VGfloat lineWidth = 1;
static canvas_line_cap_t lineCap = CANVAS_LINE_CAP_BUTT;
static canvas_line_join_t lineJoin = CANVAS_LINE_JOIN_MITER;
static VGfloat globalAlpha = 1;

void canvas__init(void)
{
	VGPaint clearPaint = 0;
	VGfloat temp_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // black
	
	egl_init();
	
	printf("{ width: %i, height: %i }\n", egl_get_width(), egl_get_height());
	
	// immediate colors for fill and stroke
	fill_color.paint = vgCreatePaint();
	stroke_color.paint = vgCreatePaint();
	
	// clear color
	clearPaint = vgCreatePaint();
	vgSetfv(VG_CLEAR_COLOR, 4, temp_color);
	vgDestroyPaint(clearPaint);
	
	// reset values
	canvas_fillStyle_color(1, 1, 1, 1);
	canvas_strokeStyle_color(1, 1, 1, 1);
	canvas_lineWidth(1);
	canvas_lineCap(CANVAS_LINE_CAP_BUTT);
	canvas_lineJoin(CANVAS_LINE_JOIN_MITER);
	canvas_globalAlpha(1);
	
	// immediate path for drawing rects, etc.
	immediatePath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
	
	// currentPath for path rendering (beginPath, etc.)
	currentPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
	
	vgSeti(VG_SCISSORING, VG_FALSE);
	
	vgLoadIdentity();
}

void canvas__cleanup(void)
{
	vgDestroyPaint(fill_color.paint);
	vgDestroyPaint(stroke_color.paint);
	
	vgDestroyPath(immediatePath);
	vgDestroyPath(currentPath);
	
	egl_cleanup();
}

void canvas_clearRect(VGfloat x, VGfloat y, VGfloat width, VGfloat height)
{
	vgSeti(VG_SCISSORING, VG_FALSE);
	vgClear(x, y, width, height);
}

void canvas_fillRect(VGfloat x, VGfloat y, VGfloat width, VGfloat height)
{
	VGfloat color_values[4];
	
	color_values[0] = fill_color.red;
	color_values[1] = fill_color.green;
	color_values[2] = fill_color.blue;
	color_values[3] = fill_color.alpha * globalAlpha;
	
	vgSetParameteri(fill_color.paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	vgSetParameterfv(fill_color.paint, VG_PAINT_COLOR, 4, color_values);
	vgSetPaint(fill_color.paint, VG_FILL_PATH);
	
	vgClearPath(immediatePath, VG_PATH_CAPABILITY_ALL);
	vguRect(immediatePath, x, y, width, height);
	vgDrawPath(immediatePath, VG_FILL_PATH);
}

void canvas_fillStyle_color(VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha)
{
	color_set_rgba(&fill_color, red, green, blue, alpha);
}

void canvas_strokeRect(VGfloat x, VGfloat y, VGfloat width, VGfloat height)
{
	VGfloat color_values[4];
	
	color_values[0] = stroke_color.red;
	color_values[1] = stroke_color.green;
	color_values[2] = stroke_color.blue;
	color_values[3] = stroke_color.alpha * globalAlpha;
	
	vgSetParameteri(stroke_color.paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	vgSetParameterfv(stroke_color.paint, VG_PAINT_COLOR, 4, color_values);
	vgSetPaint(stroke_color.paint, VG_STROKE_PATH);
	
	vgClearPath(immediatePath, VG_PATH_CAPABILITY_ALL);
	vguRect(immediatePath, x, y, width, height);
	vgDrawPath(immediatePath, VG_STROKE_PATH);
}

void canvas_strokeStyle_color(VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha)
{
	color_set_rgba(&stroke_color, red, green, blue, alpha);
}

void canvas_lineWidth(VGfloat width)
{
	lineWidth = width;
	
	vgSetf(VG_STROKE_LINE_WIDTH, width);
}

void canvas_lineCap(canvas_line_cap_t line_cap)
{
	lineCap = line_cap;
	
	vgSeti(VG_STROKE_CAP_STYLE, line_cap);
}

void canvas_lineJoin(canvas_line_join_t line_join)
{
	lineJoin = line_join;
	
	vgSeti(VG_STROKE_CAP_STYLE, line_join);
}

void canvas_globalAlpha(VGfloat alpha)
{
	globalAlpha = alpha;
	
	if(globalAlpha > 1 || globalAlpha < 0)
	{
		globalAlpha = 1;
	}
}

void canvas_beginPath(void)
{
	vgClearPath(currentPath, VG_PATH_CAPABILITY_ALL);
}

void canvas_moveTo(GLfloat x, GLfloat y)
{
	VGubyte segment[1] = { VG_MOVE_TO_REL };
	VGfloat data[2];
	
	data[0] = x;
	data[1] = y;
	
	currentPath_sx = x;
	currentPath_sy = y;
	
	vgAppendPathData(currentPath, 1, segment, (const void *)data);
}

void canvas_lineTo(GLfloat x, GLfloat y)
{
	VGubyte segment[1] = { VG_LINE_TO_REL };
	VGfloat data[2];
	
	data[0] = x;
	data[1] = y;
	
	vgAppendPathData(currentPath, 1, segment, (const void *)data);
}

void canvas_quadraticCurveTo(GLfloat cpx, GLfloat cpy, GLfloat x, GLfloat y)
{
	VGubyte segment[1] = { VG_QUAD_TO_REL };
	VGfloat data[4];
	
	data[0] = cpx;
	data[1] = cpy;
	data[2] = x;
	data[3] = y;
	
	vgAppendPathData(currentPath, 1, segment, (const void *)data);
}

void canvas_bezierCurveTo(GLfloat cp1x, GLfloat cp1y, GLfloat cp2x, GLfloat cp2y, GLfloat x, GLfloat y)
{
	VGubyte segment[1] = { VG_CUBIC_TO_REL };
	VGfloat data[4];
	
	data[0] = cp1x;
	data[1] = cp1y;
	data[2] = cp2x;
	data[3] = cp2y;
	data[4] = x;
	data[5] = y;
	
	vgAppendPathData(currentPath, 1, segment, (const void *)data);
}

void canvas_closePath(void)
{
	VGubyte segment[1] = { VG_CLOSE_PATH };
	VGfloat data[2];
	
	data[0] = currentPath_sx;
	data[1] = currentPath_sy;
	
	vgAppendPathData(currentPath, 1, segment, (const void *)data);
}

void canvas_stroke(void)
{
	VGfloat color_values[4];
	
	color_values[0] = stroke_color.red;
	color_values[1] = stroke_color.green;
	color_values[2] = stroke_color.blue;
	color_values[3] = stroke_color.alpha * globalAlpha;
	
	vgSetParameteri(stroke_color.paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	vgSetParameterfv(stroke_color.paint, VG_PAINT_COLOR, 4, color_values);
	vgSetPaint(stroke_color.paint, VG_STROKE_PATH);
	
	vgDrawPath(currentPath, VG_STROKE_PATH);
}

void canvas_fill(void)
{
	VGfloat color_values[4];
	
	color_values[0] = fill_color.red;
	color_values[1] = fill_color.green;
	color_values[2] = fill_color.blue;
	color_values[3] = fill_color.alpha * globalAlpha;
	
	vgSetParameteri(fill_color.paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	vgSetParameterfv(fill_color.paint, VG_PAINT_COLOR, 4, color_values);
	vgSetPaint(fill_color.paint, VG_FILL_PATH);
	
	vgDrawPath(currentPath, VG_FILL_PATH);
}
