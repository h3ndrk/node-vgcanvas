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

#include "canvas-shadowBlur.h"

static VGfloat canvas_shadowBlur_value = 0;

/**
 * The shadowBlur property specifies the level of the blurring effect; this
 * value doesn't correspond to a number of pixels and is not affected by the
 * current transformation matrix. The default value is 0. The value is limited
 * to the maximum value of gaussian blur deviation of the graphics card.
 * @param shadow_blur A float specifying the level of the blurring effect. The
 *                    default value is 0. Negative values are ignored. The value
 *                    will be clamped to the maximum gaussian blur deviation of
 *                    the graphics card if it is greater than that maximum
 *                    value.
 */
void canvas_shadowBlur(VGfloat shadow_blur)
{
	VGfloat max_blur = vgGetf(VG_MAX_GAUSSIAN_STD_DEVIATION);
	
	shadow_blur /= 2;
	
	if(shadow_blur > 0)
	{
		if(shadow_blur > max_blur)
		{
			canvas_shadowBlur_value = max_blur;
		}
		else
		{
			canvas_shadowBlur_value = shadow_blur;
		}
	}
}

/**
 * It returns the current value (0.0 by default).
 * @return A number specifying the current shadow blur in space units.
 */
VGfloat canvas_shadowBlur_get(void)
{
	return canvas_shadowBlur_value;
}
