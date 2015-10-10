/**
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

#ifndef __CANVAS_TEXTBASELINE_H__
#define __CANVAS_TEXTBASELINE_H__

typedef enum canvas_text_baseline_t
{
	CANVAS_TEXT_BASELINE_TOP,
	CANVAS_TEXT_BASELINE_HANGING,
	CANVAS_TEXT_BASELINE_MIDDLE,
	CANVAS_TEXT_BASELINE_ALPHABETIC,
	CANVAS_TEXT_BASELINE_IDEOGRAPHIC,
	CANVAS_TEXT_BASELINE_BOTTOM
} canvas_text_baseline_t;

void canvas_textBaseline(char *text_baseline);
char *canvas_textBaseline_get(void);

#endif /* __CANVAS_TEXTBASELINE_H__ */
