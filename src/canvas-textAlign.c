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

#include "canvas-textAlign.h"

static canvas_text_align_t canvas_textAlign_value = CANVAS_TEXT_ALIGN_LEFT;

/**
 * The textAlign property specifies the current text alignment being used when
 * drawing text. Beware that the alignment is base on the x value of the
 * fillText method. So if textAlign="center", then the text would be drawn at
 * x-50%*width.
 * @param text_align Possible values are left, right, center, start and end.
 */
void canvas_textAlign(char *text_align)
{
	if(!strcmp(text_align, "left") || !strcmp(text_align, "start"))
	{
		canvas_textAlign_value = CANVAS_TEXT_ALIGN_LEFT;
	}
	else if(!strcmp(text_align, "right") || !strcmp(text_align, "end"))
	{
		canvas_textAlign_value = CANVAS_TEXT_ALIGN_RIGHT;
	}
	else if(!strcmp(text_align, "center"))
	{
		canvas_textAlign_value = CANVAS_TEXT_ALIGN_CENTER;
	}
}

/**
 * It returns the current value (left by default).
 * @return A string specifying the current text alignment.
 */
char *canvas_textAlign_get(void)
{
	switch(canvas_textAlign_value)
	{
		case CANVAS_TEXT_ALIGN_LEFT:
		{
			return "left";
			
			break;
		}
		case CANVAS_TEXT_ALIGN_RIGHT:
		{
			return "right";
			
			break;
		}
		case CANVAS_TEXT_ALIGN_CENTER:
		{
			return "center";
			
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
