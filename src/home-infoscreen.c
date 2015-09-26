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

#include <stdio.h>
#include <math.h>

#include "egl-util.h"
#include "canvas.h"
#include "color.h"

int main(void)
{
	char s[3];
	
	canvas__init();
	
	canvas_clearRect(0, 0, egl_get_width(), egl_get_height());
	canvas_lineWidth(2);
	
	paint_t paint;
	paint_createColor(&paint, 1, 0, 0, 1);
	canvas_fillStyle(&paint);
	
	canvas_fillRect(250, 100, 100, 100);
	
	paint_t gradient;
	paint_createLinearGradient(&gradient, 0, 0, 100, 0);
	paint_addColorStop(&gradient, 0, 0, 0, 1, 1);
	paint_addColorStop(&gradient, 0.5f, 1, 0, 0, 1);
	paint_addColorStop(&gradient, 1, 0, 1, 1, 1);
	canvas_fillStyle(&gradient);
	canvas_fillRect(100, 250, 500, 100);
	
	canvas_strokeStyle(&gradient);
	canvas_strokeRect(100, 100, 100, 100);
	
	canvas_fillStyle(&paint);
	canvas_fillRect(400, 100, 100, 100);
	
	egl_swap_buffers();
	
	printf("Press <Enter> to shutdown.\n");
	fgets(s, 2, stdin);
	
	paint_destroy(&paint);
	paint_destroy(&gradient);
	canvas__cleanup();
	
	return 0;
}
