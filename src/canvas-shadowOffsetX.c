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

#include "canvas-shadowOffsetX.h"

static VGfloat canvas_shadowOffsetX_value = 0;

/**
 * The shadowOffsetX property specifies the distance that the shadow will be
 * offset in horizontal distance.
 * @param shadow_offset_x A float specifying the distance that the shadow will
 *                        be offset in horizontal distance. The default value is
 *                        0. (In difference to the Canvas 2D API negative values
 *                        are allowed.)
 */
void canvas_shadowOffsetX(VGfloat shadow_offset_x)
{
	canvas_shadowOffsetX_value = shadow_offset_x;
}

/**
 * It returns the current value (0.0 by default).
 * @return A number specifying the current shadow offset of the x axis in space
 *         units.
 */
VGfloat canvas_shadowOffsetX_get(void)
{
	return canvas_shadowOffsetX_value;
}
