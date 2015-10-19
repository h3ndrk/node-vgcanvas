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
// #include "include-freetype.h"

#include "canvas-lineJoin.h"

static VGJoinStyle canvas_lineJoin_value = VG_JOIN_MITER;

/**
 * The lineJoin property determines how two connecting segments (of lines, arcs
 * or curves) with non-zero lengths in a shape are joined together (degenerate
 * segments with zero lengths, whose specified endpoints and control points are
 * exactly at the same position, are skipped).
 * @param line_join A string specifying the style of the join point.
 */
void canvas_lineJoin(char *line_join)
{
	if(!strcmp(line_join, "miter"))
	{
		canvas_lineJoin_value = VG_JOIN_MITER;
		
		vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_MITER);
	}
	else if(!strcmp(line_join, "round"))
	{
		canvas_lineJoin_value = VG_JOIN_ROUND;
		
		vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_ROUND);
	}
	else if(!strcmp(line_join, "bevel"))
	{
		canvas_lineJoin_value = VG_JOIN_BEVEL;
		
		vgSeti(VG_STROKE_JOIN_STYLE, VG_JOIN_BEVEL);
	}
}

/**
 * It returns the current value (butt by default).
 * @return A string specifying the current style of the join point.
 */
char *canvas_lineJoin_get(void)
{
	switch(canvas_lineJoin_value)
	{
		case VG_JOIN_MITER:
		{
			return "miter";
			
			break;
		}
		case VG_JOIN_ROUND:
		{
			return "round";
			
			break;
		}
		case VG_JOIN_BEVEL:
		{
			return "bevel";
			
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
