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
#include <math.h>
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

static VGfloat canvas_ellipse_px = 0;
static VGfloat canvas_ellipse_py = 0;
static VGfloat canvas_ellipse_vg_rotation = 0;
static VGfloat canvas_ellipse_angle = 0;

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

void canvas_moveTo(VGfloat x, VGfloat y)
{
	VGubyte segment[1] = { VG_MOVE_TO_ABS };
	VGfloat data[2];

	data[0] = x;
	data[1] = y;

	currentPath_sx = x;
	currentPath_sy = y;

	vgAppendPathData(currentPath, 1, segment, (const void *)data);
}

void canvas_lineTo(VGfloat x, VGfloat y)
{
	VGubyte segment[1] = { VG_LINE_TO_ABS };
	VGfloat data[2];

	data[0] = x;
	data[1] = y;

	vgAppendPathData(currentPath, 1, segment, (const void *)data);
}

void canvas_quadraticCurveTo(VGfloat cpx, VGfloat cpy, VGfloat x, VGfloat y)
{
	VGubyte segment[1] = { VG_QUAD_TO_ABS };
	VGfloat data[4];

	data[0] = cpx;
	data[1] = cpy;
	data[2] = x;
	data[3] = y;

	vgAppendPathData(currentPath, 1, segment, (const void *)data);
}

void canvas_bezierCurveTo(VGfloat cp1x, VGfloat cp1y, VGfloat cp2x, VGfloat cp2y, VGfloat x, VGfloat y)
{
	VGubyte segment[1] = { VG_CUBIC_TO_ABS };
	VGfloat data[6];

	data[0] = cp1x;
	data[1] = cp1y;
	data[2] = cp2x;
	data[3] = cp2y;
	data[4] = x;
	data[5] = y;

	vgAppendPathData(currentPath, 1, segment, (const void *)data);
}

<<<<<<< HEAD
// static void canvas_ellipse_rotate_p(VGfloat rotation)
// {
// 	VGfloat canvas_ellipse_tx = canvas_ellipse_px * cos(rotation) - canvas_ellipse_py * sin(rotation);
// 	canvas_ellipse_py = canvas_ellipse_px * sin(rotation) + canvas_ellipse_py * cos(rotation);
// 	canvas_ellipse_px = canvas_ellipse_tx;
// }

// static void canvas_ellipse_add_arc(VGPathCommand command, VGfloat x, VGfloat y, VGfloat rotation, VGfloat radius_x, VGfloat radius_y)
// {
// 	VGubyte segment[1] = { command };
// 	VGfloat data[5];
	
// 	data[0] = radius_x;
// 	data[1] = radius_y;
// 	data[2] = rotation;
// 	data[3] = x;
// 	data[4] = y;
	
// 	printf("{ radius_x: %f, radius_y: %f, rotation: %f, x: %f, y: %f }\n", radius_x, radius_y, rotation, x, y);
	
// 	vgAppendPathData(currentPath, 1, segment, (const void *)data);
// }

// void canvas_ellipse(VGfloat x, VGfloat y, VGfloat radius_x, VGfloat radius_y, VGfloat rotation, VGfloat start_angle, VGfloat end_angle, VGboolean anticlockwise)
// {
// 	VGubyte segment[1];
// 	VGfloat data[5];
	
// 	// start_angle %= 2 * M_PI;
// 	// end_angle %= 2 * M_PI;
	
// 	if(abs(start_angle) == 2 * M_PI)
// 	{
// 		start_angle *= 0.999;
// 	}
	
// 	if(abs(end_angle) == 2 * M_PI)
// 	{
// 		end_angle *= 0.999;
// 	}
	
// 	if(anticlockwise)
// 	{
// 		if(abs(end_angle - start_angle) > M_PI)
// 		{
// 			segment[0] = VG_LCCWARC_TO_ABS;
// 		}
// 		else
// 		{
// 			segment[0] = VG_SCCWARC_TO_ABS;
// 		}
// 	}
// 	else
// 	{
// 		start_angle *= -1;
// 		end_angle *= -1;
		
// 		if(abs(end_angle - start_angle) > M_PI)
// 		{
// 			segment[0] = VG_LCWARC_TO_ABS;
// 		}
// 		else
// 		{
// 			segment[0] = VG_SCWARC_TO_ABS;
// 		}
// 	}
	
// 	// move from center point to start point at start angle
// 	canvas_moveTo(x + radius_x * cos(start_angle + (rotation * M_PI / 180)), y + radius_y * sin(start_angle + (rotation * M_PI / 180)));
	
// 	data[0] = radius_x;
// 	data[1] = radius_y;
// 	data[2] = rotation;
// 	data[3] = x + radius_x * cos(end_angle + (rotation * M_PI / 180));// + radius_x * cos(end_angle) - radius_x * cos(start_angle);
// 	data[4] = y + radius_y * sin(end_angle + (rotation * M_PI / 180));// + radius_y * sin(end_angle) - radius_y * sin(start_angle);
	
// 	printf("{ radius_x: %f, radius_y: %f, rotation: %f, x: %f, y: %f }\n", radius_x, radius_y, rotation, x, y);
	
// 	vgAppendPathData(currentPath, 1, segment, (const void *)data);
	
	// canvas_ellipse_px = radius_x * cos(start_angle);
	// canvas_ellipse_py = radius_y * sin(start_angle);
	
	// canvas_ellipse_rotate_p(rotation);
	// canvas_ellipse_vg_rotation = rotation * 180.0 / M_PI;
	
	// canvas_moveTo(x + canvas_ellipse_px, y + canvas_ellipse_py);
	
	// if(anticlockwise)
	// {
	// 	if(start_angle - end_angle >= 2 * M_PI)
	// 	{
	// 		start_angle = 2 * M_PI;
	// 		end_angle = 0;
	// 	}
		
	// 	while(end_angle > start_angle)
	// 	{
	// 		end_angle -= 2 * M_PI;
	// 	}
		
	// 	canvas_ellipse_angle = start_angle - M_PI;
		
	// 	while(canvas_ellipse_angle > end_angle)
	// 	{
	// 		canvas_ellipse_px = radius_x * cos(canvas_ellipse_angle);
	// 		canvas_ellipse_py = radius_y * sin(canvas_ellipse_angle);
			
	// 		canvas_ellipse_rotate_p(rotation);
			
	// 		canvas_ellipse_add_arc(VG_SCWARC_TO_ABS, x, y, rotation, radius_x, radius_y);
			
	// 		canvas_ellipse_angle -= 2 * M_PI;
	// 	}
		
	// 	canvas_ellipse_px = radius_x * cos(end_angle);
	// 	canvas_ellipse_py = radius_y * sin(end_angle);
		
	// 	canvas_ellipse_rotate_p(rotation);
		
	// 	canvas_ellipse_add_arc(VG_SCWARC_TO_ABS, x, y, rotation, radius_x, radius_y);
	// }
	// else
	// {
	// 	if(end_angle - start_angle >= 2 * M_PI)
	// 	{
	// 		end_angle = 2 * M_PI;
	// 		start_angle = 0;
	// 	}
		
	// 	while(end_angle < start_angle)
	// 	{
	// 		end_angle += 2 * M_PI;
	// 	}
		
	// 	canvas_ellipse_angle = start_angle + M_PI;
		
	// 	while(canvas_ellipse_angle < end_angle)
	// 	{
	// 		canvas_ellipse_px = radius_x * cos(canvas_ellipse_angle);
	// 		canvas_ellipse_py = radius_y * sin(canvas_ellipse_angle);
			
	// 		canvas_ellipse_rotate_p(rotation);
			
	// 		canvas_ellipse_add_arc(VG_SCCWARC_TO_ABS, x, y, rotation, radius_x, radius_y);
			
	// 		canvas_ellipse_angle += 2 * M_PI;
	// 	}
		
	// 	canvas_ellipse_px = radius_x * cos(end_angle);
	// 	canvas_ellipse_py = radius_y * sin(end_angle);
		
	// 	canvas_ellipse_rotate_p(rotation);
		
	// 	canvas_ellipse_add_arc(VG_SCCWARC_TO_ABS, x, y, rotation, radius_x, radius_y);
	// }
//}
=======
static void canvas_ellipse_rotate_p(VGfloat rotation)
{
	VGfloat canvas_ellipse_tx = canvas_ellipse_px * cos(rotation) - canvas_ellipse_py * sin(rotation);
	canvas_ellipse_py = canvas_ellipse_px * sin(rotation) + canvas_ellipse_py * cos(rotation);
	canvas_ellipse_px = canvas_ellipse_tx;
}

static void canvas_ellipse_add_arc(VGPathCommand command, VGfloat x, VGfloat y, VGfloat rotation, VGfloat radius_x, VGfloat radius_y)
{
	VGubyte segment[1] = { command };
	VGfloat data[5];

	data[0] = radius_x;
	data[1] = radius_y;
	data[2] = rotation;
	data[3] = x;
	data[4] = y;

	vgAppendPathData(currentPath, 1, segment, (const void *)data);
}

void canvas_ellipse(VGfloat x, VGfloat y, VGfloat radius_x, VGfloat radius_y, VGfloat rotation, VGfloat start_angle, VGfloat end_angle, VGboolean anticlockwise)
{
	canvas_ellipse_px = radius_x * cos(start_angle);
	canvas_ellipse_py = radius_y * sin(start_angle);

	canvas_ellipse_rotate_p(rotation);
	canvas_ellipse_vg_rotation = rotation * 180.0 / M_PI;

	canvas_moveTo(x + canvas_ellipse_px, y + canvas_ellipse_py);

	if(anticlockwise)
	{
		if(start_angle - end_angle >= 2 * M_PI)
		{
			start_angle = 2 * M_PI;
			end_angle = 0;
		}

		while(end_angle > start_angle)
		{
			end_angle -= 2 * M_PI;
		}

		canvas_ellipse_angle = start_angle - M_PI;

		while(canvas_ellipse_angle > end_angle)
		{
			canvas_ellipse_px = radius_x * cos(canvas_ellipse_angle);
			canvas_ellipse_py = radius_y * sin(canvas_ellipse_angle);

			canvas_ellipse_rotate_p(rotation);

			canvas_ellipse_add_arc(VG_SCWARC_TO_REL, x, y, rotation, radius_x, radius_y);

			canvas_ellipse_angle -= 2 * M_PI;
		}

		canvas_ellipse_px = radius_x * cos(end_angle);
		canvas_ellipse_py = radius_y * sin(end_angle);

		canvas_ellipse_rotate_p(rotation);

		canvas_ellipse_add_arc(VG_SCWARC_TO_REL, x, y, rotation, radius_x, radius_y);
	}
	else
	{
		if(end_angle - start_angle >= 2 * M_PI)
		{
			end_angle = 2 * M_PI;
			start_angle = 0;
		}

		while(end_angle < start_angle)
		{
			end_angle += 2 * M_PI;
		}

		canvas_ellipse_angle = start_angle + M_PI;

		while(canvas_ellipse_angle < end_angle)
		{
			canvas_ellipse_px = radius_x * cos(canvas_ellipse_angle);
			canvas_ellipse_py = radius_y * sin(canvas_ellipse_angle);

			canvas_ellipse_rotate_p(rotation);

			canvas_ellipse_add_arc(VG_SCCWARC_TO_REL, x, y, rotation, radius_x, radius_y);

			canvas_ellipse_angle += 2 * M_PI;
		}

		canvas_ellipse_px = radius_x * cos(end_angle);
		canvas_ellipse_py = radius_y * sin(end_angle);

		canvas_ellipse_rotate_p(rotation);

		canvas_ellipse_add_arc(VG_SCCWARC_TO_REL, x, y, rotation, radius_x, radius_y);
	}
}
>>>>>>> ed902a49bb35da1506c30229fc358d6a2056c7d7

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
