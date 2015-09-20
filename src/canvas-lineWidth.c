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
#include "canvas-lineWidth.h"

static VGfloat canvas_lineWidth_value = 1;

/**
 * The lineWidth property sets the thickness of lines in space units. Setting
 * zero and negative values are ignored; otherwise the current value is set to
 * the new value.
 * @param lineWidth A number specifying the line width in space units. Zero,
 *                  negative, Infinity and NaN values are ignored.
 */
void canvas_lineWidth(VGfloat line_width)
{
	if(line_width > 0)
	{
		canvas_lineWidth_value = line_width;
		
		vgSetf(VG_STROKE_LINE_WIDTH, line_width);
	}
}

/**
 * It returns the current value (1.0 by default).
 * @return A number specifying the current line width in space units.
 */
VGfloat canvas_lineWidth_get(void)
{
	return canvas_lineWidth_value;
}
