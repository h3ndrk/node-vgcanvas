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

#ifndef __CANVAS_H__
#define __CANVAS_H__

void canvas__init(void);
void canvas__cleanup(void);

void canvas_clearRect(VGfloat x, VGfloat y, VGfloat width, VGfloat height);
void canvas_fillRect(VGfloat x, VGfloat y, VGfloat width, VGfloat height);
void canvas_fillStyle_color(VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha);
void canvas_strokeRect(VGfloat x, VGfloat y, VGfloat width, VGfloat height);
void canvas_strokeStyle_color(VGfloat red, VGfloat green, VGfloat blue, VGfloat alpha);
void canvas_lineWidth(VGfloat width);
void canvas_lineCap(char *cap_style);
void canvas_lineJoin(char *cap_style);
void canvas_globalAlpha(VGfloat alpha);

#endif /* __CANVAS_H__ */
