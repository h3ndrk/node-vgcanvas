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
#include "include-freetype.h"

#include "egl-util.h"
#include "font-util.h"
#include "canvas-beginPath.h"
#include "canvas-bezierCurveTo.h"
#include "canvas-clearRect.h"
#include "canvas-globalAlpha.h"
#include "canvas-lineCap.h"
#include "canvas-lineDashOffset.h"
#include "canvas-lineJoin.h"
#include "canvas-lineTo.h"
#include "canvas-lineWidth.h"
#include "canvas-moveTo.h"
#include "canvas-quadraticCurveTo.h"
#include "canvas-arc.h"
#include "canvas-rect.h"
#include "canvas-setLineDash.h"
#include "canvas-closePath.h"
#include "canvas-clip.h"
#include "canvas-paint.h"
#include "canvas-save.h"
#include "canvas-restore.h"
#include "canvas-miterLimit.h"
#include "canvas.h"
#include "canvas-font.h"
#include "canvas-fill.h"
#include "canvas-fillStyle.h"
#include "canvas-fillRect.h"
#include "canvas-fillText.h"
#include "canvas-stroke.h"
#include "canvas-strokeStyle.h"
#include "canvas-strokeRect.h"
#include "canvas-strokeText.h"
#include "canvas-kerning.h"

int main(void)
{
	char s[3];
	
	canvas__init();
	
	font_util_new("./font.ttf", "Font");
	
	canvas_clearRect(0, 0, egl_get_width(), egl_get_height());
	canvas_lineWidth(1);
	
	paint_t paint;
	paint_createColor(&paint, 0, 0, 0, 1);
	
	canvas_fillStyle(&paint);
	
	canvas_font("Font", 200);
	canvas_kerning(VG_FALSE);
	canvas_fillText("Kerning OFF", 100, 100);
	canvas_kerning(VG_TRUE);
	canvas_fillText("Kerning ON", 100, 380);
	
	egl_swap_buffers();
	
	printf("Press <Enter> to shutdown.\n");
	fgets(s, 2, stdin);
	
	paint_cleanup(&paint);
	canvas__cleanup();
	
	return 0;
}
