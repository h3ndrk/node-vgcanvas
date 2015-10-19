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

#include "egl-util.h"
#include "canvas-beginPath.h"
#include "canvas-quadraticCurveTo.h"

/**
 * The bezierCurveTo() method of the Canvas 2D API adds a cubic Bézier curve to
 * the path. It requires three points. The first two points are control points
 * and the third one is the end point. The starting point is the last point in
 * the current path, which can be changed using moveTo() before creating the
 * Bézier curve.
 * @param cp1x The x axis of the coordinate for the first control point.
 * @param cp1y The y axis of the coordinate for the first control point.
 * @param cp2x The x axis of the coordinate for the second control point.
 * @param cp2y The y axis of the coordinate for the second control point.
 * @param x The x axis of the coordinate for the end point.
 * @param y The y axis of the coordinate for the end point.
 */
void canvas_bezierCurveTo(VGfloat cp1x, VGfloat cp1y, VGfloat cp2x, VGfloat cp2y, VGfloat x, VGfloat y)
{
	VGubyte segment[1] = { VG_CUBIC_TO_ABS };
	VGfloat data[6];
	
	data[0] = cp1x;
	data[1] = egl_get_height() - cp1y;
	data[2] = cp2x;
	data[3] = egl_get_height() - cp2y;
	data[4] = x;
	data[5] = egl_get_height() - y;
	
	vgAppendPathData(canvas_beginPath_get(), 1, segment, (const void *)data);
}
