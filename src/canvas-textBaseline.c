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
// #include "include-freetype.h"

#include "canvas-textBaseline.h"

static canvas_text_align_t canvas_textBaseline_value = CANVAS_TEXT_ALIGN_LEFT;

/**
 * The textBaseline property specifies the current text baseline being used when
 * drawing text.
 * @param text_baseline Possible values are left, right, center, start and end.
 */
void canvas_textBaseline(char *text_baseline)
{
	if(!strcmp(text_baseline, "top"))
	{
		canvas_textBaseline_value = CANVAS_TEXT_ALIGN_TOP;
	}
	else if(!strcmp(text_baseline, "hanging"))
	{
		canvas_textBaseline_value = CANVAS_TEXT_ALIGN_HANGING;
	}
	else if(!strcmp(text_baseline, "middle"))
	{
		canvas_textBaseline_value = CANVAS_TEXT_ALIGN_MIDDLE;
	}
	else if(!strcmp(text_baseline, "alphabetic"))
	{
		canvas_textBaseline_value = CANVAS_TEXT_BASELINE_ALPHABETIC;
	}
	else if(!strcmp(text_baseline, "ideographic"))
	{
		canvas_textBaseline_value = CANVAS_TEXT_BASELINE_IDEOGRAPHIC;
	}
	else if(!strcmp(text_baseline, "bottom"))
	{
		canvas_textBaseline_value = CANVAS_TEXT_BASELINE_BOTTOM;
	}
}

/**
 * It returns the current value (left by default).
 * @return A string specifying the current text baseline.
 */
char *canvas_textBaseline_get(void)
{
	switch(canvas_textBaseline_value)
	{
		case CANVAS_TEXT_BASELINE_TOP:
		{
			return "top";
			
			break;
		}
		case CANVAS_TEXT_BASELINE_HANGING:
		{
			return "hanging";
			
			break;
		}
		case CANVAS_TEXT_BASELINE_MIDDLE:
		{
			return "middle";
			
			break;
		}
		case CANVAS_TEXT_BASELINE_ALPHABETIC:
		{
			return "alphabetic";
			
			break;
		}
		case CANVAS_TEXT_BASELINE_IDEOGRAPHIC:
		{
			return "ideographic";
			
			break;
		}
		case CANVAS_TEXT_BASELINE_BOTTOM:
		{
			return "bottom";
			
			break;
		}
		default:
		{
			return "";
			
			break;
		}
	}
	
	return "";
}
