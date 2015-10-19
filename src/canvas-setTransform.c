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

#include "egl-util.h"
#include "canvas-setTransform.h"

/**
 * The setTransform() method resets (overrides) the current transformation to
 * the identity matrix and then invokes a transformation described by the
 * arguments of this method.
 *
 * See also the transform() method, which does not override the current
 * transform matrix and multiplies it with a given one.
 * @param a (m11) Horizontal scaling.
 * @param b (m12) Horizontal skewing.
 * @param c (m21) Vertical skewing.
 * @param d (m22) Vertical scaling.
 * @param e (dx) Horizontal moving.
 * @param f (dy) Vertical moving.
 */
void canvas_setTransform(VGfloat a, VGfloat b, VGfloat c, VGfloat d, VGfloat e, VGfloat f)
{
	VGfloat matrix[9];
	
	// a (m11): Horizontal scaling.
	// b (m12): Horizontal skewing.
	// c (m21): Vertical skewing.
	// d (m22): Vertical scaling.
	// e (dx):  Horizontal moving.
	// f (dy):  Vertical moving.
	
	// | a c e |
	// | b d f |
	// | 0 0 1 |
	
	// -> [ a, b, 0, c, d, 0, e, f, 1 ]
	
	matrix[0] = a;
	matrix[1] = -b;
	matrix[2] = 0;
	matrix[3] = -c;
	matrix[4] = d;
	matrix[5] = 0;
	matrix[6] = e;
	matrix[7] = -f;
	matrix[8] = 1;
	
	vgTranslate(0, egl_get_height());
	
	vgLoadMatrix(matrix);
	
	vgTranslate(0, -egl_get_height());
}
