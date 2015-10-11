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
#include "canvas-textAlign.h"
#include "canvas-textBaseline.h"
#include "canvas-kerning.h"
#include "canvas-shadowColor.h"
#include "canvas-shadowBlur.h"
#include "canvas-shadowOffsetX.h"
#include "canvas-shadowOffsetY.h"

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
	VGfloat start_x = 0;
	VGfloat end_x = 0;
	VGfloat start_y = 0;
	VGfloat start_y_temp = 0;
	VGfloat end_y = 0;
	VGfloat end_y_temp = 0;
	VGfloat matrix_backup_fill_paint[9];
	VGfloat matrix_backup_path[9];
	
	if(fonts_index < 0 || text == NULL)
	{
		return;
	}
	
	for(text_index = 0; text_index < strlen(text); text_index++)
	{
		char_index = font_util_get_char_index(fonts_index, text[text_index]);
		
		if(text_index == 0)
		{
			start_x = font_util_get_bearing_x(fonts_index, char_index);
		}
		
		start_y_temp = font_util_get_bearing_y(fonts_index, char_index);
		end_y_temp = font_util_get_height(fonts_index, char_index) - font_util_get_bearing_y(fonts_index, char_index);
		
		if(start_y_temp > start_y)
		{
			start_y = start_y_temp;
		}
		
		if(end_y_temp > end_y)
		{
			end_y = end_y_temp;
		}
		
		if(text_index < strlen(text) - 1)
		{
			// apply kerning if kerning should be used and if kerning is available
			if(canvas_kerning_get() && font_util_get_kerning_availability(fonts_index) == VG_TRUE)
			{
				offset_kerning_x = font_util_get_kerning_x(fonts_index, text[text_index], text[text_index + 1]);
				
				offset_x += offset_kerning_x;
			}
			
			offset_x += font_util_get_advance_x(fonts_index, char_index);
		}
		else
		{
			end_x = offset_x + font_util_get_bearing_x(fonts_index, char_index) + font_util_get_width(fonts_index, char_index);
		}
	}
	
	// printf("{\n\ttext: \"%s\",\n\tfont_index: %i,\n\tsize: %f,\n\tstart_x: %f,\n\tend_x: %f,\n\tstart_y: %f,\n\tend_y: %f,\n\tascender: %f,\n\tdescender: %f\n}\n", text, fonts_index, size, start_x * size, end_x * size, start_y * size, end_y * size, font_util_get_ascender(fonts_index) * size, font_util_get_descender(fonts_index) * size);
	
	switch(canvas_textAlign_get_internal())
	{
		case CANVAS_TEXT_ALIGN_LEFT:
		{
			x += -start_x * size;
			
			break;
		}
		case CANVAS_TEXT_ALIGN_RIGHT:
		{
			x += -end_x * size;
			
			break;
		}
		case CANVAS_TEXT_ALIGN_CENTER:
		{
			x += -((end_x - start_x) * 0.5 + start_x) * size;
			
			break;
		}
	}
	
	switch(canvas_textBaseline_get_internal())
	{
		case CANVAS_TEXT_BASELINE_TOP:
		{
			y += start_y * size;
			
			break;
		}
		case CANVAS_TEXT_BASELINE_HANGING:
		{
			y += font_util_get_ascender(fonts_index) * size;
			
			break;
		}
		case CANVAS_TEXT_BASELINE_MIDDLE:
		{
			y += (start_y + end_y) * 0.5 * size;
			
			break;
		}
		// do nothing on alphabetic baseline
		case CANVAS_TEXT_BASELINE_ALPHABETIC:
		{
		// 	y = y;
			
			break;
		}
		case CANVAS_TEXT_BASELINE_IDEOGRAPHIC:
		{
			y += -font_util_get_descender(fonts_index) * size;
			
			break;
		}
		case CANVAS_TEXT_BASELINE_BOTTOM:
		{
			y += -end_y * size;
			
			break;
		}
	}
	
	if(canvas_shadowColor_get_enabled())
	{
		egl_blur_begin();
		
		paint_activate(canvas_shadowColor_get(), VG_FILL_PATH);
		
		vgSeti(VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER);
		
		vgGetMatrix(matrix_backup_fill_paint);
		
		vgScale(1 / size, 1 / size);
		vgTranslate(-x, -(egl_get_height() - y));
		
		vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
		
		vgGetMatrix(matrix_backup_path);
		
		vgTranslate(x, egl_get_height() - y);
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
		
		vgLoadMatrix(matrix_backup_path);
		
		vgSeti(VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER);
		
		vgLoadMatrix(matrix_backup_fill_paint);
		
		vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
		
		egl_blur_end(canvas_shadowBlur_get(), canvas_shadowOffsetX_get(), canvas_shadowOffsetY_get());
	}
	
	offset_x = 0;
	
	paint_activate(canvas_fillStyle_get(), VG_FILL_PATH);
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER);
	
	vgGetMatrix(matrix_backup_fill_paint);
	
	vgScale(1 / size, 1 / size);
	vgTranslate(-x, -(egl_get_height() - y));
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
	
	vgGetMatrix(matrix_backup_path);
	
	vgTranslate(x, egl_get_height() - y);
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
	
	vgLoadMatrix(matrix_backup_path);
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER);
	
	vgLoadMatrix(matrix_backup_fill_paint);
	
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
}
