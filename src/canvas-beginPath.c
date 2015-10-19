/*
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

#include "canvas-beginPath.h"

static VGPath canvas_beginPath_immediate_path = 0;

/**
 * Initializes beginPath(). Generates a new immediate path for drawing rects,
 * paths, text, etc.
 */
void canvas_beginPath_init(void)
{
	canvas_beginPath_immediate_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, VG_PATH_CAPABILITY_ALL);
}

/**
 * Cleans up beginPath(). Destroys the immediate path.
 */
void canvas_beginPath_cleanup(void)
{
	vgDestroyPath(canvas_beginPath_immediate_path);
}

/**
 * The beginPath() method starts a new path by emptying the list of sub-paths.
 * Call this method when you want to create a new path.
 */
void canvas_beginPath(void)
{
	vgClearPath(canvas_beginPath_immediate_path, VG_PATH_CAPABILITY_ALL);
}

/**
 * Returns the immediate path for drawing.
 * @return The immediate path for drawing rects, paths, text, etc.
 */
VGPath canvas_beginPath_get(void)
{
	return canvas_beginPath_immediate_path;
}
