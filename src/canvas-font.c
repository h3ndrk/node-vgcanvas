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
#include "font-util.h"
#include "canvas-font.h"

static int canvas_font_index = -1; // no font
static float canvas_font_size = 0;

/**
 * The font property specifies the current text style being used when drawing
 * text. This string uses the same syntax as the CSS font specifier. The default
 * font is undefined.
 * @param path The font path.
 * @param size The font size in space units.
 */
void canvas_font(char *path, VGfloat size)
{
	canvas_font_index = font_util_get(path);
	
	if(canvas_font_index < 0)
	{
		eprintf("Failed to find font face: %s\n", path);
		
		return;
	}
	
	canvas_font_size = size;
}

/**
 * Returns the font index.
 * @return The font index.
 */
int canvas_font_get_index(void)
{
	return canvas_font_index;
}

/**
 * Returns the font size.
 * @return The font size.
 */
float canvas_font_get_size(void)
{
	return canvas_font_size;
}
