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

#ifndef __CANVAS_SAVE_H__
#define __CANVAS_SAVE_H__

typedef struct canvas_save_stack_t
{
	VGfloat matrix_path[9];
	VGfloat matrix_image[9];
	VGfloat matrix_fill[9];
	VGfloat matrix_stroke[9];
	
	VGboolean clip_clipping;
	VGMaskLayer clip_mask;
	
	VGint lineDash_count;
	VGfloat *lineDash_data;
	VGfloat lineDash_offset;
	
	paint_t *fillStyle;
	VGint fillStyle_count;
	VGfloat *fillStyle_data;
	paint_t *strokeStyle;
	VGint strokeStyle_count;
	VGfloat *strokeStyle_data;
	VGfloat globalAlpha;
	
	VGfloat lineWidth;
	char *lineCap;
	char *lineJoin;
	VGfloat miterLimit;
	
	char *globalCompositeOperation;
	
	char *font_name;
	VGfloat font_size;
	
	char *textAlign;
	char *textBaseline;
	
	// TODO: imageSmoothingEnabled missing
	
	struct canvas_save_stack_t *next;
} canvas_save_stack_t;

void canvas_save(void);
void canvas_save_cleanup_state(canvas_save_stack_t *state);
void canvas_save_cleanup(void);
canvas_save_stack_t *canvas_save_get(void);
void canvas_save_set(canvas_save_stack_t *mask);

#endif /* __CANVAS_SAVE_H__ */
