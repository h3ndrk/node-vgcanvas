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

#include "color.h"

void color_set_rgb(color_t *color, float red, float green, float blue)
{
	color->color_type = 0; // type: color
	
	color->red = red;
	color->green = green;
	color->blue = blue;
	color->alpha = 1;
}

void color_set_rgba(color_t *color, float red, float green, float blue, float alpha)
{
	color->color_type = 0; // type: color
	
	color->red = red;
	color->green = green;
	color->blue = blue;
	color->alpha = alpha;
}
