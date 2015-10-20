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

#include "include-core.h"
#include "include-openvg.h"

#include "log-util.h"
#include "egl-util.h"
#include "canvas-paint.h"
#include "canvas-globalAlpha.h"

/**
 * Creates a new RGBA color paint
 *
 * @param paint Pointer to paint struct
 * @param red Red component (0..1)
 * @param green Green component (0..1)
 * @param blue Blue component (0..1)
 * @param alpha Alpha component (0..1)
 */
void paint_createColor(paint_t *paint, VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha)
{
	paint->paint_type = PAINT_TYPE_COLOR;
	paint->count = 0;
	paint->data = NULL;
	
	paint->paint = vgCreatePaint();
	vgSetParameteri(paint->paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	
	paint_setRGBA(paint, red, green, blue, alpha);
}

/**
 * Creates a new linear gradient paint
 *
 * @param paint Pointer to paint struct
 * @param x1 The x axis of the coordinate of the start point
 * @param y1 The y axis of the coordinate of the start point
 * @param x2 The x axis of the coordinate of the end point
 * @param y2 The y axis of the coordinate of the end point
 */
void paint_createLinearGradient(paint_t *paint, VGfloat x1, VGfloat y1, VGfloat x2, VGfloat y2)
{
	VGfloat data[4];
	
	paint->paint_type = PAINT_TYPE_LINEAR_GRADIENT;
	paint->count = 0;
	paint->data = NULL;
	
	data[0] = x1;
	data[1] = egl_get_height() - y1;
	data[2] = x2;
	data[3] = egl_get_height() - y2;
	
	paint->paint = vgCreatePaint();
	
	vgSetParameteri(paint->paint, VG_PAINT_TYPE, VG_PAINT_TYPE_LINEAR_GRADIENT);
	vgSetParameterfv(paint->paint, VG_PAINT_LINEAR_GRADIENT, 4, data);
}

/**
 * Creates a new linear gradient paint
 *
 * @param paint Pointer to paint struct
 * @param cx The x axis of the coordinate of the start circle
 * @param cy The y axis of the coordinate of the start circle
 * @param r The radius of the start circle
 * @param fx The x axis of the coordinate of the end circle
 * @param fy The y axis of the coordinate of the end circle
 */
void paint_createRadialGradient(paint_t *paint, VGfloat cx, VGfloat cy, VGfloat r, VGfloat fx, VGfloat fy)
{
	VGfloat data[5];
	
	paint->paint_type = PAINT_TYPE_RADIAL_GRADIENT;
	paint->count = 0;
	paint->data = NULL;
	
	data[0] = cx;
	data[1] = egl_get_height() - cy;
	data[2] = fx;
	data[3] = egl_get_height() - fy;
	data[4] = r;
	
	paint->paint = vgCreatePaint();
	
	vgSetParameteri(paint->paint, VG_PAINT_TYPE, VG_PAINT_TYPE_RADIAL_GRADIENT);
	vgSetParameterfv(paint->paint, VG_PAINT_RADIAL_GRADIENT, 5, data);
}

/**
 * Creates a new pattern paint.
 *
 * @param paint Pointer to paint struct
 * @param img Pointer to image
 * @param mode The VGTilingMode (no-repeat, repeat)
 */
void paint_createPattern(paint_t *paint, image_t *img, VGTilingMode mode)
{
	paint->paint_type = PAINT_TYPE_PATTERN;
	paint->count = 0;
	paint->data = NULL;
	
	paint->paint = vgCreatePaint();
	vgSetParameteri(paint->paint, VG_PAINT_TYPE, VG_PAINT_TYPE_PATTERN);
	vgSetParameteri(paint->paint, VG_PAINT_PATTERN_TILING_MODE, mode);
	vgPaintPattern(paint->paint, img->image);
	
}

/**
 * Destroys a paint. Deallocates memory and releases the OpenVG paint.
 *
 * @param paint Pointer to paint struct
 */
void paint_cleanup(paint_t *paint)
{
	if(paint->data)
	{
		free(paint->data);
	}
	
	vgDestroyPaint(paint->paint);
}

/**
 * Sets RGBA values of a color paint. Expects the paint type to be
 * PAINT_TYPE_COLOR.
 *
 * @param paint Pointer to paint struct
 * @param red Red component (0..1)
 * @param green Green component (0..1)
 * @param blue Blue component (0..1)
 * @param alpha Alpha component (0..1)
 */
void paint_setRGBA(paint_t *paint, VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha)
{
	VGfloat *paint_data_backup = NULL;
	
	if(paint->paint_type != PAINT_TYPE_COLOR)
	{
		eprintf("Failed to set color of paint: paint is a gradient.\n");
		
		return;
	}
	
	paint->count = 4;
	paint_data_backup = paint->data;
	paint->data = realloc(paint->data, 4 * sizeof(VGfloat));
	
	if(paint->data == NULL)
	{
		eprintf("Failed to reallocate color data of paint.\n");
		
		paint->data = paint_data_backup;
		
		return;
	}
	
	paint->data[0] = red;
	paint->data[1] = green;
	paint->data[2] = blue;
	paint->data[3] = alpha;
}

/**
 * Adds a color stop to a gradient paint. Expects the paint type to be
 * PAINT_TYPE_LINEAR_GRADIENT or PAINT_TYPE_RADIAL_GRADIENT.
 *
 * @param paint Pointer to paint struct
 * @param position Position of the point (0..1)
 * @param red Red component (0..1)
 * @param green Green component (0..1)
 * @param blue Blue component (0..1)
 * @param alpha Alpha component (0..1)
 */
void paint_addColorStop(paint_t *paint, VGfloat position, VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha)
{
	VGfloat *paint_data_backup = NULL;
	
	if(paint->paint_type != PAINT_TYPE_LINEAR_GRADIENT && paint->paint_type != PAINT_TYPE_RADIAL_GRADIENT)
	{
		eprintf("Failed to add stop color to paint: paint is not a gradient.\n");
		
		return;
	}
	
	paint->count += 5;
	paint_data_backup = paint->data;
	paint->data = realloc(paint->data, paint->count * sizeof(VGfloat));
	
	if(paint->data == NULL)
	{
		eprintf("Failed to reallocate color data for gradient.\n");
		
		paint->data = paint_data_backup;
		
		return;
	}
	
	paint->data[paint->count - 5] = position;
	paint->data[paint->count - 4] = red;
	paint->data[paint->count - 3] = green;
	paint->data[paint->count - 2] = blue;
	paint->data[paint->count - 1] = alpha;
}

/**
 * Activates the paint. Multiplies alpha values by globalAlpha and sets the
 * paint of the specified modes.
 * 
 * @param paint Pointer to paint struct
 * @param mode bitwise OR of {VG_FILL_PATH | VG_STROKE_PATH}
 */
void paint_activate(paint_t *paint, VGbitfield mode)
{
	VGfloat data_paint[4];
	VGfloat *data_gradient = NULL;
	int i = 0;
	
	switch(paint->paint_type)
	{
		case PAINT_TYPE_COLOR:
		{
			memcpy(data_paint, paint->data, 4 * sizeof(VGfloat));
			
			data_paint[3] *= canvas_globalAlpha_get();
			
			vgSetParameterfv(paint->paint, VG_PAINT_COLOR, 4, data_paint);
			
			break;
		}
		case PAINT_TYPE_LINEAR_GRADIENT:
		case PAINT_TYPE_RADIAL_GRADIENT:
		{
			if(paint->count % 5 != 0)
			{
				eprintf("Failed to activate gradient paint: gradient data is misaligned.\n");
				
				return;
			}
			
			data_gradient = malloc(paint->count * sizeof(VGfloat));
			if(data_gradient == NULL)
			{
				eprintf("Failed to allocate color data for gradient.\n");
				
				return;
			}
			
			memcpy(data_gradient, paint->data, paint->count * sizeof(VGfloat));
			
			for(i = 4; i < paint->count; i += 5)
			{
				data_gradient[i] *= canvas_globalAlpha_get();
			}
			
			vgSetParameterfv(paint->paint, VG_PAINT_COLOR_RAMP_STOPS, paint->count, data_gradient);
			vgSetParameteri(paint->paint, VG_PAINT_COLOR_RAMP_SPREAD_MODE, VG_COLOR_RAMP_SPREAD_PAD);
			vgSetParameteri(paint->paint, VG_PAINT_COLOR_RAMP_PREMULTIPLIED, VG_FALSE);
			
			free(data_gradient);
			
			break;
		}
		case PAINT_TYPE_PATTERN:
		
			break;
	}
	
	vgSetPaint(paint->paint, mode);
}
