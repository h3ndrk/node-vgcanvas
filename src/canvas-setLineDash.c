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
#include "canvas-beginPath.h"
#include "canvas-setLineDash.h"

static VGfloat *canvas_setLineDash_data = NULL;
static VGint canvas_setLineDash_count = 0;

/**
 * The setLineDash() method sets the line dash pattern.
 * @param count The size of the array.
 * @param data An Array. A list of numbers that specifies distances to
 *             alternately draw a line and a gap (in coordinate space units).
 *             If the number of elements in the array is odd, the elements of
 *             the array get copied and concatenated. For example, [5, 15, 25]
 *             will become [5, 15, 25, 5, 15, 25]. This argument is irrelevant
 *             when count is 0.
 */
void canvas_setLineDash(VGint count, VGfloat *data)
{
	VGfloat *canvas_setLineDash_data_backup = canvas_setLineDash_data;
	
	if(count > 0)
	{
		if(canvas_setLineDash_data == NULL)
		{
			canvas_setLineDash_data = malloc(count * sizeof(VGfloat));
			
			if(canvas_setLineDash_data == NULL)
			{
				canvas_setLineDash_count = 0;
				
				printf("Failed to save lineDash data.\n");
				
				return;
			}
		}
		else
		{
			canvas_setLineDash_data = realloc(canvas_setLineDash_data, count * sizeof(VGfloat));
			
			if(canvas_setLineDash_data == NULL)
			{
				canvas_setLineDash_data = canvas_setLineDash_data_backup;
				
				printf("Failed to save lineDash data.\n");
				
				return;
			}
		}
		
		memcpy(canvas_setLineDash_data, data, count * sizeof(VGfloat));
		
		vgSetfv(VG_STROKE_DASH_PATTERN, count, (const VGfloat *)data);
	}
	else
	{
		if(canvas_setLineDash_data != NULL)
		{
			free(canvas_setLineDash_data);
			canvas_setLineDash_data = NULL;
		}
		
		vgSetfv(VG_STROKE_DASH_PATTERN, count, NULL);
	}
	
	canvas_setLineDash_count = count;
}

/**
 * Cleans up setLineDash(). Destroys saved dash pattern.
 */
void canvas_setLineDash_cleanup(void)
{
	if(canvas_setLineDash_data != NULL)
	{
		free(canvas_setLineDash_data);
		canvas_setLineDash_data = NULL;
	}
	
	canvas_setLineDash_count = 0;
}

/**
 * Returns the saved dash pattern data.
 * @return The saved dash pattern data.
 */
VGfloat *canvas_setLineDash_get_data(void)
{
	return canvas_setLineDash_data;
}

/**
 * Returns the saved dash pattern array size.
 * @return The saved dash pattern array size.
 */
VGint canvas_setLineDash_get_count(void)
{
	return canvas_setLineDash_count;
}
