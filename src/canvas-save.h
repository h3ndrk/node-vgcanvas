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

#ifndef __CANVAS_SAVE_H__
#define __CANVAS_SAVE_H__

typedef struct canvas_save_stack_t
{
	// canvas_line_cap_t lineCap;
	// canvas_line_join_t lineJoin;
	
	// color_t fillColor;
	// color_t strokeColor;
	
	// VGfloat globalAlpha;
	// VGfloat lineWidth;
	
	// VGint dashCount;
	// VGfloat *dashPattern;
	// VGfloat dashOffset;
	
	// VGboolean clipping;
	// VGMaskLayer savedLayer;
	
	struct canvas_save_stack_t *next;
} canvas_save_stack_t;

void canvas_save(void);
void canvas_save_cleanup(void);
canvas_save_stack_t *canvas_save_get(void);

#endif /* __CANVAS_SAVE_H__ */
