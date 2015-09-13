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

#ifndef __COLOR_H__
#define __COLOR_H__

typedef struct
{
	char color_type; // 0 = color
	VGPaint paint;
	VGfloat red;
	VGfloat green;
	VGfloat blue;
	VGfloat alpha;
} color_t;

void color_set_rgb(color_t *color, float red, float green, float blue);
void color_set_rgba(color_t *color, float red, float green, float blue, float alpha);

#endif /* __COLOR_H__ */
