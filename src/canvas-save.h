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
	// TODO: transformation matrix missing
	
	VGboolean clip_clipping;
	VGMaskLayer clip_mask;
	
	VGint lineDash_count;
	VGfloat *lineDash_data;
	VGfloat lineDash_offset;
	
	// TODO: strokeStyle missing
	// TODO: fillStyle missing
	VGfloat globalAlpha;
	
	VGfloat lineWidth;
	VGfloat lineCap;
	VGfloat lineJoin;
	VGfloat miterLimit;
	
	// TODO: shadowOffsetX missing
	// TODO: shadowOffsetY missing
	// TODO: shadowOffsetBlur missing
	// TODO: shadowOffsetColor missing
	
	// TODO: globalCompositeOperation missing
	
	// TODO: font missing
	// TODO: textAlign missing
	// TODO: textBaseline missing
	// TODO: direction missing
	
	// TODO: imageSmoothingEnabled missing
	
	struct canvas_save_stack_t *next;
} canvas_save_stack_t;

void canvas_save(void);
void canvas_save_cleanup_state(canvas_save_stack_t *state);
void canvas_save_cleanup(void);
canvas_save_stack_t *canvas_save_get(void);
void canvas_clip_set(canvas_save_stack_t *mask);

#endif /* __CANVAS_SAVE_H__ */
