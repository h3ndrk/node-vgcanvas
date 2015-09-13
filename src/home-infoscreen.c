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
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "EGL/egl.h"
#include "GLES/gl.h"
#include "bcm_host.h"
#include "VG/openvg.h"
#include "VG/vgu.h"
#include "VG/vgext.h"

#include "egl-util.h"
#include "canvas.h"

int main(void)
{
	canvas__init();
	
	canvas_clearRect(0, 0, egl_get_width(), egl_get_height());
	
	canvas_lineWidth(10);
	
	canvas_fillStyle_color(1, 0, 0, 1);
	
	canvas_fillRect(100, 100, 100, 100);
	canvas_globalAlpha(0.5);
	canvas_fillStyle_color(1, 1, 0, 1);
	canvas_fillRect(150, 150, 100, 100);
	
	canvas_strokeStyle_color(1, 1, 1, 1);
	canvas_globalAlpha(1);
	
	canvas_beginPath();
	canvas_moveTo(300, 300);
	canvas_lineTo(200, 200);
	canvas_quadraticCurveTo(100, -150, 200, -200);
	canvas_bezierCurveTo(-100, -150, -110, -190, -200, -200);
	canvas_ellipse(500, 500, 100, 200, 0, 0, 0, VG_FALSE);
	canvas_closePath();
	canvas_fill();
	canvas_stroke();
	
	egl_swap_buffers();
	
	sleep(5);
	
	canvas__cleanup();
	
	return 0;
}
