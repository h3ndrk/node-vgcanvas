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

#include "include-core.h"
#include "include-openvg.h"
// #include "include-freetype.h"

#include "canvas-globalCompositeOperation.h"

static VGBlendMode canvas_globalCompositeOperation_value = VG_BLEND_SRC;

/**
 * The globalCompositeOperation property sets the type of compositing operation
 * to apply when drawing new shapes, where type is a string identifying which of
 * the compositing or blending mode operations to use.
 * @param global_composite_operation A string specifying the composite
 *                                   operation.
 */
void canvas_globalCompositeOperation(char *global_composite_operation)
{
	if(!strcmp(global_composite_operation, "source-atop") || !strcmp(global_composite_operation, "source-out") || !strcmp(global_composite_operation, "copy") || !strcmp(global_composite_operation, "xor"))
	{
		canvas_globalCompositeOperation_value = VG_BLEND_SRC;
		
		vgSeti(VG_BLEND_MODE, VG_BLEND_SRC);
	}
	else if(!strcmp(global_composite_operation, "source-in"))
	{
		canvas_globalCompositeOperation_value = VG_BLEND_SRC_IN;
		
		vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_IN);
	}
	else if(!strcmp(global_composite_operation, "source-over"))
	{
		canvas_globalCompositeOperation_value = VG_BLEND_SRC_OVER;
		
		vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);
	}
	else if(!strcmp(global_composite_operation, "destination-in") || !strcmp(global_composite_operation, "destination-atop") || !strcmp(global_composite_operation, "destination-out"))
	{
		canvas_globalCompositeOperation_value = VG_BLEND_DST_IN;
		
		vgSeti(VG_BLEND_MODE, VG_BLEND_DST_IN);
	}
	else if(!strcmp(global_composite_operation, "destination-over"))
	{
		canvas_globalCompositeOperation_value = VG_BLEND_DST_OVER;
		
		vgSeti(VG_BLEND_MODE, VG_BLEND_DST_OVER);
	}
	else if(!strcmp(global_composite_operation, "lighter"))
	{
		canvas_globalCompositeOperation_value = VG_BLEND_LIGHTEN;
		
		vgSeti(VG_BLEND_MODE, VG_BLEND_LIGHTEN);
	}
	else if(!strcmp(global_composite_operation, "vg-multiply"))
	{
		canvas_globalCompositeOperation_value = VG_BLEND_MULTIPLY;
		
		vgSeti(VG_BLEND_MODE, VG_BLEND_MULTIPLY);
	}
	else if(!strcmp(global_composite_operation, "vg-screen"))
	{
		canvas_globalCompositeOperation_value = VG_BLEND_SCREEN;
		
		vgSeti(VG_BLEND_MODE, VG_BLEND_SCREEN);
	}
	else if(!strcmp(global_composite_operation, "vg-darker"))
	{
		canvas_globalCompositeOperation_value = VG_BLEND_DARKEN;
		
		vgSeti(VG_BLEND_MODE, VG_BLEND_DARKEN);
	}
	else if(!strcmp(global_composite_operation, "vg-additive"))
	{
		canvas_globalCompositeOperation_value = VG_BLEND_ADDITIVE;
		
		vgSeti(VG_BLEND_MODE, VG_BLEND_ADDITIVE);
	}
}

/**
 * It returns the current value (source-atop by default).
 * @return A string specifying the current composite operation.
 */
char *canvas_globalCompositeOperation_get(void)
{
	switch(canvas_globalCompositeOperation_value)
	{
		case VG_BLEND_SRC:
		{
			return "source-atop";
			
			break;
		}
		case VG_BLEND_SRC_IN:
		{
			return "source-in";
			
			break;
		}
		case VG_BLEND_SRC_OVER:
		{
			return "source-over";
			
			break;
		}
		case VG_BLEND_DST_IN:
		{
			return "destination-in";
			
			break;
		}
		case VG_BLEND_DST_OVER:
		{
			return "destination-over";
			
			break;
		}
		case VG_BLEND_LIGHTEN:
		{
			return "lighter";
			
			break;
		}
		case VG_BLEND_MULTIPLY:
		{
			return "vg-multiply";
			
			break;
		}
		case VG_BLEND_SCREEN:
		{
			return "vg-screen";
			
			break;
		}
		case VG_BLEND_DARKEN:
		{
			return "vg-darker";
			
			break;
		}
		case VG_BLEND_ADDITIVE:
		{
			return "vg-additive";
			
			break;
		}
		default:
		{
			return "";
			
			break;
		}
	}
	
	return "";
}
