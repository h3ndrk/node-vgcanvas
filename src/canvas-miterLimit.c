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

#include "canvas-miterLimit.h"

static VGfloat canvas_miterLimit_value = 10;

/**
 * The miterLimit property of the Canvas 2D API sets the miter limit ratio in
 * space units. Setting zero, negative, Infinity and NaN values are ignored;
 * otherwise the current value is set to the new value.
 * @param miter_limit A number specifying the miter limit ratio in space units.
 *                    Zero, negative, Infinity and NaN values are ignored.
 */
void canvas_miterLimit(VGfloat miter_limit)
{
	if(miter_limit > 0)
	{
		canvas_miterLimit_value = miter_limit;
		
		vgSetf(VG_STROKE_MITER_LIMIT, miter_limit);
	}
}

/**
 * It returns the current value (10.0 by default).
 * @return A number specifying the current miter limit.
 */
VGfloat canvas_miterLimit_get(void)
{
	return canvas_miterLimit_value;
}
