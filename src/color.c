/**
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

#include <VG/openvg.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include "color.h"
#include "canvas.h"

void paint_createColor(paint_t *paint, float red, float green, float blue, float alpha)
{
	paint->paintType = PAINT_TYPE_COLOR;
	paint->count = 0;
	paint->data = NULL;
	
	paint->paint = vgCreatePaint();
	vgSetParameteri(paint->paint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
	
	paint_setRGBA(paint, red, green, blue, alpha);
}

void paint_createLinearGradient(paint_t *paint, float x1, float y1, float x2, float y2)
{
	paint->paintType = PAINT_TYPE_LINEAR_GRADIENT;
	paint->count = 0;
	paint->data = NULL;
	
	VGfloat params[4] = {x1, y1, x2, y2};
	
	paint->paint = vgCreatePaint();
	vgSetParameteri(paint->paint, VG_PAINT_TYPE, VG_PAINT_TYPE_LINEAR_GRADIENT);
	vgSetParameterfv(paint->paint, VG_PAINT_LINEAR_GRADIENT, 4, params);
	
}

void paint_destroy(paint_t *paint)
{
	if(paint->data)
	{
		free(paint->data);
	}
	
	vgDestroyPaint(paint->paint);
}

void paint_setRGBA(paint_t *paint, VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha)
{
	assert(paint->paintType == PAINT_TYPE_COLOR);
	
	paint->count = 4;
	paint->data = realloc(paint->data, 4 * sizeof(VGfloat));
	if(!paint->data)
	{
		printf("realloc failed\n");
		exit(1);
	}
	
	paint->data[0] = red;
	paint->data[1] = green;
	paint->data[2] = blue;
	paint->data[3] = alpha;
	
}

void paint_addColorStop(paint_t *paint, VGfloat position, VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha)
{
	assert(paint->paintType == PAINT_TYPE_LINEAR_GRADIENT);
	
	paint->count += 5;
	paint->data = realloc(paint->data, paint->count * sizeof(VGfloat));
	if(!paint->data)
	{
		printf("realloc failed\n");
		exit(1);
	}
	
	paint->data[paint->count - 5] = position;
	paint->data[paint->count - 4] = red;
	paint->data[paint->count - 3] = green;
	paint->data[paint->count - 2] = blue;
	paint->data[paint->count - 1] = alpha;
	
}

void paint_activate(paint_t *paint, VGbitfield mode)
{
	switch(paint->paintType) {
		case PAINT_TYPE_COLOR:
		{
			VGfloat data[4];
			memcpy(data, paint->data, 4 * sizeof(VGfloat));
			
			data[3] *= canvas_getState()->globalAlpha;
			
			vgSetParameterfv(paint->paint, VG_PAINT_COLOR, 4, data);
		
			break;
		}
		case PAINT_TYPE_LINEAR_GRADIENT:
		{
			assert(paint->count % 5 == 0);
		
			VGfloat data[paint->count];
			memcpy(data, paint->data, paint->count * sizeof(VGfloat));
			
			for(int i = 4; i < paint->count; i += 5) {
				data[i] *= canvas_getState()->globalAlpha;
			}
			
			vgSetParameterfv(paint->paint, VG_PAINT_COLOR_RAMP_STOPS, paint->count, data);
			vgSetParameteri(paint->paint, VG_PAINT_COLOR_RAMP_SPREAD_MODE, VG_COLOR_RAMP_SPREAD_REPEAT);
			vgSetParameteri(paint->paint, VG_PAINT_COLOR_RAMP_PREMULTIPLIED, VG_FALSE);
			break;
		}
	}
	
	vgSetPaint(paint->paint, mode);
}
