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
#include "log-util.h"
#include "canvas-beginPath.h"
#include "canvas-paint.h"
#include "canvas-strokeStyle.h"
#include "canvas-font.h"
#include "font-util.h"
#include "canvas-lineWidth.h"
#include "canvas-setLineDash.h"
#include "canvas-lineDashOffset.h"
#include "canvas-fillText.h"
#include "canvas-kerning.h"

/**
 * The strokeText() method strokes a given text at the given (x, y) position. If
 * the optional fourth parameter for a maximum width is provided, the text will
 * be scaled to fit that width. maxWidth is not supported.
 * @param text The text to render using the current font, textAlign,
 *             textBaseline, and direction values.
 * @param x The x axis of the coordinate for the text starting point.
 * @param y The y axis of the coordinate for the text starting point.
 */
void canvas_strokeText(char *text, VGfloat x, VGfloat y)
{
	int fonts_index = canvas_font_get_index();
	VGfloat size = canvas_font_get_size();
	int lineDashPattern_index = 0;
	VGfloat lineDashOffset = canvas_lineDashOffset_get();
	VGfloat lineWidth = canvas_lineWidth_get();
	VGint lineDashCount = canvas_setLineDash_get_count();
	VGfloat *lineDashPattern = NULL;
	VGfloat *lineDashPattern2 = NULL;
	unsigned int text_index = 0;
	VGfloat offset_x = 0;
	VGfloat offset_kerning_x = 0;
	int char_index = 0;
	
	if(fonts_index < 0 || text == NULL)
	{
		return;
	}
	
	lineDashPattern = malloc(canvas_setLineDash_get_count() * sizeof(VGfloat));
	lineDashPattern2 = malloc(canvas_setLineDash_get_count() * sizeof(VGfloat));
	if(lineDashPattern == NULL || lineDashPattern2 == NULL)
	{
		eprintf("Failed to copy dash pattern.\n");
		
		return;
	}
	
	memcpy(lineDashPattern, canvas_setLineDash_get_data(), canvas_setLineDash_get_count() * sizeof(VGfloat));
	
	paint_activate(canvas_strokeStyle_get(), VG_STROKE_PATH);
	
	for(lineDashPattern_index = 0; lineDashPattern_index < lineDashCount; lineDashPattern_index++)
	{
		lineDashPattern2[lineDashPattern_index] = lineDashPattern[lineDashPattern_index] / size;
	}
	
	canvas_setLineDash(lineDashCount, lineDashPattern2);
	canvas_lineWidth(lineWidth / size);
	canvas_lineDashOffset(lineDashOffset / size);
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_STROKE_PAINT_TO_USER);
	
	vgScale(1 / size, 1 / size);
	vgTranslate(-x, -(egl_get_height() - y - size));
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
	
	vgTranslate(x, egl_get_height() - y - size);
	vgScale(size, size);
	
	for(text_index = 0; text_index < strlen(text); text_index++)
	{
		char_index = font_util_get_char_index(fonts_index, text[text_index]);
		
		vgDrawPath(font_util_get_path(fonts_index, char_index), VG_STROKE_PATH);
		
		if(text_index < strlen(text) - 1)
		{
			// apply kerning if kerning should be used and if kerning is available
			if(canvas_kerning_get() && font_util_get_kerning_availability(fonts_index) == VG_TRUE)
			{
				offset_kerning_x = font_util_get_kerning_x(fonts_index, text[text_index], text[text_index + 1]);
				
				offset_x += offset_kerning_x;
				vgTranslate(offset_kerning_x, 0);
			}
			
			offset_x += font_util_get_advance_x(fonts_index, char_index);
			vgTranslate(font_util_get_advance_x(fonts_index, char_index), 0);
		}
	}
	
	vgTranslate(-offset_x, 0);
	
	vgScale(1 / size, 1 / size);
	vgTranslate(-x, -(egl_get_height() - y - size));
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_STROKE_PAINT_TO_USER);
	
	vgTranslate(x, egl_get_height() - y - size);
	vgScale(size, size);
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
	
	canvas_lineDashOffset(lineDashOffset);
	canvas_lineWidth(lineWidth);
	canvas_setLineDash(lineDashCount, lineDashPattern);
	
	free(lineDashPattern);
	free(lineDashPattern2);
}
