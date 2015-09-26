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

#include <stdio.h>
#include <math.h>

#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_OUTLINE_H

#include "egl-util.h"
#include "canvas.h"
#include "canvas-paint.h"
#include "canvas-clearRect.h"
#include "canvas-lineWidth.h"
#include "canvas-lineCap.h"
#include "canvas-lineJoin.h"
#include "canvas-globalAlpha.h"
#include "canvas-beginPath.h"
#include "canvas-moveTo.h"
#include "canvas-closePath.h"
#include "canvas-lineTo.h"

int main(void)
{
	char s[3];
	
	canvas__init();
	
	font_new("./font.ttf");
	
	canvas_clearRect(0, 0, egl_get_width(), egl_get_height());
	canvas_lineWidth(2);
	
	paint_t paint;
	paint_createColor(&paint, 1, 0, 0, 1);
	
	paint_t gradient;
	paint_createLinearGradient(&gradient, 500, 100, 700, 300);
	paint_addColorStop(&gradient, 0, 0, 1, 0, 1);
	paint_addColorStop(&gradient, 0.25f, 0, 0, 0, 0);
	paint_addColorStop(&gradient, 0.5f, 0, 0, 1, 1);
	paint_addColorStop(&gradient, 0.75f, 0, 0, 0, 0);
	paint_addColorStop(&gradient, 1, 1, 0, 0, 1);
	
	paint_t radial;
	paint_createRadialGradient(&radial, 200, 200, 100, 200, 200);
	paint_addColorStop(&radial, 0, 1, 0, 0, 1);
	paint_addColorStop(&radial, 1, 0, 0, 0, 0);
	
	paint_t textGradient;
	paint_createLinearGradient(&textGradient, 0, 0, egl_get_width(), 0);
	paint_addColorStop(&textGradient, 0, 0, 1, 0, 1);
	paint_addColorStop(&textGradient, 1, 1, 0, 0, 1);
	
	canvas_fillStyle(&paint);
	canvas_fillRect(0, 100, 100, 100);
	
	canvas_strokeStyle(&paint);
	canvas_strokeRect(0, 250, 100, 100);
	
	canvas_beginPath();
	canvas_moveTo(200, 200);
	canvas_lineTo(400, 900);
	canvas_lineTo(800, 500);
	canvas_closePath();
	canvas_stroke();
	
	canvas_beginPath();
	canvas_lineTo(300, 1000);
	canvas_stroke();

	paint_setRGBA(&paint, 1, 1, 0, 1);
	canvas_strokeRect(150, 250, 100, 100);
	
	canvas_fillStyle(&gradient);
	canvas_fillRect(500, 100, 200, 200);
	
	canvas_fillStyle(&radial);
	canvas_fillRect(100, 100, 200, 200);
	
	VGfloat dash[2] = {10, 10};
	canvas_setLineDash(2, dash);
	canvas_lineWidth(2);
	canvas_beginPath();
	canvas_moveTo(0, 800);
	canvas_lineTo(egl_get_width(), 800);
	canvas_stroke();
	
	canvas_fillStyle(&gradient);
	canvas_render_text_fill("./font.ttf", "Test", 100, 800, 100);
	
	
	// canvas_beginPath();
	// vgTranslate(100, 100);
	// font_render_character("/root/home-infoscreen/font.ttf", 'H');
	// canvas_fill();
	// canvas_beginPath();
	// vgTranslate(70, 0);
	// font_render_character("/root/home-infoscreen/font.ttf", 'i');
	// canvas_fill();
	// vgTranslate(-150, -100);
	
	
	canvas_fillRect(60, 100, 10, 64);
	
	egl_swap_buffers();
	
	printf("Press <Enter> to shutdown.\n");
	fgets(s, 2, stdin);
	
	paint_destroy(&paint);
	paint_destroy(&gradient);
	canvas__cleanup();
	
	return 0;
}
