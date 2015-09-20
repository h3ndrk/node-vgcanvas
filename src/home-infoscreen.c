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
// #include "font.h"
#include "canvas-clearRect.h"
#include "canvas-lineWidth.h"

int main(void)
{
	char s[3];
	
	canvas__init();
	
	font_new("/root/home-infoscreen/font.ttf");
	
	canvas_clearRect(0, 0, egl_get_width(), egl_get_height());
	
	canvas_lineWidth(1);
	
	canvas_save();
	
	canvas_beginPath();
	canvas_rect(125, 125, 50, 50);
	canvas_clip();
	
	canvas_fillStyle_color(1, 0, 0, 1);
	
	canvas_fillRect(100, 100, 100, 100);
	canvas_globalAlpha(0.5);
	canvas_fillStyle_color(1, 1, 0, 1);
	canvas_fillRect(150, 150, 100, 100);
	
	canvas_restore();
	
	canvas_strokeStyle_color(1, 1, 1, 1);
	canvas_globalAlpha(1);
	
	canvas_beginPath();
	canvas_moveTo(400, 500);
	canvas_lineTo(600, 500);
	canvas_moveTo(500, 400);
	canvas_lineTo(500, 600);
	canvas_stroke();
	
	canvas_beginPath();
	canvas_arc(500, 500, 100, 0, 0.5 * M_PI, VG_TRUE);
	canvas_stroke();
	
	VGfloat dash[2];
	dash[0] = 5;
	dash[1] = 10;
	
	canvas_setLineDash(2, dash);
	
	canvas_beginPath();
	canvas_rect(400, 400, 200, 200);
	canvas_stroke();
	
	canvas_render_text_stroke("/root/home-infoscreen/font.ttf", "Test", 100, 100, 650);
	
	canvas_beginPath();
	canvas_rect(800, 400, 200, 200);
	canvas_stroke();
	
	canvas_setLineDash(0, NULL);
	
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
	
	canvas__cleanup();
	
	return 0;
}
