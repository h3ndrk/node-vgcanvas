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
// #include "include-freetype.h"

#include "log-util.h"
#include "canvas-clip.h"
#include "canvas-setLineDash.h"
#include "canvas-globalAlpha.h"
#include "canvas-lineWidth.h"
#include "canvas-lineCap.h"
#include "canvas-lineJoin.h"
#include "canvas-miterLimit.h"
#include "canvas-lineDashOffset.h"
#include "canvas-paint.h"
#include "canvas-fillStyle.h"
#include "canvas-strokeStyle.h"
#include "canvas-save.h"
#include "canvas-restore.h"

/**
 * The restore() method restores the most recently saved canvas state by popping
 * the top entry in the drawing state stack. If there is no saved state, this
 * method does nothing.
 */
void canvas_restore(void)
{
	canvas_save_stack_t *state_top = canvas_save_get();
	canvas_save_stack_t *state_beneath = NULL;
	
	printf("Restoring from stack...\n");
	
	if(state_top == NULL)
	{
		eprintf("Failed to restore top state of stack. No states in stack.\n");
		
		return;
	}
	
	state_beneath = state_top->next;
	state_top->next = NULL;
	
	canvas_save_set(state_beneath);
	
	// restore properties from top state in stack
	// TODO: transformation matrix missing
	
	if(state_top->clip_clipping == VG_TRUE)
	{
		canvas_clip_set_mask(state_top->clip_mask);
	}
	canvas_clip_set_clipping(state_top->clip_clipping);
	
	canvas_setLineDash(state_top->lineDash_count, state_top->lineDash_data);
	
	canvas_fillStyle(state_top->fillStyle);
	if(state_top->fillStyle_count != 0 && state_top->fillStyle_data != NULL)
	{
		// printf("Restoring color...\n");
		
		memcpy(canvas_fillStyle_get()->data, state_top->fillStyle_data, state_top->fillStyle_count * sizeof(VGfloat));
		canvas_fillStyle_get()->count = state_top->fillStyle_count;
	}
	canvas_strokeStyle(state_top->strokeStyle);
	if(state_top->strokeStyle_count != 0 && state_top->strokeStyle_data != NULL)
	{
		// printf("Restoring color...\n");
		
		memcpy(canvas_strokeStyle_get()->data, state_top->strokeStyle_data, state_top->strokeStyle_count * sizeof(VGfloat));
		canvas_strokeStyle_get()->count = state_top->strokeStyle_count;
	}
	canvas_globalAlpha(state_top->globalAlpha);
	
	canvas_lineWidth(state_top->lineWidth);
	canvas_lineCap(state_top->lineCap);
	canvas_lineJoin(state_top->lineJoin);
	canvas_miterLimit(state_top->miterLimit);
	canvas_lineDashOffset(state_top->lineDash_offset);
	
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
	
	canvas_save_cleanup_state(state_top);
}
