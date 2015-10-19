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

#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <string>
#include <nan.h>

extern "C" {
	#include "image-util.h"
}

using namespace v8;

namespace vgcanvas {
	class Image : public Nan::ObjectWrap {
	public:
		Image();
		virtual ~Image();
		image_t* GetImage();
		std::string* GetPath();
		void SetImage(image_t *image);
		
		static void Init(Local<Object> exports);
		static void New(const Nan::FunctionCallbackInfo<Value> &info);
		static void GetSize(Local<String> property, const PropertyCallbackInfo<Value>& info);
		static void SetSrc(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);
		static void GetSrc(Local<String> property, const PropertyCallbackInfo<Value>& info);
		
	private:
		Image(const Image&);
		
		std::string path;
		image_t *image;
		
	};

}

#endif
