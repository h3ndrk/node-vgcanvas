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

static VGboolean smoothing_value = VG_TRUE;

/**
 * The imageSmoothing property can be set to change if images are smoothed (true, default) or not (false).
 * @param smoothing A Boolean indicating whether to smooth images or not.
 */
void canvas_imageSmoothing(VGboolean smoothing)
{
	vgSeti(VG_IMAGE_QUALITY, smoothing ? VG_IMAGE_QUALITY_BETTER : VG_IMAGE_QUALITY_NONANTIALIASED);
}

/**
 * Returns the current value (true by default).
 * @return A boolean value specifying .
 */
VGboolean canvas_imageSmoothing_get(void)
{
	return smoothing_value;
}
