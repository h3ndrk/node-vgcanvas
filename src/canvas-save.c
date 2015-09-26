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
	
	// save properties to stack top
	
	// canvas_save_stack_top->property = something;
}

/**
 * Cleans up specific stack states. Destroys the given state of the stack.
 * @param state The state to be destroyed.
 */
static canvas_save_cleanup_state(canvas_save_stack_t *state)
{
	if(state->next != NULL)
	{
		canvas_save_cleanup_state(state->next);
	}
	
	// cleanup properties of stack top
	
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
