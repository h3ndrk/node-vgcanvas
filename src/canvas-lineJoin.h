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

#ifndef __CANVAS_LINEJOIN_H__
#define __CANVAS_LINEJOIN_H__

typedef enum canvas_line_join_t
{
	CANVAS_LINE_JOIN_MITER = VG_JOIN_MITER,
	CANVAS_LINE_JOIN_ROUND = VG_JOIN_ROUND,
	CANVAS_LINE_JOIN_BEVEL = VG_JOIN_BEVEL
} canvas_line_join_t;

void canvas_lineJoin(char *line_join);
char *canvas_lineJoin_get(void);

#endif /* __CANVAS_LINEJOIN_H__ */
