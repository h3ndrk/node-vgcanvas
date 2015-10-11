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
	unsigned int i = 0;
	
	canvas__init();
	
	font_util_new("./font.ttf", "font");
	image_t* image = image_load("./test.png");
	
	draw_grid();
	
	paint_t paint;
	//paint_createLinearGradient(&paint, 0, 0, 1000, 0);
	//paint_addColorStop(&paint, 0, 0, 1, 0, 1);
	//paint_addColorStop(&paint, 1, 0, 0, 1, 1);
	//paint_createColor(&paint, 1, 0, 0, 1);
	//canvas_fillStyle(&paint);
	//canvas_font("font", 30);
	
	//for(int u = 0; u < 50; u++)
	//{
	//	for(int i = 0; i < 50; i++) 
	//	{
			/*paint_t p2;
			paint_createColor(&p2, 1, 0, 0, 1);
			canvas_fillStyle(&p2);*/
	//		canvas_fillRect(u * 10, i * 10, 5, 5);
	//	}
	//}
	
	/*canvas_clearRect(0, 0, egl_get_width(), egl_get_height());
	canvas_lineWidth(2);
	
	paint_t paint;
	paint_createColor(&paint, 1, 0.3, 0, 1);
	
	canvas_fillStyle(&paint);
	canvas_strokeStyle(&paint);
	canvas_fillRect(100, 160, 450, 140);*/
	
	canvas_drawImage(image, 100, 100, 200, 200, 0, 0, 200, 200);
	canvas_drawImage(image, 400, 100, 200, 200, 0, 100, 200, 200);
	canvas_drawImage(image, 100, 500, 200, 200, 100, 0, 400, 200);
	
	// paint_t gradient;
	// paint_createLinearGradient(&gradient, 100, 0, 500, 0);
	// paint_addColorStop(&gradient, 0, 0, 1, 0, 1);
	// paint_addColorStop(&gradient, 0.25f, 0, 0, 0, 0);
	// paint_addColorStop(&gradient, 0.5f, 0, 0, 1, 1);
	// paint_addColorStop(&gradient, 0.75f, 0, 0, 0, 0);
	// paint_addColorStop(&gradient, 1, 1, 0, 0, 1);
	
	// canvas_fillStyle(&gradient);
	// canvas_fillRect(0, 0, egl_get_width(), egl_get_height());
	
	// paint_t radial;
	// paint_createRadialGradient(&radial, 200, 200, 100, 200, 200);
	// paint_addColorStop(&radial, 0, 1, 0, 0, 1);
	// paint_addColorStop(&radial, 1, 0, 0, 0, 0);
	
	// paint_t textGradient;
	// paint_createLinearGradient(&textGradient, 0, 0, egl_get_width(), 0);
	// paint_addColorStop(&textGradient, 0, 0, 1, 0, 1);
	// paint_addColorStop(&textGradient, 1, 1, 0, 0, 1);
	
	// canvas_fillStyle(&paint);
	// canvas_fillRect(0, 100, 100, 100);
	
	// canvas_fillStyle(&paint);
	// canvas_strokeStyle(&paint);
	// canvas_strokeRect(0, 250, 100, 100);
	
	// canvas_beginPath();
	// canvas_moveTo(200, 200);
	// canvas_lineTo(400, 900);
	// canvas_lineTo(800, 500);
	// canvas_closePath();
	// canvas_stroke();
	
	// canvas_beginPath();
	// canvas_lineTo(300, 1000);
	// canvas_stroke();

	// paint_setRGBA(&paint, 1, 1, 0, 1);
	// canvas_strokeRect(150, 250, 100, 100);
	
	// canvas_fillStyle(&gradient);
	// canvas_fillRect(500, 100, 200, 200);
	
	// canvas_fillStyle(&radial);
	// canvas_fillRect(100, 100, 200, 200);
	
	// canvas_fillRect(100, 800, 400, 3);
	
	// canvas_save();
	
	// canvas_fillStyle(&gradient);
	
	// canvas_fillRect(100, 825, 400, 3);
	
	// canvas_restore();
	
	// canvas_fillRect(100, 850, 400, 3);
	
	// canvas_strokeStyle(&paint);
	// canvas_fillStyle(&paint);
	//canvas_font("Font", 200);
	//canvas_fillText("node", 620, 100);
	//canvas_fillText("vgcanvas", 100, 330);
	
	// canvas_beginPath();
	// vgTranslate(100, 100);
	// font_render_character("/root/home-infoscreen/font.ttf", 'H');
	// canvas_fill();
	// canvas_beginPath();
	// vgTranslate(70, 0);
	// font_render_character("/root/home-infoscreen/font.ttf", 'i');
	// canvas_fill();
	// vgTranslate(-150, -100);
	
	// canvas_fillRect(60, 100, 10, 64);
	
	egl_swap_buffers();
	
	printf("Press <Enter> to shutdown.\n");
	fgets(s, 2, stdin);
	
	//paint_cleanup(&paint);
	// paint_destroy(&gradient);
	// paint_destroy(&textGradient);
	// paint_destroy(&radial);
	image_cleanup(image);
	canvas__cleanup();
	
	return 0;
}
