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
#include "canvas-strokeRect.h"
#include "canvas-shadowColor.h"
#include "canvas-shadowBlur.h"
#include "canvas-shadowOffsetX.h"
#include "canvas-shadowOffsetY.h"
#include "canvas-clearRect.h"
#include "canvas-lineWidth.h"
#include "canvas-lineCap.h"
#include "canvas-lineDashOffset.h"
#include "canvas-miterLimit.h"
#include "canvas-lineJoin.h"
#include "canvas-globalAlpha.h"
#include "canvas-setLineDash.h"
#include "canvas-save.h"
#include "canvas-beginPath.h"
#include "canvas-clip.h"
#include "canvas-fillStyle.h"
#include "canvas-kerning.h"

/**
 * The strokeRect() method paints a rectangle which has a starting point at (x,
 * y) and has a w width and an h height onto the canvas, using the current
 * stroke style.
 * @param x The x axis of the coordinate for the rectangle starting point.
 * @param y The y axis of the coordinate for the rectangle starting point.
 * @param width The rectangle's width.
 * @param height The rectangle's height.
 */
void canvas_strokeRect(VGfloat x, VGfloat y, VGfloat width, VGfloat height)
{
	if(canvas_shadowColor_get_enabled())
	{
		egl_blur_begin();
		
		canvas_globalAlpha(canvas_globalAlpha_get());
		canvas_lineCap(canvas_lineCap_get());
		canvas_lineDashOffset(canvas_lineDashOffset_get());
		canvas_lineJoin(canvas_lineJoin_get());
		canvas_lineWidth(canvas_lineWidth_get());
		// canvas_setLineDash(0, NULL);
		canvas_miterLimit(canvas_miterLimit_get());
		canvas_kerning(canvas_kerning_get());
		
		paint_activate(canvas_shadowColor_get(), VG_STROKE_PATH);
		
		canvas_beginPath();
		
		vguRect(canvas_beginPath_get(), x, egl_get_height() - y - height, width, height);
		
		vgDrawPath(canvas_beginPath_get(), VG_STROKE_PATH);
		
		egl_blur_end(canvas_shadowBlur_get(), canvas_shadowOffsetX_get(), canvas_shadowOffsetY_get());
	}
	
	paint_activate(canvas_strokeStyle_get(), VG_STROKE_PATH);
	
	canvas_beginPath();
	
	vguRect(canvas_beginPath_get(), x, egl_get_height() - y - height, width, height);
	
	vgDrawPath(canvas_beginPath_get(), VG_STROKE_PATH);
}
