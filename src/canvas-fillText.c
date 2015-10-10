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

#include "log-util.h"
#include "egl-util.h"
#include "canvas-beginPath.h"
#include "canvas-paint.h"
#include "canvas-fillStyle.h"
#include "canvas-font.h"
#include "font-util.h"
#include "canvas-fillText.h"
#include "canvas-kerning.h"

/**
 * The fillText() method fills a given text at the given (x, y) position. If the
 * optional fourth parameter for a maximum width is provided, the text will be
 * scaled to fit that width. maxWidth is not supported.
 * @param text The text to render using the current font, textAlign,
 *             textBaseline, and direction values.
 * @param x The x axis of the coordinate for the text starting point.
 * @param y The y axis of the coordinate for the text starting point.
 */
void canvas_fillText(char *text, VGfloat x, VGfloat y)
{
	int fonts_index = canvas_font_get_index();
	VGfloat size = canvas_font_get_size();
	unsigned int text_index = 0;
	VGfloat offset_x = 0;
	VGfloat offset_kerning_x = 0;
	int char_index = 0;
	
	if(fonts_index < 0 || text == NULL)
	{
		return;
	}
	
	paint_activate(canvas_fillStyle_get(), VG_FILL_PATH);
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER);
	
	vgScale(1 / size, 1 / size);
	vgTranslate(-x, -(egl_get_height() - y - size));
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
	
	vgTranslate(x, egl_get_height() - y - size);
	vgScale(size, size);
	
	for(text_index = 0; text_index < strlen(text); text_index++)
	{
		char_index = font_util_get_char_index(fonts_index, text[text_index]);
		
		vgDrawPath(font_util_get_path(fonts_index, char_index), VG_FILL_PATH);
		
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
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER);
	
	vgTranslate(x, egl_get_height() - y - size);
	vgScale(size, size);
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
}
