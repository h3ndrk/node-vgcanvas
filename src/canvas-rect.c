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
#include "canvas-rect.h"

/**
 * The rect() method creates a path for a rectangle at position (x, y) with a
 * size that is determined by width and height. Those four points are connected
 * by straight lines and the sub-path is marked as closed, so that you can fill
 * or stroke this rectangle.
 * @param x The x axis of the coordinate for the rectangle starting point.
 * @param y The y axis of the coordinate for the rectangle starting point.
 * @param width The rectangle's width.
 * @param height The rectangle's height.
 */
void canvas_rect(VGfloat x, VGfloat y, VGfloat width, VGfloat height)
{
	vguRect(canvas_beginPath_get(), x, egl_get_height() - y - height, width, height);
}
