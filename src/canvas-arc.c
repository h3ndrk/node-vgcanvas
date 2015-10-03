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
#include "canvas-arc.h"
#include "coordinate-util.h"

/**
 * The arc() method adds an arc to the path which is centered at (x, y) position
 * with radius r starting at startAngle and ending at endAngle going in the
 * given direction by anticlockwise (defaulting to clockwise).
 * @param x The x coordinate of the arc's center.
 * @param y The y coordinate of the arc's center.
 * @param radius The arc's radius.
 * @param start_angle The angle at which the arc starts, measured clockwise from
 *                    the positive x axis and expressed in radians.
 * @param end_angle The angle at which the arc ends, measured clockwise from the
 *                  positive x axis and expressed in radians.
 * @param anticlockwise A Boolean which, if true, causes the arc to be drawn
 *                      counter-clockwise between the two angles.
 */
void canvas_arc(VGfloat x, VGfloat y, VGfloat radius, VGfloat start_angle, VGfloat end_angle, VGboolean anticlockwise)
{
	VGfloat angle_extent = 0;
	
	// dprintf("arc: { x: %i, y: %i, radius: %i, start_angle: %i, end_angle: %i, anticlockwise: %s }\n", x, y, radius, start_angle, end_angle, log_util_booleanToString(anticlockwise));
	
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
	
	vguArc(canvas_beginPath_get(), x, egl_get_height() - y, radius * 2, radius * 2, start_angle, angle_extent, VGU_ARC_OPEN);
}
