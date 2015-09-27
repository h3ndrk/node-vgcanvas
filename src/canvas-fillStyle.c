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

#include "canvas-fillStyle.h"

static paint_t *canvas_fillStyle_paint = NULL;

/**
 * The fillStyle property specifies the color or style to use inside shapes.
 * @param paint The fill style paint.
 */
void canvas_fillStyle(paint_t *paint)
{
	canvas_fillStyle_paint = paint;
}

/**
 * Returns the fill style paint.
 * @return The fill style paint.
 */
paint_t *canvas_fillStyle_get(void)
{
	return canvas_fillStyle_paint;
}
