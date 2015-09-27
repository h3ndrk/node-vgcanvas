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

#include "canvas-clip.h"
#include "canvas-setLineDash.h"
#include "canvas-globalAlpha.h"
#include "canvas-lineWidth.h"
#include "canvas-lineCap.h"
#include "canvas-lineJoin.h"
#include "canvas-miterLimit.h"
#include "canvas-lineDashOffset.h"
#include "canvas-save.h"

static canvas_save_stack_t *canvas_save_stack_top = NULL;

/**
 * The save() method saves the entire state of the canvas by pushing the current
 * state onto a stack.
 */
void canvas_save(void)
{
	canvas_save_stack_t *state = NULL;
	
	state = malloc(sizeof(canvas_save_stack_t));
	
	if(state == NULL)
	{
		printf("Failed to add stack element.\n");
		
		return;
	}
	
	if(canvas_save_stack_top == NULL) // state is first element in stack
	{
		canvas_save_stack_top = state;
	}
	else
	{
		state->next = canvas_save_stack_top;
		canvas_save_stack_top = state;
	}
	
	// save properties to top state of stack
	// TODO: transformation matrix missing
	
	canvas_save_stack_top->clip_clipping = canvas_clip_get_clipping();
	if(canvas_save_stack_top->clip_clipping == VG_TRUE)
	{
		canvas_save_stack_top->clip_mask = canvas_clip_get_mask();
	}
	else
	{
		canvas_save_stack_top->clip_mask = 0;
	}
	
	canvas_save_stack_top->lineDash_count = canvas_setLineDash_get_count();
	if(canvas_save_stack_top->lineDash_count > 0)
	{
		canvas_save_stack_top->lineDash_data = malloc(canvas_save_stack_top->lineDash_count * sizeof(VGfloat));
		
		if(canvas_save_stack_top->lineDash_data == NULL)
		{
			printf("Failed to add stack element: Copying lineDash data failed.\n");
			
			canvas_save_stack_top->lineDash_count = 0;
		}
		else
		{
			memcpy(canvas_save_stack_top->lineDash_data, canvas_setLineDash_get_data(), canvas_save_stack_top->lineDash_count * sizeof(VGfloat));
		}
	}
	else
	{
		canvas_save_stack_top->lineDash_data = NULL;
	}
	
	// TODO: strokeStyle missing
	// TODO: fillStyle missing
	canvas_save_stack_top->globalAlpha = canvas_globalAlpha_get();
	
	canvas_save_stack_top->lineWidth = canvas_lineWidth_get();
	canvas_save_stack_top->lineCap = canvas_lineCap_get();
	canvas_save_stack_top->lineJoin = canvas_lineJoin_get();
	canvas_save_stack_top->miterLimit = canvas_miterLimit_get();
	canvas_save_stack_top->lineDash_offset = canvas_lineDashOffset_get();
	
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
}

/**
 * Cleans up specific stack states. Destroys the given state of the stack.
 * @param state The state to be destroyed.
 */
void canvas_save_cleanup_state(canvas_save_stack_t *state)
{
	if(state->next != NULL)
	{
		canvas_save_cleanup_state(state->next);
	}
	
	// cleanup properties of top state of stack
	
	// free(canvas_save_stack_top->property);
	// free(canvas_save_stack_top);
}

/**
 * Cleans up save(). Destroys the stack.
 */
void canvas_save_cleanup(void)
{
	printf("Cleaning up stack...\n");
	
	if(canvas_save_stack_top != NULL)
	{
		canvas_save_cleanup_state(canvas_save_stack_top);
	}
}

/**
 * Returns the stack.
 * @return The stack.
 */
canvas_save_stack_t *canvas_save_get(void)
{
	return canvas_save_stack_top;
}

/**
 * Sets the stack.
 * @param stack The stack.
 */
void canvas_save_set(canvas_save_stack_t *stack)
{
	canvas_save_stack_top = stack;
}
