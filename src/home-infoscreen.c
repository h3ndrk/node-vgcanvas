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
#include "canvas-measureText.h"
#include "canvas-kerning.h"
#include "canvas-textAlign.h"
#include "canvas-textBaseline.h"
#include "canvas-shadowColor.h"
#include "canvas-shadowBlur.h"
#include "canvas-shadowOffsetX.h"
#include "canvas-shadowOffsetY.h"

int main(void)
{
	char s[3];
	
	canvas__init();
	
	font_util_new("./font.ttf", "Font");
	
	canvas_clearRect(0, 0, egl_get_width(), egl_get_height());
	canvas_lineWidth(10);
	
	paint_t paint;
	paint_createColor(&paint, 0, 0, 1, 1);
	
	paint_t shadow;
	paint_createColor(&shadow, 1, 0, 0, 1);
	
	canvas_shadowBlur(10);
	canvas_shadowOffsetX(20);
	canvas_shadowOffsetY(20);
	
	canvas_fillStyle(&paint);
	canvas_strokeStyle(&paint);
	canvas_shadowColor(&shadow);
	
	canvas_fillRect(200, 200, 200, 200);
	
	canvas_beginPath();
	canvas_moveTo(500, 500);
	canvas_lineTo(600, 600);
	canvas_lineTo(400, 600);
	canvas_closePath();
	canvas_fill();
	
	canvas_font("Font", 200);
	canvas_fillText("Test", 300, 900);
	
	canvas_strokeRect(1000, 200, 200, 200);
	
	// canvas_beginPath();
	// canvas_moveTo(1500, 500);
	// canvas_lineTo(1600, 600);
	// canvas_lineTo(1400, 600);
	// canvas_closePath();
	// canvas_stroke();
	
	// canvas_font("Font", 200);
	// canvas_strokeText("Test", 1300, 900);
	
	// egl_blur_begin();
	
	// canvas_fillRect(300, 600, 200, 200);
	// canvas_strokeRect(100, 100, 1720, 880);
	
	// egl_blur_end(16, 0, 20);
	
	// paint_setRGBA(&paint, 1, 0, 0, 1);
	
	// canvas_textBaseline("top");
	// canvas_fillText("Font 1", 300, 300);
	
	// canvas_fillRect(300, 600, 200, 200);
	// canvas_strokeRect(100, 100, 1720, 880);
	
	// paint_t shadow;
	// paint_createColor(&shadow, 1, 1, 1, 1);
	
	// canvas_shadowColor(&shadow);
	
	// paint_setRGBA(&shadow, 1, 0, 0, 0);
	
	// canvas_shadowColor(&shadow);
	
	// canvas_measureText(&metrics, "node-vgcanvas");
	// printf("TextMetrics: {\n");
	// printf("\tfont_size: %f\n", metrics.font_size);
	// printf("\twidth: %f\n", metrics.width);
	// printf("\theight: %f\n", metrics.height);
	// printf("\tactual_bounding_box_left: %f\n", metrics.actual_bounding_box_left);
	// printf("\tactual_bounding_box_right: %f\n", metrics.actual_bounding_box_right);
	// printf("\tactual_bounding_box_ascent: %f\n", metrics.actual_bounding_box_ascent);
	// printf("\tactual_bounding_box_descent: %f\n", metrics.actual_bounding_box_descent);
	// printf("\tfont_bounding_box_ascent: %f\n", metrics.font_bounding_box_ascent);
	// printf("\tfont_bounding_box_descent: %f\n", metrics.font_bounding_box_descent);
	// printf("\tem_height_ascent: %f\n", metrics.em_height_ascent);
	// printf("\tem_height_descent: %f\n", metrics.em_height_descent);
	// printf("\thanging_baseline: %f\n", metrics.hanging_baseline);
	// printf("\talphabetic_baseline: %f\n", metrics.alphabetic_baseline);
	// printf("\tideographic_baseline: %f\n", metrics.ideographic_baseline);
	// printf("}\n");
	
	// canvas_strokeRect(100, 100, metrics.width, metrics.height);
	// canvas_font("Font", 75);
	// canvas_fillText("node-vgcanvas", 100, 350);
	// canvas_font("Font", 25);
	// canvas_fillText("node-vgcanvas", 100, 450);
	// canvas_font("Font", 15);
	// canvas_fillText("node-vgcanvas", 100, 495);
	// canvas_font("Font", 7);
	// canvas_fillText("node-vgcanvas", 100, 520);
	
	egl_swap_buffers();
	
	printf("Press <Enter> to shutdown.\n");
	fgets(s, 2, stdin);
	
	paint_cleanup(&paint);
	canvas__cleanup();
	
	return 0;
}
