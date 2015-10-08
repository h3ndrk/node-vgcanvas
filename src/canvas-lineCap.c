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

#include "canvas-lineCap.h"

static VGCapStyle canvas_lineCap_value = VG_CAP_BUTT;

/**
 * The lineCap property determines how the end points of every line are drawn.
 * There are three possible values for this property and those are: butt, round
 * and square. By default this property is set to butt.
 * @param line_cap A string specifying the style of the end point.
 */
void canvas_lineCap(char *line_cap)
{
	if(!strcmp(line_cap, "butt"))
	{
		canvas_lineCap_value = VG_CAP_BUTT;
		
		vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_BUTT);
	}
	else if(!strcmp(line_cap, "round"))
	{
		canvas_lineCap_value = VG_CAP_ROUND;
		
		vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_ROUND);
	}
	else if(!strcmp(line_cap, "square"))
	{
		canvas_lineCap_value = VG_CAP_SQUARE;
		
		vgSeti(VG_STROKE_CAP_STYLE, VG_CAP_SQUARE);
	}
}

/**
 * It returns the current value (butt by default).
 * @return A string specifying the current style of the end point.
 */
char *canvas_lineCap_get(void)
{
	switch(canvas_lineCap_value)
	{
		case VG_CAP_BUTT:
		{
			return "butt";
			
			break;
		}
		case VG_CAP_ROUND:
		{
			return "round";
			
			break;
		}
		case VG_CAP_SQUARE:
		{
			return "square";
			
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
