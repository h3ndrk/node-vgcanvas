/*
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

#include <iostream>
#include "gradient.h"
#include "vgcanvas.h"

using namespace v8;

namespace vgcanvas {
	
	Nan::Persistent<Function> constructor;
	
	Gradient::Gradient() {

	}
	
	Gradient::~Gradient() {
		paint_cleanup(&paint);
	}
	
	void Gradient::Init(Local<Object> exports) {
		Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(Gradient::New);
		tpl->SetClassName(Nan::New("Gradient").ToLocalChecked());
		tpl->InstanceTemplate()->SetInternalFieldCount(1);
		
		Nan::SetPrototypeMethod(tpl, "addColorStopRGBA", Gradient::AddColorStop);
		
		constructor.Reset(tpl->GetFunction());
		exports->Set(Nan::New("Gradient").ToLocalChecked(), tpl->GetFunction());
	}
	
	void Gradient::New(const Nan::FunctionCallbackInfo<Value> &info) {
		if (info.IsConstructCall()) {
			Gradient *gradient = new Gradient();
			gradient->Wrap(info.This());
			info.GetReturnValue().Set(info.This());
			
			std::string typeStr(*Nan::Utf8String(info[0]));

			if(typeStr == "linear") {
				if(!checkArgs(info, 4, 1)) {
					Nan::ThrowTypeError("wrong args");
					return;
				}

				paint_createLinearGradient(gradient->GetPaint(), info[1]->NumberValue(), info[2]->NumberValue(),
					info[3]->NumberValue(), info[4]->NumberValue());

			} else if(typeStr == "radial") {
				if(!checkArgs(info, 5, 1)) {
					Nan::ThrowTypeError("wrong args");
					return;
				}

				paint_createRadialGradient(gradient->GetPaint(), info[1]->NumberValue(), info[2]->NumberValue(),
					info[3]->NumberValue(), info[4]->NumberValue(), info[5]->NumberValue());
			} else {
				Nan::ThrowTypeError("invalid type");
				return;
			}
			 
		} else {
			Nan::ThrowTypeError("not called as constructor");
		}
	}
	
	void Gradient::AddColorStop(const Nan::FunctionCallbackInfo<Value> &info) {
		if(!checkArgs(info, 5, 0)) {
			Nan::ThrowTypeError("wrong args");
			return;
		}
		
		Gradient* obj = Gradient::Unwrap<Gradient>(info.Holder());
		paint_addColorStop(obj->GetPaint(), info[0]->NumberValue(), info[1]->NumberValue(),
			info[2]->NumberValue(), info[3]->NumberValue(), info[4]->NumberValue());
		
	}
	
	paint_t* Gradient::GetPaint() {
		return &paint;
	}
	
}
