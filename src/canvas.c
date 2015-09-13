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
static VGfloat globalAlpha = 1;

void canvas__init(void)
{
	VGPaint clearPaint = 0;
	VGfloat temp_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	
	egl_init();
	
	printf("{ width: %i, height: %i }\n", egl_get_width(), egl_get_height());
	
	// immediate colors for fill and stroke
	fill_color.paint = vgCreatePaint();
	stroke_color.paint = vgCreatePaint();
	
	// clear color
	clearPaint = vgCreatePaint();
	vgSetfv(VG_CLEAR_COLOR, 4, temp_color);
	vgDestroyPaint(clearPaint);
	
	// reset fill and stroke color
	canvas_fillStyle_color(1, 1, 1, 1);
	canvas_strokeStyle_color(1, 1, 1, 1);
	
	// immediate path for drawing rects, circles, etc.
	immediatePath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
	
	vgSeti(VG_SCISSORING, VG_FALSE);
	
	vgLoadIdentity();
}

void canvas__cleanup(void)
{
	vgDestroyPaint(fill_color.paint);
	vgDestroyPaint(stroke_color.paint);
	
	vgDestroyPath(immediatePath);
	
	egl_cleanup();
}

void canvas_clearRect(VGfloat x, VGfloat y, VGfloat width, VGfloat height)
{
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
	vgSetf(VG_STROKE_LINE_WIDTH, width);
}

void canvas_lineCap(char *cap_style)
{
	if(!strcmp(cap_style, "butt"))
	{
		vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_BUTT);
	}
	else if(!strcmp(cap_style, "round"))
	{
		vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_ROUND);
	}
	else
	{
		vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_SQUARE);
	}
}

void canvas_lineJoin(char *join_style)
{
	if(!strcmp(join_style, "miter"))
	{
		vgSeti(VG_STROKE_CAP_STYLE, VG_JOIN_MITER);
	}
	else if(!strcmp(join_style, "round"))
	{
		vgSeti(VG_STROKE_CAP_STYLE, VG_JOIN_ROUND);
	}
	else
	{
		vgSeti(VG_STROKE_CAP_STYLE, VG_JOIN_BEVEL);
	}
}

void canvas_globalAlpha(VGfloat alpha)
{
	globalAlpha = alpha;
	
	if(globalAlpha > 1 || globalAlpha < 0)
	{
		globalAlpha = 1;
	}
}
