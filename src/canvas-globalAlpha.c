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
#include "canvas-globalAlpha.h"

static VGfloat canvas_globalAlpha_value = 1;

/**
 * The globalAlpha property specifies the alpha value that is applied to shapes
 * and images before they are drawn onto the canvas. The value is in the range
 * from 0.0 (fully transparent) to 1.0 (fully opaque)
 * @param global_alpha A number between 0.0 (fully transparent) and 1.0 (fully
 *                    opaque). The default value is 1.0 Values outside the
 *                    range, including Infinity and NaN will not be set and
 *                    globalAlpha will retain its previous value.
 */
void canvas_globalAlpha(VGfloat global_alpha)
{
	if(global_alpha >= 0 && global_alpha <= 1)
	{
		canvas_globalAlpha_value = global_alpha;
	}
}

/**
 * It returns the current value (1.0 by default).
 * @return A number specifying the current globalAlpha property.
 */
VGfloat canvas_globalAlpha_get(void)
{
	return canvas_globalAlpha_value;
}
