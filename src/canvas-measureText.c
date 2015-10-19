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

#include "log-util.h"
#include "egl-util.h"
#include "canvas-beginPath.h"
#include "canvas-paint.h"
#include "canvas-fillStyle.h"
#include "canvas-font.h"
#include "font-util.h"
#include "canvas-measureText.h"
#include "canvas-kerning.h"
#include "canvas-textAlign.h"
#include "canvas-textBaseline.h"

/**
 * The measureText() method returns an object that contains information about
 * the measured text (such as its width for example).
 * @param metrics The metrics structure where the measured informations are
 *                stored.
 * @param text The text to measure using the current font, textAlign,
 *             textBaseline, and direction values.
 */
void canvas_measureText(canvas_measure_text_metrics_t *metrics, char *text)
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
		
		// printf("%c %f %f\n", text[text_index], start_y * size, end_y * size);
		
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
	
	metrics->font_size = size;
	metrics->width = (end_x - start_x) * size;
	metrics->height = (start_y + end_y) * size;
	
	switch(canvas_textAlign_get_internal())
	{
		case CANVAS_TEXT_ALIGN_LEFT:
		{
			metrics->actual_bounding_box_left = 0;
			metrics->actual_bounding_box_right = metrics->width;
			
			break;
		}
		case CANVAS_TEXT_ALIGN_RIGHT:
		{
			metrics->actual_bounding_box_left = metrics->width;
			metrics->actual_bounding_box_right = 0;
			
			break;
		}
		case CANVAS_TEXT_ALIGN_CENTER:
		{
			metrics->actual_bounding_box_left = metrics->width * 0.5;
			metrics->actual_bounding_box_right = metrics->width * 0.5;
			
			break;
		}
	}
	
	switch(canvas_textBaseline_get_internal())
	{
		case CANVAS_TEXT_BASELINE_TOP: case CANVAS_TEXT_BASELINE_HANGING:
		{
			metrics->actual_bounding_box_ascent = 0;
			metrics->actual_bounding_box_descent = metrics->height;
			
			break;
		}
		case CANVAS_TEXT_BASELINE_MIDDLE:
		{
			metrics->actual_bounding_box_ascent = metrics->height * 0.5;
			metrics->actual_bounding_box_descent = metrics->height * 0.5;
			
			break;
		}
		case CANVAS_TEXT_BASELINE_ALPHABETIC:
		{
			metrics->actual_bounding_box_ascent = start_y * size;
			metrics->actual_bounding_box_descent = end_y * size;
			
			break;
		}
		case CANVAS_TEXT_BASELINE_IDEOGRAPHIC:
		{
			metrics->actual_bounding_box_ascent = metrics->height;
			metrics->actual_bounding_box_descent = 0;
			
			break;
		}
		case CANVAS_TEXT_BASELINE_BOTTOM:
		{
			metrics->actual_bounding_box_ascent = start_y * size;
			metrics->actual_bounding_box_descent = end_y * size;
			
			break;
		}
	}
	
	metrics->em_height_ascent = font_util_get_ascender(fonts_index) * size;
	metrics->em_height_descent = font_util_get_descender(fonts_index) * size;
	metrics->font_bounding_box_ascent = font_util_get_ascender(fonts_index) * size;
	metrics->font_bounding_box_descent = font_util_get_descender(fonts_index) * size;
	metrics->hanging_baseline = font_util_get_ascender(fonts_index) * size;
	metrics->alphabetic_baseline = 0;
	metrics->ideographic_baseline = font_util_get_descender(fonts_index) * size;
	metrics->rendering_offset_x = start_x * size;
	metrics->rendering_offset_y = start_y * size;
}
