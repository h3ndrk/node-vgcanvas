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
	FT_Face face;
	unsigned int text_index = 0;
	VGfloat offset_x = 0;
	VGfloat size = canvas_font_get_size();
	
	if(fonts_index < 0)
	{
		return;
	}
	
	paint_activate(canvas_fillStyle_get(), VG_FILL_PATH);
	
	for(text_index = 0; text_index < strlen(text); text_index++)
	{
		face = font_util_get_face(fonts_index, text[text_index]);
		
		// printf("fill: '%c': %f %f\n", text[text_index], ((float)(face->glyph->metrics.vertAdvance) / 64), ((float)(face->glyph->metrics.horiAdvance) / 64));
		
		if(face->glyph->outline.n_contours != 0)
		{
			canvas_beginPath();
			
			convert_outline(face->glyph->outline.points, face->glyph->outline.tags, face->glyph->outline.contours, face->glyph->outline.n_contours, face->glyph->outline.n_points);
			
			vgAppendPathData(canvas_beginPath_get(), segments_count_get(), segments_get(), coords_get());
			
			vgTranslate(offset_x, 0);
			vgTranslate(x, egl_get_height() - y);
			vgScale((VGfloat)size / 64, (VGfloat)size / 64);
			
			vgDrawPath(canvas_beginPath_get(), VG_FILL_PATH);
			
			vgScale((VGfloat)64 / size, (VGfloat)64 / size);
			vgTranslate(-x, -(egl_get_height() - y));
			vgTranslate(-offset_x, 0);
			
		}
		
		offset_x += ((float)(face->glyph->metrics.horiAdvance) / 64) * ((float)size / 64);
	}
}
