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

#ifndef __CANVAS_CLIP_H__
#define __CANVAS_CLIP_H__

#include <VG/openvg.h>

void canvas_clip_init(void);
void canvas_clip(void);
VGboolean canvas_clip_get_clipping(void);
void canvas_clip_set_clipping(VGboolean clipping);
VGMaskLayer canvas_clip_get_mask(void);
void canvas_clip_set_mask(VGMaskLayer mask);
void canvas_clip_cleanup_mask(VGMaskLayer mask);

#endif /* __CANVAS_CLIP_H__ */
