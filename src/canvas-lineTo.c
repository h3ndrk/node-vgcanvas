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

#include "include-core.h"
#include "include-openvg.h"
// #include "include-freetype.h"
#include "canvas-beginPath.h"
#include "canvas-moveTo.h"

/**
 * The lineTo() method connects the last point in the sub-path to the x, y
 * coordinates with a straight line (but does not actually draw it).
 * @param x The x axis of the coordinate for the end of the line.
 * @param y The y axis of the coordinate for the end of the line.
 */
void canvas_lineTo(VGfloat x, VGfloat y)
{
	VGubyte segment[1] = { VG_LINE_TO_ABS };
	VGfloat data[2];
	
	data[0] = x;
	data[1] = y;
	
	vgAppendPathData(canvas_beginPath_get(), 1, segment, (const void *)data);
}
