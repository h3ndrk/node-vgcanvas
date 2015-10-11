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

#include "egl-util.h"
#include "canvas-beginPath.h"
#include "canvas-paint.h"
#include "canvas-strokeStyle.h"
#include "canvas-stroke.h"

/**
 * The stroke() method fills the current or given path with the current stroke
 * style using the non-zero or even-odd winding rule.
 */
void canvas_stroke(void)
{
	paint_activate(canvas_strokeStyle_get(), VG_STROKE_PATH);
	
	vgDrawPath(canvas_beginPath_get(), VG_STROKE_PATH);
}
