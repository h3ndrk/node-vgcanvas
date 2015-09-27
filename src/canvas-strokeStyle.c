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

#include "canvas-strokeStyle.h"

static paint_t *canvas_strokeStyle_paint = NULL;

/**
 * The strokeStyle property specifies the color or style to use inside shapes.
 * @param paint The stroke style paint.
 */
void canvas_strokeStyle(paint_t *paint)
{
	canvas_strokeStyle_paint = paint;
}

/**
 * Returns the stroke style paint.
 * @return The stroke style paint.
 */
paint_t *canvas_strokeStyle_get(void)
{
	return canvas_strokeStyle_paint;
}
