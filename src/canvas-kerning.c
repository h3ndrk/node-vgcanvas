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

#include "canvas-kerning.h"

static VGboolean canvas_kerning_value = VG_TRUE;

/**
 * The kerning property specifies whether all following text renderings should
 * use font kerning. If the font does not support font kerning the kerning
 * property will be ignored.
 * @param kerning A boolean which should be true if font kerning should be used.
 */
void canvas_kerning(VGboolean kerning)
{
	canvas_kerning_value = kerning;
}

/**
 * It returns the current value (true by default).
 * @return A boolean value specifying the current kerning property.
 */
VGboolean canvas_kerning_get(void)
{
	return canvas_kerning_value;
}
