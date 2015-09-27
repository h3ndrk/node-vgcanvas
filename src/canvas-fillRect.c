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

#include "canvas-paint.h"
#include "canvas-fillStyle.h"
#include "canvas-beginPath.h"
#include "canvas-fillRect.h"

/**
 * The fillRect() method draws a filled rectangle at (x, y) position whose size
 * is determined by width and height and whose style is determined by the
 * fillStyle attribute.
 * @param x The x axis of the coordinate for the rectangle starting point.
 * @param y The y axis of the coordinate for the rectangle starting point.
 * @param width The rectangle's width.
 * @param height The rectangle's height.
 */
void canvas_fillRect(VGfloat x, VGfloat y, VGfloat width, VGfloat height)
{
	paint_activate(canvas_fillStyle_get(), VG_FILL_PATH);

	canvas_beginPath();
	
	vguRect(canvas_beginPath_get(), x, y, width, height);
	
	vgDrawPath(canvas_beginPath_get(), VG_FILL_PATH);
}
