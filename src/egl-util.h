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

#ifndef __GL_UTIL_H__
#define __GL_UTIL_H__

void egl_init(void);
void egl_cleanup(void);
EGLint egl_error(void);
void egl_swap_buffers(void);
EGLDisplay egl_get_display(void);
EGLSurface egl_get_display(void);
EGLContext egl_get_display(void);
uint32_t egl_get_width(void);
uint32_t egl_get_height(void);

#endif /* __GL_UTIL_H__ */
