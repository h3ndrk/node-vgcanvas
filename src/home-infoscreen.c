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
#include "image-util.h"
#include "canvas-drawImage.h"
#include "canvas-kerning.h"

void draw_grid(void)
{
	paint_t paint;
	paint_createColor(&paint, 0.7f, 0.7f, 0.7f, 1);
	canvas_strokeStyle(&paint);
	
	for(int x = 0; x < egl_get_width(); x += 100)
	{
		canvas_beginPath();
		canvas_moveTo(x, 0);
		canvas_lineTo(x, egl_get_height());
		canvas_stroke();
	}
	
	for(int y = 0; y < egl_get_height(); y += 100)
	{
		canvas_beginPath();
		canvas_moveTo(0, y);
		canvas_lineTo(egl_get_width(), y);
		canvas_stroke();
	}
	
	paint_cleanup(&paint);
}

int main(void)
{
	char s[3];
	
	canvas__init();
	
	font_util_new("./font.ttf", "Font");
	image_t* image = image_load("./test.png");
	
	draw_grid();
	
	canvas_drawImage(image, 100, 100, 200, 200, 0, 0, 200, 200);
	canvas_drawImage(image, 400, 100, 200, 200, 0, 100, 200, 200);
	canvas_drawImage(image, 100, 500, 200, 200, 100, 0, 400, 200);
	
	
	canvas_font("Font", 100);
	canvas_kerning(VG_FALSE);
	canvas_fillText("Kerning OFF", 100, 100);
	canvas_kerning(VG_TRUE);
	canvas_fillText("Kerning ON", 100, 380);
	
	egl_swap_buffers();
	
	printf("Press <Enter> to shutdown.\n");
	fgets(s, 2, stdin);
	
	image_cleanup(image);
	canvas__cleanup();
	
	return 0;
}
