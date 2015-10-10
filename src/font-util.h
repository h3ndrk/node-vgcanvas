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

#ifndef __FONT_UTIL_H__
#define __FONT_UTIL_H__

#include <VG/openvg.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

typedef struct character_t
{
	char charcode;
	FT_UInt glyph_index;
	VGPath path;
	VGfloat advance_x;
	VGfloat bearing_x;
	VGfloat bearing_y;
	VGfloat width;
	VGfloat height;
} character_t;

typedef struct font_t
{
	char *path;
	char *name;
	FT_Face face;
	character_t **characters;
	int characters_amount;
	VGboolean kerning_available;
} font_t;

#define FONT_UTIL_SIZE 64 * 64 * 64
#define FONT_UTIL_TO_FLOAT(ft_size) ((float)(ft_size) / (FONT_UTIL_SIZE))

int font_util_get(char *name);
FT_Face font_util_get_face(unsigned int fonts_index, char character);
void font_util_init(void);
void font_util_cleanup(void);
int font_util_new(char *path, char *name);
void font_util_remove(char *name);
int font_util_get_char_index(unsigned int fonts_index, char character);
VGPath font_util_get_path(unsigned int fonts_index, int char_index);
VGfloat font_util_get_width(unsigned int fonts_index, int char_index);
VGfloat font_util_get_height(unsigned int fonts_index, int char_index);
VGfloat font_util_get_advance_x(unsigned int fonts_index, int char_index);
VGfloat font_util_get_bearing_x(unsigned int fonts_index, int char_index);
VGfloat font_util_get_bearing_y(unsigned int fonts_index, int char_index);
VGboolean font_util_get_kerning_availability(unsigned int fonts_index);
VGfloat font_util_get_kerning_x(unsigned int fonts_index, char character, char character_next);

#endif /* __FONT_UTIL_H__ */
