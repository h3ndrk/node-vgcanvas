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

typedef struct font_t
{
	char *path;
	FT_Face face;
} font_t;

void convert_outline(const FT_Vector *points, const char *tags, const short *contours, short contours_count, short points_count);
int font_util_get(char *path);
FT_Face font_util_get_face(int fonts_index, char character);
void font_util_init(void);
void font_util_cleanup(void);
void font_util_new(char *path);
void font_util_remove(char *path);
VGuint segments_count_get(void);
VGubyte *segments_get(void);
VGuint coords_count_get(void);
VGfloat *coords_get(void);

#endif /* __FONT_UTIL_H__ */
