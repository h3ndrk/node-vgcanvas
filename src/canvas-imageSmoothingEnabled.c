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

#include "canvas-imageSmoothingEnabled.h"

static VGboolean canvas_imageSmoothingEnabled_value = VG_TRUE;

/**
 * The imageSmoothingEnabled property can be set to change if images are
 * smoothed (true, default) or not (false).
 * @param image_smoothing_enabled A Boolean indicating whether to smooth images
 *                                or not.
 */
void canvas_imageSmoothingEnabled(VGboolean image_smoothing_enabled)
{
	vgSeti(VG_IMAGE_QUALITY, image_smoothing_enabled ? VG_IMAGE_QUALITY_BETTER : VG_IMAGE_QUALITY_NONANTIALIASED);
}

/**
 * Returns the current value (true by default).
 * @return A boolean value specifying .
 */
VGboolean canvas_imageSmoothingEnabled_get(void)
{
	return canvas_imageSmoothingEnabled_value;
}
