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

#include "egl-util.h"
#include "canvas-beginPath.h"
#include "canvas-quadraticCurveTo.h"

/**
 * The quadraticCurveTo() method adds a quadratic Bézier curve to the path. It
 * requires two points. The first point is a control point and the second one is
 * the end point. The starting point is the last point in the current path,
 * which can be changed using moveTo() before creating the quadratic Bézier
 * curve.
 * @param cpx The x axis of the coordinate for the control point.
 * @param cpy The y axis of the coordinate for the control point.
 * @param x The x axis of the coordinate for the end point.
 * @param y The y axis of the coordinate for the end point.
 */
void canvas_quadraticCurveTo(VGfloat cpx, VGfloat cpy, VGfloat x, VGfloat y)
{
	VGubyte segment[1] = { VG_QUAD_TO_ABS };
	VGfloat data[4];
	
	data[0] = cpx;
	data[1] = egl_get_height() - cpy;
	data[2] = x;
	data[3] = egl_get_height() - y;
	
	vgAppendPathData(canvas_beginPath_get(), 1, segment, (const void *)data);
}
