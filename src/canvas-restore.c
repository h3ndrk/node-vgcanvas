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
	
	if(state_top == NULL)
	{
		printf("Failed to restore top state of stack. No states in stack.\n");
		
		return;
	}
	
	state_beneath = state_top->next;
	state_top->next = NULL;
	
	canvas_save_set(state_beneath);
	
	// restore properties from top state in stack
	
	// something(canvas_save_stack_top->property);
	
	canvas_save_cleanup_state(state_top);
}
