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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "EGL/egl.h"
#include "GLES/gl.h"
#include "bcm_host.h"

static EGLDisplay display;
static EGLContext context;
static EGLSurface surface;

uint32_t screen_width;
uint32_t screen_height;

static EGLConfig config;

void egl_init(void)
{
	EGLBoolean result;
	int32_t success = 0;
	static EGL_DISPMANX_WINDOW_T nativewindow;
	
	static const EGLint attribute_list[] = {
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_ALPHA_MASK_SIZE, 8,
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT & EGL_SWAP_BEHAVIOR_PRESERVED_BIT,
		EGL_NONE
	};
	
	EGLint num_config;
	
	VC_RECT_T dst_rect;
	VC_RECT_T src_rect;
	DISPMANX_ELEMENT_HANDLE_T dispman_element;
	DISPMANX_DISPLAY_HANDLE_T dispman_display;
	DISPMANX_UPDATE_HANDLE_T  dispman_update;
	
	// bcm_host_init() must be called before anything else
	bcm_host_init();
	
	// get an EGL display connection
	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	
	result = eglInitialize(display, NULL, NULL);
	assert(EGL_FALSE != result);
	
	// bind OpenVG API
	eglBindAPI(EGL_OPENVG_API);
	
	// get an appropriate EGL frame buffer configuration
	result = eglChooseConfig(display, attribute_list,
		&config, 1, &num_config);
	assert(EGL_FALSE != result);
	
	// create an EGL rendering context
	context = eglCreateContext(display, config, EGL_NO_CONTEXT, NULL);
	assert(context != EGL_NO_CONTEXT);
	
	// create an EGL window surface
	success = graphics_get_display_size(0 /* LCD */ , &screen_width,
	&screen_height);
	assert(success >= 0);
	
	printf("Display size: %i x %i\n", screen_width, screen_height);
	
	dst_rect.x = 0;
	dst_rect.y = 0;
	dst_rect.width  = screen_width;
	dst_rect.height = screen_height;
	
	src_rect.x = 0;
	src_rect.y = 0;
	src_rect.width  = screen_width  << 16;
	src_rect.height = screen_height << 16;
	
	dispman_display = vc_dispmanx_display_open(0 /* LCD */ );
	dispman_update  = vc_dispmanx_update_start(0);
	
	dispman_element = vc_dispmanx_element_add(dispman_update, dispman_display, 0 /*layer */ , &dst_rect, 0 /*src */ , &src_rect, DISPMANX_PROTECTION_NONE, 0 /*alpha */ , 0 /*clamp */ , DISPMANX_NO_ROTATE /*transform */);
	
	nativewindow.element = dispman_element;
	nativewindow.width   = screen_width;
	nativewindow.height  = screen_height;
	vc_dispmanx_update_submit_sync(dispman_update);
	
	surface = eglCreateWindowSurface(display, config, &nativewindow, NULL);
	assert(surface != EGL_NO_SURFACE);
	
	// connect the context to the surface
	result = eglMakeCurrent(display, surface, surface, context);
	assert(EGL_FALSE != result);
	
	// preserve color buffer when swapping
	eglSurfaceAttrib(display, surface, EGL_SWAP_BEHAVIOR, EGL_BUFFER_PRESERVED);
}

// Code from https://github.com/ajstarks/openvg/blob/master/oglinit.c doesn't
// seem necessary.
void egl_init_open_gles(void)
{
	//DAVE - Set up screen ratio
	glViewport(0, 0, (GLsizei) screen_width, (GLsizei) screen_height);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	float ratio = (float)screen_width / (float)screen_height;
	glFrustumf(-ratio, ratio, -1.0f, 1.0f, 1.0f, 10.0f);
}

void egl_finish(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	eglSwapBuffers(display, surface);
	eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroySurface(display, surface);
	eglDestroyContext(display, context);
	eglTerminate(display);
	
	bcm_host_deinit();
}

int main(void)
{
	egl_init();
	egl_init_open_gles();
	
	printf("Started.\n");
	
	sleep(5);
	
	printf("Shutting down.\n");
	
	egl_finish();
	
	return 0;
}
