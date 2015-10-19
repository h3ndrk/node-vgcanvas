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

#include "canvas-scale.h"

/**
 * The scale() method adds a scaling transformation to the canvas units by x
 * horizontally and by y vertically.
 * 
 * By default, one unit on the canvas is exactly one pixel. If we apply, for
 * instance, a scaling factor of 0.5, the resulting unit would become 0.5 pixels
 * and so shapes would be drawn at half size. In a similar way setting the
 * scaling factor to 2.0 would increase the unit size and one unit now becomes
 * two pixels. This results in shapes being drawn twice as large.
 * @param x Scaling factor in the horizontal direction.
 * @param y Scaling factor in the vertical direction.
 */
void canvas_scale(VGfloat x, VGfloat y)
{
	vgScale(x, y);
}
