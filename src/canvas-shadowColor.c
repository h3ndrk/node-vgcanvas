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

#include "canvas-paint.h"
#include "canvas-shadowColor.h"

static VGboolean canvas_shadowColor_enabled = VG_FALSE;
static paint_t *canvas_shadowColor_paint = NULL;

/**
 * The shadowColor property specifies the color of the shadow.
 * @param paint The shadow color paint.
 */
void canvas_shadowColor(paint_t *paint)
{
	if(paint->paint_type == PAINT_TYPE_COLOR)
	{
		canvas_shadowColor_paint = paint;
		
		// transparent colors result in disabled shadows
		if(canvas_shadowColor_paint->count == 4 && canvas_shadowColor_paint->data[3] == 0)
		{
			canvas_shadowColor_enabled = VG_FALSE;
		}
		else
		{
			canvas_shadowColor_enabled = VG_TRUE;
		}
	}
}

/**
 * Returns the shadow color paint.
 * @return The shadow color paint.
 */
paint_t *canvas_shadowColor_get(void)
{
	return canvas_shadowColor_paint;
}

/**
 * Returns the whether shadows are enabled or not. The value true means shadows
 * are enabled.
 * @return The enabled state.
 */
VGboolean canvas_shadowColor_get_enabled(void)
{
	return canvas_shadowColor_enabled;
}
