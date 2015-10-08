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

#ifndef __FONT_UTIL_H__
#define __FONT_UTIL_H__

#include <VG/openvg.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

typedef struct font_t
{
	char *path;
	char *name;
	FT_Face face;
	VGFont vg_font;
} font_t;

#define FONT_UTIL_SIZE 64 * 64 * 64
#define FONT_UTIL_TO_FLOAT(ft_size) ((float)(ft_size) / (FONT_UTIL_SIZE))

int font_util_get(char *name);
FT_Face font_util_get_face(int fonts_index, char character);
VGFont font_util_get_font(int fonts_index);
void font_util_init(void);
void font_util_cleanup(void);
int font_util_new(char *path, char *name);
void font_util_remove(char *name);
VGuint segments_count_get(void);
VGubyte *segments_get(void);
VGuint coords_count_get(void);
VGfloat *coords_get(void);

#endif /* __FONT_UTIL_H__ */
