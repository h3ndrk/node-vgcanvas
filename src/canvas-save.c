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

#include "include-core.h"
#include "include-openvg.h"
// #include "include-freetype.h"

#include "log-util.h"
#include "font-util.h"
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
#include "canvas-globalCompositeOperation.h"
#include "canvas-font.h"
#include "canvas-textAlign.h"
#include "canvas-textBaseline.h"

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
		eprintf("Failed to add stack element.\n");
		
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
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
	vgGetMatrix(canvas_save_stack_top->matrix_path);
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_IMAGE_USER_TO_SURFACE);
	vgGetMatrix(canvas_save_stack_top->matrix_image);
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_FILL_PAINT_TO_USER);
	vgGetMatrix(canvas_save_stack_top->matrix_fill);
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_STROKE_PAINT_TO_USER);
	vgGetMatrix(canvas_save_stack_top->matrix_stroke);
	vgSeti(VG_MATRIX_MODE, VG_MATRIX_PATH_USER_TO_SURFACE);
	
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
			eprintf("Failed to add stack element: Copying lineDash data failed.\n");
			
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
	
	canvas_save_stack_top->fillStyle = canvas_fillStyle_get();
	if(canvas_save_stack_top->fillStyle->paint_type == PAINT_TYPE_COLOR)
	{
		canvas_save_stack_top->fillStyle_data = malloc(canvas_save_stack_top->fillStyle->count * sizeof(VGfloat));
		
		if(canvas_save_stack_top->fillStyle_data == NULL)
		{
			eprintf("Failed to add stack element: Failed to save fillStyle.\n");
			
			canvas_save_stack_top->fillStyle_count = 0;
		}
		else
		{
			memcpy(canvas_save_stack_top->fillStyle_data, canvas_save_stack_top->fillStyle->data, canvas_save_stack_top->fillStyle->count * sizeof(VGfloat));
			canvas_save_stack_top->fillStyle_count = canvas_save_stack_top->fillStyle->count;
		}
	}
	else
	{
		canvas_save_stack_top->fillStyle_data = NULL;
		canvas_save_stack_top->fillStyle_count = 0;
	}
	canvas_save_stack_top->strokeStyle = canvas_strokeStyle_get();
	if(canvas_save_stack_top->strokeStyle->paint_type == PAINT_TYPE_COLOR)
	{
		canvas_save_stack_top->strokeStyle_data = malloc(canvas_save_stack_top->strokeStyle->count * sizeof(VGfloat));
		
		if(canvas_save_stack_top->strokeStyle_data == NULL)
		{
			eprintf("Failed to add stack element: Failed to save strokeStyle.\n");
			
			canvas_save_stack_top->strokeStyle_count = 0;
		}
		else
		{
			memcpy(canvas_save_stack_top->strokeStyle_data, canvas_save_stack_top->strokeStyle->data, canvas_save_stack_top->strokeStyle->count * sizeof(VGfloat));
			canvas_save_stack_top->strokeStyle_count = canvas_save_stack_top->strokeStyle->count;
		}
	}
	else
	{
		canvas_save_stack_top->strokeStyle_data = NULL;
		canvas_save_stack_top->strokeStyle_count = 0;
	}
	canvas_save_stack_top->globalAlpha = canvas_globalAlpha_get();
	
	canvas_save_stack_top->lineWidth = canvas_lineWidth_get();
	canvas_save_stack_top->lineCap = canvas_lineCap_get();
	canvas_save_stack_top->lineJoin = canvas_lineJoin_get();
	canvas_save_stack_top->miterLimit = canvas_miterLimit_get();
	canvas_save_stack_top->lineDash_offset = canvas_lineDashOffset_get();
	
	canvas_save_stack_top->globalCompositeOperation = canvas_globalCompositeOperation_get();
	
	canvas_save_stack_top->font_name = strdup(font_util_get_name(canvas_font_get_index()));
	canvas_save_stack_top->font_size = canvas_font_get_size();
	
	canvas_save_stack_top->textAlign = canvas_textAlign_get();
	canvas_save_stack_top->textBaseline = canvas_textBaseline_get();
	
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
	if(state->clip_clipping == VG_TRUE)
	{
		canvas_clip_cleanup_mask(state->clip_mask);
	}
	
	if(state->fillStyle_data != NULL)
	{
		free(state->fillStyle_data);
		state->fillStyle_data = NULL;
	}
	
	if(state->strokeStyle_data != NULL)
	{
		free(state->strokeStyle_data);
		state->strokeStyle_data = NULL;
	}
	
	if(state->lineDash_data != NULL)
	{
		free(state->lineDash_data);
		state->lineDash_data = NULL;
	}
	
	if(state->font_name != NULL)
	{
		free(state->font_name);
		state->font_name = NULL;
	}
	
	free(state);
	state = NULL;
}

/**
 * Cleans up save(). Destroys the stack.
 */
void canvas_save_cleanup(void)
{
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
