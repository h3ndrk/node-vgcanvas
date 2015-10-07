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

#include "log-util.h"
#include "egl-util.h"
#include "canvas-beginPath.h"
#include "canvas-paint.h"
#include "canvas-fillStyle.h"
#include "canvas-font.h"
#include "font-util.h"
#include "canvas-fillText.h"

/**
 * The fillText() method fills a given text at the given (x, y) position. If the
 * optional fourth parameter for a maximum width is provided, the text will be
 * scaled to fit that width. maxWidth is not supported.
 * @param text The text to render using the current font, textAlign,
 *             textBaseline, and direction values.
 * @param x The x axis of the coordinate for the text starting point.
 * @param y The y axis of the coordinate for the text starting point.
 */
void canvas_fillText(char *text, float x, float y)
{
	int fonts_index = canvas_font_get_index();
	VGFont vg_font = font_util_get_font(fonts_index);
	VGfloat size = canvas_font_get_size();
	VGuint *text_converted = NULL;
	unsigned int text_converted_index = 0;
	VGfloat glyph_origin[2] = { 0, 0 };
	
	if(fonts_index < 0 || text == NULL)
	{
		return;
	}
	
	paint_activate(canvas_fillStyle_get(), VG_FILL_PATH);
	
	text_converted = malloc(strlen(text) * sizeof(VGuint));
	if(text_converted == NULL)
	{
		eprintf("Failed to convert text data to 2 byte text.\n");
		
		return;
	}
	
	for(text_converted_index = 0; text_converted_index < strlen(text); text_converted_index++)
	{
		text_converted[text_converted_index] = (VGuint)text[text_converted_index];
	}
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER);
	
	vgScale(1 / size, 1 / size);
	vgTranslate(-x, -(egl_get_height() - y - size));
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_GLYPH_USER_TO_SURFACE);
	
	vgSetfv(VG_GLYPH_ORIGIN, 2, glyph_origin);
	
	vgTranslate(x, egl_get_height() - y - size);
	vgScale(size, size);
	
	vgDrawGlyphs(vg_font, strlen(text), text_converted, NULL, NULL, VG_FILL_PATH, VG_FALSE);
	
	vgScale(1 / size, 1 / size);
	vgTranslate(-x, -(egl_get_height() - y - size));
	
	vgSetfv(VG_GLYPH_ORIGIN, 2, glyph_origin);
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER);
	
	vgTranslate(x, egl_get_height() - y - size);
	vgScale(size, size);
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
	
	free(text_converted);
}
