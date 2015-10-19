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

#ifndef __CANVAS_BEZIERCURVETO_H__
#define __CANVAS_BEZIERCURVETO_H__

#include <VG/openvg.h>

void canvas_bezierCurveTo(VGfloat cp1x, VGfloat cp1y, VGfloat cp2x, VGfloat cp2y, VGfloat x, VGfloat y);

#endif /* __CANVAS_BEZIERCURVETO_H__ */
