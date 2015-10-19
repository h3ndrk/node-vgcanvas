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
#include "include-freetype.h"

#include "egl-util.h"
#include "font-util.h"
#include "image-util.h"
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
#include "canvas-drawImage.h"
#include "canvas-imageSmoothingEnabled.h"

int main(void)
{
	char s[3];
	
	canvas__init();
	
	font_util_new("./font.ttf", "Font");
	image_t *img = image_load("test2.png");
	
	canvas_clearRect(0, 0, egl_get_width(), egl_get_height());
	canvas_lineWidth(10);
	
	paint_t black;
	paint_t red;
	paint_createColor(&black, 0, 0, 0, 0.5);
	paint_createColor(&red, 1, 0, 0, 0.5);
	
	/*canvas_fillStyle(&black);
	canvas_font("Font", 200);
	canvas_textBaseline("middle");
	canvas_textAlign("right");
	canvas_fillText("I", egl_get_width() / 2 - 200, egl_get_height() / 2);
	canvas_textAlign("left");
	canvas_fillText("node", egl_get_width() / 2 + 200, egl_get_height() / 2);
	canvas_fillStyle(&red);
	canvas_fillRect(egl_get_width() / 2 - 80, egl_get_height() / 2 - 80, 160, 160);*/

	canvas_imageSmoothingEnabled(VG_TRUE);
	canvas_drawImage(img, 100, 100, 200, 200, 0, 0, img->width, img->height);
	canvas_imageSmoothingEnabled(VG_FALSE);
	canvas_drawImage(img, 400, 100, 200, 200, 0, 0, img->width, img->height);
	
	canvas_fillStyle(&red);
	canvas_fillRect(100, 400, 100, 100);
	canvas_fillStyle(&black);
	canvas_fillRect(150, 400, 100, 100);
	
	egl_swap_buffers();
	
	printf("Press <Enter> to shutdown.\n");
	fgets(s, 2, stdin);
	
	paint_cleanup(&black);
	paint_cleanup(&red);
	image_cleanup(img);
	canvas__cleanup();
	
	return 0;
}
