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
#include "canvas-lineDashOffset.h"

static VGfloat canvas_lineDashOffset_value = 0;

/**
 * The lineDashOffset property sets the line dash pattern offset or "phase" to
 * achieve a "marching ants" effect, for example.
 * @param line_dash_offset A float specifying the amount of the offset. Initially 0.0.
 */
void canvas_lineWidth(VGfloat line_dash_offset)
{
	canvas_lineDashOffset_value = line_dash_offset;
	
	vgSetf(VG_STROKE_DASH_PHASE, line_dash_offset);
}

/**
 * It returns the current value (0.0 by default).
 * @return A number specifying the current line dash offset in space units.
 */
VGfloat canvas_lineWidth_get(void)
{
	return canvas_lineDashOffset_value;
}
