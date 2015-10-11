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

#ifndef __CANVAS_TEXTALIGN_H__
#define __CANVAS_TEXTALIGN_H__

typedef enum canvas_text_align_t
{
	CANVAS_TEXT_ALIGN_LEFT,
	CANVAS_TEXT_ALIGN_RIGHT,
	CANVAS_TEXT_ALIGN_CENTER
} canvas_text_align_t;

void canvas_textAlign(char *text_align);
char *canvas_textAlign_get(void);
canvas_text_align_t canvas_textAlign_get_internal(void);

#endif /* __CANVAS_TEXTALIGN_H__ */
