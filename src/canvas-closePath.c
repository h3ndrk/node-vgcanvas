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

#include "canvas-beginPath.h"
#include "canvas-closePath.h"

/**
 * The closePath() method causes the point of the pen to move back to the start
 * of the current sub-path. It tries to add a straight line (but does not
 * actually draw it) from the current point to the start. If the shape has
 * already been closed or has only one point, this function does nothing.
 */
void canvas_closePath(void)
{
	VGubyte segment[1] = { VG_CLOSE_PATH };
	VGfloat data[2];
	
	data[0] = 0;
	data[1] = 0;
	
	vgAppendPathData(canvas_beginPath_get(), 1, segment, (const void *)data);
}
