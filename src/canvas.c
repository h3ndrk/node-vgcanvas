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
#include "include-freetype.h"

#include "egl-util.h"
#include "canvas.h"
#include "canvas-paint.h"
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
#include "canvas-strokeStyle.h"
#include "font-util.h"

void canvas__init(void)
{
	font_util_init();
	egl_init();
	
	paint_t *fill = malloc(sizeof(paint_t));
	paint_t *stroke = malloc(sizeof(paint_t));
	paint_createColor(fill, 0, 0, 0, 1);
	canvas_fillStyle(fill);
	paint_createColor(stroke, 0, 0, 0, 1);
	canvas_strokeStyle(stroke);
	
	// initialize immediate path, clipping mask and clearing rectangle
	canvas_beginPath_init();
	canvas_clip_init();
	canvas_clearRect_init();
	
	// initialize values
	canvas_globalAlpha(canvas_globalAlpha_get());
	canvas_lineCap(canvas_lineCap_get());
	canvas_lineDashOffset(canvas_lineDashOffset_get());
	canvas_lineJoin(canvas_lineJoin_get());
	canvas_lineWidth(canvas_lineWidth_get());
	canvas_setLineDash(0, NULL);
	canvas_miterLimit(canvas_miterLimit_get());
}

void canvas__cleanup(void)
{
	canvas_beginPath_cleanup();
	canvas_setLineDash_cleanup();
	canvas_save_cleanup();
	
	egl_cleanup();
	
	font_util_cleanup();
}
