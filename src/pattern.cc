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

#include "pattern.h"
#include "vgcanvas.h"
#include "image.h"

using namespace v8;

namespace vgcanvas {
	
	Pattern::Pattern() {

	}
	
	Pattern::~Pattern() {
		paint_cleanup(&paint);
	}
	
	void Pattern::Init(Local<Object> exports) {
		Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(Pattern::New);
		tpl->SetClassName(Nan::New("Pattern").ToLocalChecked());
		tpl->InstanceTemplate()->SetInternalFieldCount(1);
		
		exports->Set(Nan::New("Pattern").ToLocalChecked(), tpl->GetFunction());
	}
	
	void Pattern::New(const Nan::FunctionCallbackInfo<Value> &info) {
		if (info.IsConstructCall()) {
			Pattern *pattern = new Pattern();
			pattern->Wrap(info.This());
			info.GetReturnValue().Set(info.This());
			
			std::string typeStr(*Nan::Utf8String(info[0]));

			if(info.Length() != 2 || !info[0]->IsObject() || !info[1]->IsString()) {
				Nan::ThrowTypeError("wrong arg");
				return;
			}
			
			Image *img = Image::Unwrap<Image>(Local<Object>::Cast(info[0]));
			
			if(!img->GetImage()) {
				std::string mode(*Nan::Utf8String(info[1]));
				paint_createPattern(pattern->GetPaint(), img->GetImage(), mode == "no-repeat" ? VG_TILE_FILL : VG_TILE_REPEAT);
			} else {
				Nan::ThrowError("invalid image");
				return;
			}
		} else {
			Nan::ThrowTypeError("not called as constructor");
		}
	}
	
	paint_t* Pattern::GetPaint() {
		return &paint;
	}
	
}
