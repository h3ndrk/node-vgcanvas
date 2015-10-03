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
#include "canvas-clearRect.h"

/**
 * Initializes clearRect(). Sets the clear color and disables scissoring.
 */
void canvas_clearRect_init(void)
{
	VGfloat clear_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // white
	vgSetfv(VG_CLEAR_COLOR, 4, clear_color);

	vgSeti(VG_SCISSORING, VG_FALSE);
	
	canvas_clearRect(0, 0, egl_get_width(), egl_get_height());
}

/**
 * The method sets all pixels in the rectangle defined by starting point
 * (x, y) and size (width, height) to transparent black, erasing any previously
 * drawn content.
 * @param x The x axis of the coordinate for the rectangle starting point.
 * @param y The y axis of the coordinate for the rectangle starting point.
 * @param width The rectangle's width.
 * @param height The rectangle's height.
 */
void canvas_clearRect(VGfloat x, VGfloat y, VGfloat width, VGfloat height)
{
	vgClear(x, egl_get_height() - y - height, width, height);
}
