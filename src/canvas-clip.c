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
#include "canvas-clip.h"

static VGboolean canvas_clip_clipping = VG_FALSE;

/**
 * Initializes clip(). Disables masking by default.
 */
void canvas_clip_init(void)
{
	vgSeti(VG_MASKING, VG_FALSE);
}

/**
 * The closePath() method causes the point of the pen to move back to the start
 * of the current sub-path. It tries to add a straight line (but does not
 * actually draw it) from the current point to the start. If the shape has
 * already been closed or has only one point, this function does nothing.
 */
void canvas_clip(void)
{
	if(!canvas_clip_clipping)
	{
		vgMask(VG_INVALID_HANDLE, VG_FILL_MASK, 0, 0, egl_get_width(), egl_get_height());
	}
	
	vgRenderToMask(canvas_beginPath_get(), VG_FILL_PATH, VG_INTERSECT_MASK);
	
	vgSeti(VG_MASKING, VG_TRUE);
	
	canvas_clip_clipping = VG_TRUE;
}

/**
 * Returns the clipping state.
 * @return The clipping state.
 */
VGboolean canvas_clip_get_clipping(void)
{
	return canvas_clip_clipping;
}

/**
 * Sets the clipping state.
 * @param clipping The clipping state.
 */
void canvas_clip_set_clipping(VGboolean clipping)
{
	vgSeti(VG_MASKING, clipping);
	
	canvas_clip_clipping = clipping;
}

/**
 * Returns a newly created clipping mask layer. This mask must be destroyed by
 * canvas_clip_cleanup_mask().
 * @return The newly created clipping mask layer. This mask must be destroyed by
 *         canvas_clip_cleanup_mask().
 */
VGMaskLayer canvas_clip_get_mask(void)
{
	VGMaskLayer mask = vgCreateMaskLayer(egl_get_width(), egl_get_height());
	vgCopyMask(mask, 0, 0, 0, 0, egl_get_width(), egl_get_height());
	
	return mask;
}

/**
 * Sets the clipping mask layer.
 * @param mask The clipping mask layer.
 */
void canvas_clip_set_mask(VGMaskLayer mask)
{
	vgMask(mask, VG_SET_MASK, 0, 0, egl_get_width(), egl_get_height());
}

/**
 * Cleans up the given clipping mask layer.
 * @param mask The clipping mask layer.
 */
void canvas_clip_cleanup_mask(VGMaskLayer mask)
{
	vgDestroyMaskLayer(mask);
}
