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
#include <sys/time.h>
#include <EGL/egl.h>
#include <bcm_host.h>
#include <VG/openvg.h>
#include <VG/vgu.h>
#include <VG/vgext.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

#include "egl-util.h"
#include "canvas.h"
#include "color.h"
// #include "font.h"
#include "canvas-clearRect.h"
#include "canvas-lineWidth.h"
#include "canvas-lineCap.h"
#include "canvas-lineJoin.h"
#include "canvas-globalAlpha.h"

static VGPaint fillColor;
static VGPaint strokeColor;
static VGPath immediatePath = 0;
VGPath currentPath = 0;
static VGfloat currentPath_sx = 0;
static VGfloat currentPath_sy = 0;

// static VGfloat canvas_ellipse_px = 0;
// static VGfloat canvas_ellipse_py = 0;
// static VGfloat canvas_ellipse_vg_rotation = 0;
// static VGfloat canvas_ellipse_angle = 0;

static canvas_state_t currentState;
static canvas_state_t *stateStack = NULL;

static int init = 0;

#define SEGMENTS_COUNT_MAX 256
#define COORDS_COUNT_MAX 1024
#define FONT_FLOAT_FROM_26_6(x) ((VGfloat)x / 64.0f)

static FT_Library font_library = NULL;
static font_t *fonts = NULL;
static int fonts_amount = 0;

static VGuint segments_count;
static VGubyte segments[SEGMENTS_COUNT_MAX];
static VGuint coords_count;
static VGfloat coords[COORDS_COUNT_MAX];

void canvas__init(void)
{
	font_init();
	
	egl_init();
	
	printf("{ width: %i, height: %i }\n", egl_get_width(), egl_get_height());
	
	// immediate colors for fill and stroke
	fillColor = vgCreatePaint();
	strokeColor = vgCreatePaint();
	
	// reset values
	canvas_fillStyle_color(1, 1, 1, 1);
	canvas_strokeStyle_color(1, 1, 1, 1);
	canvas_lineWidth(1);
	canvas_lineCap("butt");
	canvas_lineJoin("miter");
	canvas_globalAlpha(1);
	canvas_lineDashOffset(0);
	canvas_setLineDash(0, NULL);
	currentState.clipping = VG_FALSE;
	currentState.savedLayer = 0;
	currentState.next = NULL;
	
	canvas_beginPath_init();
	
	// immediate path for drawing rects, etc.
	immediatePath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
	
	// currentPath for path rendering (beginPath, etc.)
	currentPath = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
	
	vgSeti(VG_SCISSORING, VG_FALSE);
	vgSeti(VG_MASKING, VG_FALSE);
	
	vgLoadIdentity();
	
	init = 1;
	
	canvas_clearRect_init();
}

static void canvas__destroyState(canvas_state_t *state)
{
	if(state->savedLayer)
	{
		vgDestroyMaskLayer(state->savedLayer);
	}
	
	if(state->dashPattern)
		free(state->dashPattern);
	
}

void canvas__cleanup(void)
{
	if(!init)
		return;
	
	canvas_state_t *current = stateStack;
	while(current)
	{
		canvas_state_t *next = current->next;
		canvas__destroyState(current);
		free(current);
		current = next;
	}
	canvas__destroyState(&currentState);
	
	canvas_beginPath_cleanup();
	
	vgDestroyPath(immediatePath);
	vgDestroyPath(currentPath);
	
	vgDestroyPaint(fillColor);
	vgDestroyPaint(strokeColor);
	
	egl_cleanup();
	
	font_cleanup();
}

unsigned int canvas_stackSize(void)
{
	unsigned int size = 0;
	canvas_state_t *current = stateStack;
	
	while(current)
	{
		current = current->next;
		size++;
	}
	
	return size;
}

void canvas_fillRect(VGfloat x, VGfloat y, VGfloat width, VGfloat height)
{
	VGfloat color_values[4];
	
	color_values[0] = currentState.fillColor.red;
	color_values[1] = currentState.fillColor.green;
	color_values[2] = currentState.fillColor.blue;
	color_values[3] = currentState.fillColor.alpha * canvas_globalAlpha_get();
	
	vgSetParameteri(fillColor, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	vgSetParameterfv(fillColor, VG_PAINT_COLOR, 4, color_values);
	vgSetPaint(fillColor, VG_FILL_PATH);
	
	vgClearPath(immediatePath, VG_PATH_CAPABILITY_ALL);
	vguRect(immediatePath, x, y, width, height);
	vgDrawPath(immediatePath, VG_FILL_PATH);
}

void canvas_fillStyle_color(VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha)
{
	color_set_rgba(&currentState.fillColor, red, green, blue, alpha);
}

void canvas_strokeRect(VGfloat x, VGfloat y, VGfloat width, VGfloat height)
{
	VGfloat color_values[4];
	
	color_values[0] = currentState.strokeColor.red;
	color_values[1] = currentState.strokeColor.green;
	color_values[2] = currentState.strokeColor.blue;
	color_values[3] = currentState.strokeColor.alpha * canvas_globalAlpha_get();
	
	vgSetParameteri(strokeColor, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	vgSetParameterfv(strokeColor, VG_PAINT_COLOR, 4, color_values);
	vgSetPaint(strokeColor, VG_STROKE_PATH);
	
	vgClearPath(immediatePath, VG_PATH_CAPABILITY_ALL);
	vguRect(immediatePath, x, y, width, height);
	vgDrawPath(immediatePath, VG_STROKE_PATH);
}

void canvas_strokeStyle_color(VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha)
{
	color_set_rgba(&currentState.strokeColor, red, green, blue, alpha);
}

// void canvas_lineWidth(VGfloat width)
// {
// 	currentState.lineWidth = width;
	
// 	vgSetf(VG_STROKE_LINE_WIDTH, width);
// }

// void canvas_lineCap(canvas_line_cap_t line_cap)
// {
// 	currentState.lineCap = line_cap;
	
// 	vgSeti(VG_STROKE_CAP_STYLE, line_cap);
// }

// void canvas_lineJoin(canvas_line_join_t line_join)
// {
// 	currentState.lineJoin = line_join;
	
// 	vgSeti(VG_STROKE_CAP_STYLE, line_join);
// }

// void canvas_globalAlpha(VGfloat alpha)
// {
// 	if(alpha > 1 || alpha < 0)
// 	{
// 		alpha = 1;
// 	}
	
// 	canvas_globalAlpha_get() = alpha;
// }

// void canvas_beginPath(void)
// {
// 	vgClearPath(currentPath, VG_PATH_CAPABILITY_ALL);
// }

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

void canvas_arc(VGfloat x, VGfloat y, VGfloat radius, VGfloat start_angle, VGfloat end_angle, VGboolean anticlockwise)
{
	VGfloat angle_extent = 0;
	
	// radian to degrees
	start_angle *= 180 / M_PI;
	end_angle *= 180 / M_PI;
	
	// calculate angle extent
	if(anticlockwise == VG_TRUE)
	{
		angle_extent = 360 - (end_angle - start_angle);
	}
	else
	{
		angle_extent = 0 - (end_angle - start_angle);
	}
	
	vguArc(currentPath, x, y, radius * 2, radius * 2, start_angle, angle_extent, VGU_ARC_OPEN);
}

// static canvas_arcTo_transform(VGfloat px, VGfloat py, VGfloat *x, VGfloat *y)
// {
// 	*x = (px * cos_rotation - py * sin_rotation) * scale_x;
// }

// // radius_y must default to radius_x, rotation must default to 0
// void canvas_arcTo(VGfloat x1, VGfloat y1, VGfloat x2, VGfloat y2, VGfloat radius_x, VGfloat radius_y, VGfloat rotation)
// {
// 	VGfloat scale_x = radius_x / radius_y;
// 	VGfloat cos_rotation = cos(-rotation);
// 	VGfloat sin_rotation = sin(-rotation);
	
// 	VGfloat p0_x = (x * cos_rotation - py * sin_rotation) * scale_x;
// }

void canvas_rect(VGfloat x, VGfloat y, VGfloat width, VGfloat height)
{
	vguRect(currentPath, x, y, width, height);
}

void canvas_setLineDash(VGint count, const VGfloat *data)
{
	currentState.dashCount = count;
	if(count > 0)
	{
		currentState.dashPattern = realloc(currentState.dashPattern, count * sizeof(data));
		if(!currentState.dashPattern) 
		{
			printf("realloc failed\n");
			exit(1);
		}
			
		memcpy(currentState.dashPattern, data, count * sizeof(VGfloat));
	}
	else
	{
		currentState.dashPattern = 0;
	}
		
	vgSetfv(VG_STROKE_DASH_PATTERN, count, data);
}

// void canvas_lineDashOffset(VGfloat offset)
// {
// 	currentState.dashOffset = offset;
// 	vgSetf(VG_STROKE_DASH_PHASE, offset);
// }

void canvas_closePath(void)
{
	VGubyte segment[1] = { VG_CLOSE_PATH };
	VGfloat data[2];
	
	data[0] = currentPath_sx;
	data[1] = currentPath_sy;
	
	vgAppendPathData(currentPath, 1, segment, (const void *)data);
}

void canvas_clip(void)
{
	if(!currentState.clipping)
	{
		vgMask(VG_INVALID_HANDLE, VG_FILL_MASK, 0, 0, egl_get_width(), egl_get_height());
	}
	
	vgRenderToMask(currentPath, VG_FILL_PATH, VG_INTERSECT_MASK);
	
	vgSeti(VG_MASKING, VG_TRUE);
	
	currentState.clipping = VG_TRUE;
}

void canvas_save(void)
{
	canvas_state_t *savedState = malloc(sizeof(canvas_state_t));
	if(!savedState)
	{
		printf("malloc failed\n");
		exit(1);
	}
	
	memcpy(savedState, &currentState, sizeof(canvas_state_t));
	
	// may be NULL
	savedState->next = stateStack;
	
	stateStack = savedState;
	
	if(currentState.clipping)
	{	
		savedState->savedLayer = vgCreateMaskLayer(egl_get_width(), egl_get_height());
		vgCopyMask(savedState->savedLayer, 0, 0, 0, 0, egl_get_width(), egl_get_height());
	}
	
	if(currentState.dashCount > 0)
	{
		savedState->dashPattern = malloc(currentState.dashCount * sizeof(VGfloat));
		if(!savedState->dashPattern)
		{
			printf("malloc failed\n");
			exit(1);
		}
		
		memcpy(savedState->dashPattern, &currentState.dashPattern, currentState.dashCount * sizeof(VGfloat));
	}
	
	
}

void canvas_restore(void)
{
	if(!stateStack) 
	{
		printf("Can't restore state. No state on stack.\n");
		return;
	}
	
	canvas_state_t *restore = stateStack;
	
	if(restore->clipping)
	{
		vgMask(restore->savedLayer, VG_SET_MASK, 0, 0, egl_get_width(), egl_get_height());
		vgDestroyMaskLayer(restore->savedLayer);
	}
	
	vgSeti(VG_MASKING, restore->clipping);
	currentState.clipping = restore->clipping;
	// canvas_lineWidth(restore->lineWidth);
	// canvas_lineCap(restore->lineCap);
	// canvas_lineJoin(restore->lineJoin);
	// canvas_globalAlpha(restore->globalAlpha);
	canvas_lineDashOffset(restore->dashOffset);
	currentState.fillColor = restore->fillColor;
	currentState.strokeColor = restore->strokeColor;
	
	if(currentState.dashPattern)
		free(currentState.dashPattern);
	
	currentState.dashPattern = restore->dashPattern;
	currentState.dashCount = restore->dashCount;
	
	stateStack = restore->next;
	free(restore);
	
}

canvas_state_t* canvas_getState(void)
{
	return &currentState;
}

void canvas_stroke(void)
{
	VGfloat color_values[4];
	
	color_values[0] = currentState.strokeColor.red;
	color_values[1] = currentState.strokeColor.green;
	color_values[2] = currentState.strokeColor.blue;
	color_values[3] = currentState.strokeColor.alpha * canvas_globalAlpha_get();
	
	vgSetParameteri(strokeColor, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	vgSetParameterfv(strokeColor, VG_PAINT_COLOR, 4, color_values);
	vgSetPaint(strokeColor, VG_STROKE_PATH);
	
	vgDrawPath(currentPath, VG_STROKE_PATH);
}

void canvas_fill(void)
{
	VGfloat color_values[4];
	
	color_values[0] = currentState.fillColor.red;
	color_values[1] = currentState.fillColor.green;
	color_values[2] = currentState.fillColor.blue;
	color_values[3] = currentState.fillColor.alpha * canvas_globalAlpha_get();
	
	vgSetParameteri(fillColor, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	vgSetParameterfv(fillColor, VG_PAINT_COLOR, 4, color_values);
	vgSetPaint(fillColor, VG_FILL_PATH);
	
	vgDrawPath(currentPath, VG_FILL_PATH);
}

static void convert_contour(const FT_Vector *points, const char *tags, short points_count)
{
	int first_coords = coords_count;
	
	int first = 1;
	char last_tag = 0;
	int c = 0;
	
	for (; points_count != 0; ++points, ++tags, --points_count)
	{
		++c;
		
		char tag = *tags;
		if(first)
		{
			assert(tag & 0x1);
			assert(c==1); c=0;
			segments[segments_count++] = VG_MOVE_TO;
			first = 0;
		}
		else if(tag & 0x1)
		{
			/* on curve */
			
			if (last_tag & 0x1)
			{
				/* last point was also on -- line */
				assert(c==1); c=0;
				segments[segments_count++] = VG_LINE_TO;
			}
			else
			{
				/* last point was off -- quad or cubic */
				if (last_tag & 0x2)
				{
					/* cubic */
					assert(c==3); c=0;
					segments[segments_count++] = VG_CUBIC_TO;
				}
				else
				{
					/* quad */
					assert(c==2); c=0;
					segments[segments_count++] = VG_QUAD_TO;
				}
			}
		}
		else
		{
			/* off curve */
			
			if (tag & 0x2)
			{
				/* cubic */
				
				assert((last_tag & 0x1) || (last_tag & 0x2)); /* last either on or off and cubic */
			}
			else
			{
				/* quad */
				
				if (!(last_tag & 0x1))
				{
					/* last was also off curve */
					
					assert(!(last_tag & 0x2)); /* must be quad */
					
					/* add on point half-way between */
					assert(c==2); c=1;
					segments[segments_count++] = VG_QUAD_TO;
					VGfloat x = (coords[coords_count - 2] + FONT_FLOAT_FROM_26_6(points->x)) * 0.5f;
					VGfloat y = (coords[coords_count - 1] + FONT_FLOAT_FROM_26_6(points->y)) * 0.5f;
					coords[coords_count++] = x;
					coords[coords_count++] = y;
				}
			}
		}
		last_tag = tag;
		
		coords[coords_count++] = FONT_FLOAT_FROM_26_6(points->x);
		coords[coords_count++] = FONT_FLOAT_FROM_26_6(points->y);
	}
	
	if (last_tag & 0x1)
	{
		/* last point was also on -- line (implicit with close path) */
		assert(c==0);
	}
	else
	{
		++c;
		
		/* last point was off -- quad or cubic */
		if (last_tag & 0x2)
		{
			/* cubic */
			assert(c==3); c=0;
			segments[segments_count++] = VG_CUBIC_TO;
		}
		else
		{
			/* quad */
			assert(c==2); c=0;
			segments[segments_count++] = VG_QUAD_TO;
		}
		coords[coords_count++] = coords[first_coords + 0];
		coords[coords_count++] = coords[first_coords + 1];
	}
	
	segments[segments_count++] = VG_CLOSE_PATH;
}

static void convert_outline(const FT_Vector *points, const char *tags, const short *contours, short contours_count, short points_count)
{
	segments_count = 0;
	coords_count = 0;
	
	short last_contour = 0;
	for (; contours_count != 0; ++contours, --contours_count)
	{
		short contour = *contours + 1;
		convert_contour(points + last_contour, tags + last_contour, contour - last_contour);
		last_contour = contour;
	}
	assert(last_contour == points_count);
	
	assert(segments_count <= SEGMENTS_COUNT_MAX); /* oops... we overwrote some memory */
	assert(coords_count <= COORDS_COUNT_MAX);
}

static int font_get(char *path)
{
	int i = 0;
	
	if(path == NULL || fonts == NULL)
	{
		return -1;
	}
	
	for(i = 0; i < fonts_amount; i++)
	{
		if(strcmp(fonts[i].path, path) == 0)
		{
			return i;
		}
	}
	
	return -1;
}

static FT_Face font_get_face(int fonts_index, char character)
{
	FT_UInt glyph_index = FT_Get_Char_Index(fonts[fonts_index].face, character);
	
	if(glyph_index == 0)
	{
		printf("Failed get character index: Unknown character code.\n");
		return NULL;
	}
	
	if(FT_Load_Glyph(fonts[fonts_index].face, glyph_index, FT_LOAD_NO_BITMAP | FT_LOAD_NO_HINTING | FT_LOAD_IGNORE_TRANSFORM))
	{
		printf("Failed load glyph.\n");
		return NULL;
	}
	
	return fonts[fonts_index].face;
}

void canvas_render_text_fill(char *path, char *text, float x, float y, unsigned int size)
{
	int fonts_index = 0;
	FT_Face face;
	unsigned int text_index = 0;
	// VGPath glyph_path = 0;
	VGfloat offset_x = 0;
	VGfloat color_values[4];
	
	color_values[0] = currentState.fillColor.red;
	color_values[1] = currentState.fillColor.green;
	color_values[2] = currentState.fillColor.blue;
	color_values[3] = currentState.fillColor.alpha * canvas_globalAlpha_get();
	
	if(fonts == NULL)
	{
		return;
	}
	
	fonts_index = font_get(path);
	
	if(fonts_index < 0)
	{
		printf("Failed to find font face: %s\n", path);
		return;
	}
	
	for(text_index = 0; text_index < strlen(text); text_index++)
	{
		face = font_get_face(fonts_index, text[text_index]);
		
		printf("'%c': %f %f\n", text[text_index], ((float)(face->glyph->metrics.vertAdvance) / 64), ((float)(face->glyph->metrics.horiAdvance) / 64));
		
		if(face->glyph->outline.n_contours != 0)
		{
			vgSetParameteri(fillColor, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
			vgSetParameterfv(fillColor, VG_PAINT_COLOR, 4, color_values);
			vgSetPaint(fillColor, VG_FILL_PATH);
			
			vgClearPath(immediatePath, VG_PATH_CAPABILITY_ALL);
			convert_outline(face->glyph->outline.points, face->glyph->outline.tags, face->glyph->outline.contours, face->glyph->outline.n_contours, face->glyph->outline.n_points);
			vgAppendPathData(immediatePath, segments_count, segments, coords);
			vgTranslate(offset_x, 0);
			vgTranslate(x, y);
			vgScale((VGfloat)size / 64, (VGfloat)size / 64);
			vgDrawPath(immediatePath, VG_FILL_PATH);
			vgScale((VGfloat)64 / size, (VGfloat)64 / size);
			vgTranslate(-x, -y);
			vgTranslate(-offset_x, 0);
			
			offset_x += ((float)(face->glyph->metrics.horiAdvance) / 64) * ((float)size / 64);
		}
	}
}

void canvas_render_text_stroke(char *path, char *text, float x, float y, unsigned int size)
{
	int fonts_index = 0;
	FT_Face face;
	unsigned int text_index = 0;
	// VGPath glyph_path = 0;
	VGfloat offset_x = 0;
	VGfloat color_values[4];
	int lineDashPattern_index = 0;
	VGfloat lineDashOffset = currentState.dashOffset;
	VGfloat lineWidth = currentState.lineWidth;
	VGint lineDashCount = currentState.dashCount;
	VGfloat *lineDashPattern = malloc(currentState.dashCount * sizeof(VGfloat));
	VGfloat *lineDashPattern2 = malloc(currentState.dashCount * sizeof(VGfloat));
	if(lineDashPattern == NULL || lineDashPattern2 == NULL)
	{
		printf("Failed to copy dash pattern.\n");
		return;
	}
	
	memcpy(lineDashPattern, currentState.dashPattern, currentState.dashCount * sizeof(VGfloat));
	
	color_values[0] = currentState.strokeColor.red;
	color_values[1] = currentState.strokeColor.green;
	color_values[2] = currentState.strokeColor.blue;
	color_values[3] = currentState.strokeColor.alpha * canvas_globalAlpha_get();
	
	if(fonts == NULL)
	{
		free(lineDashPattern);
		free(lineDashPattern2);
		return;
	}
	
	fonts_index = font_get(path);
	
	if(fonts_index < 0)
	{
		printf("Failed to find font face: %s\n", path);
		free(lineDashPattern);
		free(lineDashPattern2);
		return;
	}
	
	for(text_index = 0; text_index < strlen(text); text_index++)
	{
		face = font_get_face(fonts_index, text[text_index]);
		
		// printf("'%c': %f %f\n", text[text_index], ((float)(face->glyph->metrics.vertAdvance) / 64), ((float)(face->glyph->metrics.horiAdvance) / 64));
		
		if(face->glyph->outline.n_contours != 0)
		{
			for(lineDashPattern_index = 0; lineDashPattern_index < lineDashCount; lineDashPattern_index++)
			{
				lineDashPattern2[lineDashPattern_index] = lineDashPattern[lineDashPattern_index] * ((VGfloat)64 / size);
			}
			
			canvas_setLineDash(lineDashCount, lineDashPattern2);
			canvas_lineWidth(lineWidth * ((VGfloat)64 / size));
			canvas_lineDashOffset(lineDashOffset * ((VGfloat)64 / size));
			
			vgSetParameteri(strokeColor, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
			vgSetParameterfv(strokeColor, VG_PAINT_COLOR, 4, color_values);
			vgSetPaint(strokeColor, VG_STROKE_PATH);
			
			vgClearPath(immediatePath, VG_PATH_CAPABILITY_ALL);
			convert_outline(face->glyph->outline.points, face->glyph->outline.tags, face->glyph->outline.contours, face->glyph->outline.n_contours, face->glyph->outline.n_points);
			vgAppendPathData(immediatePath, segments_count, segments, coords);
			vgTranslate(offset_x, 0);
			vgTranslate(x, y);
			vgScale((VGfloat)size / 64, (VGfloat)size / 64);
			vgDrawPath(immediatePath, VG_STROKE_PATH);
			vgScale((VGfloat)64 / size, (VGfloat)64 / size);
			vgTranslate(-x, -y);
			vgTranslate(-offset_x, 0);
			
			canvas_lineDashOffset(lineDashOffset);
			canvas_lineWidth(lineWidth);
			canvas_setLineDash(lineDashCount, lineDashPattern);
			
			offset_x += ((float)(face->glyph->metrics.horiAdvance) / 64) * ((float)size / 64);
		}
	}
	
	free(lineDashPattern);
	free(lineDashPattern2);
}

void font_init(void)
{
	if(FT_Init_FreeType(&font_library))
	{
		printf("Failed to initialize freetype2. Fonts can't be used.\n");
		return;
	}
	
	printf("Freetype2 initialized.\n");
}

void font_cleanup(void)
{
	printf("Cleaning up fonts...\n");
	
	if(fonts != NULL)
	{
		while(fonts != NULL)
		{
			font_remove(fonts[0].path);
		}
	}
	
	FT_Done_FreeType(font_library);
}

void font_new(char *path)
{
	FT_Error error = 0;
	
	printf("Adding font: %s\n", path);
	
	fonts = realloc(fonts, (++fonts_amount) * sizeof(font_t));
	
	if(fonts == NULL)
	{
		printf("Failed to grow font list.\n");
		return;
	}
	
	fonts[fonts_amount - 1].path = strdup(path);
	
	error = FT_New_Face(font_library, path, 0, &(fonts[fonts_amount - 1].face));
	if(error == FT_Err_Unknown_File_Format)
	{
		printf("Failed to load font face: Unknown file format: %s\n", path);
		font_remove(path);
		return;
	}
	else if(error)
	{
		printf("Failed to load font face: %s (0x%x)\n", path, error);
		font_remove(path);
		return;
	}
	
	if(FT_Set_Char_Size(fonts[fonts_amount - 1].face, 0, 64 * 64, 96, 96))
	{
		printf("Failed to set font size: %s\n", path);
		font_remove(path);
		return;
	}
}

void font_remove(char *path)
{
	int i = 0;
	int fonts_index = 0;
	
	if(fonts == NULL)
	{
		return;
	}
	
	printf("Removing font: %s\n", path);
	
	fonts_index = font_get(path);
	
	if(fonts_index < 0)
	{
		printf("Failed to find font face: %s\n", path);
		return;
	}
	
	free(fonts[fonts_index].path);
	FT_Done_Face(fonts[fonts_index].face);
	
	for(i = fonts_index; i < fonts_amount - 1; i++)
	{
		fonts[i] = fonts[i + 1];
	}
	
	if((--fonts_amount) < 1)
	{
		free(fonts);
		fonts = NULL;
		
		return;
	}
	
	fonts = realloc(fonts, fonts_amount * sizeof(font_t));
	if(fonts == NULL)
	{
		printf("Failed to shrink font list.\n");
		return;
	}
}
