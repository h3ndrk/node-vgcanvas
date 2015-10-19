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

#ifndef __CANVAS_MEASURETEXT_H__
#define __CANVAS_MEASURETEXT_H__

#include <VG/openvg.h>

typedef struct canvas_measure_text_metrics_t
{
	VGfloat font_size;
	VGfloat width;
	VGfloat height;
	VGfloat actual_bounding_box_left;
	VGfloat actual_bounding_box_right;
	VGfloat actual_bounding_box_ascent;
	VGfloat actual_bounding_box_descent;
	VGfloat font_bounding_box_ascent;
	VGfloat font_bounding_box_descent;
	VGfloat em_height_ascent;
	VGfloat em_height_descent;
	VGfloat hanging_baseline;
	VGfloat alphabetic_baseline;
	VGfloat ideographic_baseline;
	VGfloat rendering_offset_x;
	VGfloat rendering_offset_y;
} canvas_measure_text_metrics_t;

void canvas_measureText(canvas_measure_text_metrics_t *metrics, char *text);

#endif /* __CANVAS_MEASURETEXT_H__ */
