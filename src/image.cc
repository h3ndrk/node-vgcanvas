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

#include <iostream>
#include <cstdio>
#include "image.h"
#include "vgcanvas.h"

using namespace v8;

namespace vgcanvas {
	
	struct AsyncData {
		uv_work_t req;
		Nan::Persistent<Object> obj;
		std::string *path;
		FIBITMAP *bitmap;
	};
	
	Image::Image() : path(""), image(0) {

	}
	
	Image::~Image() {
		if(GetImage()) {
			std::cout << "Cleaning up image " << GetPath()->c_str() << "\n";
			image_cleanup(image);
		}
	}
	
	void Image::Init(Local<Object> exports) {
		Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(Image::New);
		tpl->SetClassName(Nan::New("Image").ToLocalChecked());
		
		Local<ObjectTemplate> obj = tpl->InstanceTemplate();
		obj->SetAccessor(Nan::New("width").ToLocalChecked(), Image::GetSize);
		obj->SetAccessor(Nan::New("height").ToLocalChecked(), Image::GetSize);
		obj->SetAccessor(Nan::New("src").ToLocalChecked(), Image::GetSrc, Image::SetSrc);
		obj->SetInternalFieldCount(1);
		
		Nan::SetPrototypeMethod(tpl, "setData", Image::SetData);
		
		exports->Set(Nan::New("Image").ToLocalChecked(), tpl->GetFunction());
	}
	
	void Image::New(const Nan::FunctionCallbackInfo<Value> &info) {
		if (info.IsConstructCall()) {
			Image *gradient = new Image();
			gradient->Wrap(info.This());
			info.GetReturnValue().Set(info.This());
		} else {
			Nan::ThrowTypeError("not called as constructor");
		}
	}
	
	void Image::GetSize(Local<String> property, const PropertyCallbackInfo<Value>& info) {
		Image* obj = Image::Unwrap<Image>(info.Holder());
		std::string str(*Nan::Utf8String(property));
		
		if(!obj->GetImage()) {
			info.GetReturnValue().Set(Nan::New(0));
			return;
		}
		
		if(str == "width") {
			info.GetReturnValue().Set(Nan::New(obj->GetImage()->width));
		} else if(str == "height") {
			info.GetReturnValue().Set(Nan::New(obj->GetImage()->height));
		}
	}
	
	void LoadImage(uv_work_t *req) {
		AsyncData *data = static_cast<AsyncData*>(req->data);
		data->bitmap = image_load_bitmap(data->path->c_str());
	}
	
	void FinishedLoading(uv_work_t *req, int status) {
		Nan::HandleScope scope;
		
		AsyncData *data = static_cast<AsyncData*>(req->data);
		Local<Object> localObj = Nan::New(data->obj);
		Image *obj = Image::Unwrap<Image>(localObj);
		bool hasOnLoad = localObj->HasRealNamedProperty(Nan::New("onload").ToLocalChecked());
		bool hasOnError = localObj->HasRealNamedProperty(Nan::New("onerror").ToLocalChecked());
		
		if(!data->bitmap) {
			if(hasOnError) {
				std::string msg = "Failed to create image: ";
				msg += strerror(errno);
				Local<Value> error = Nan::Error(msg.c_str());
				Local<Function> func = Local<Function>::Cast(localObj->GetRealNamedProperty(Nan::New("onerror").ToLocalChecked()));
				func->Call(localObj, 1, &error);
			}
			
			data->obj.Reset();
			return;
		}
		
		std::cout << "Finished loading " << data->path->c_str() << "\n";
		
		obj->SetImage(image_create(VG_sARGB_8888,  FreeImage_GetWidth(data->bitmap),  FreeImage_GetHeight(data->bitmap), FreeImage_GetBits(data->bitmap)));
		image_free_bitmap(data->bitmap);
		
		if(!obj->GetImage()) {
			if(hasOnError) {
				Local<Value> error = Nan::Error("Failed to create image");
				Local<Function> func = Local<Function>::Cast(localObj->GetRealNamedProperty(Nan::New("onerror").ToLocalChecked()));
				func->Call(localObj, 1, &error);
			}
			data->obj.Reset();
			return;
		}
		
		
		if(hasOnLoad) {
			Local<Function> func = Local<Function>::Cast(localObj->GetRealNamedProperty(Nan::New("onload").ToLocalChecked()));
			func->Call(localObj, 0, NULL);
		}
		
		data->obj.Reset();
		delete data;
		
	}
	
	void Image::SetSrc(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info) {
		Image* obj = Image::Unwrap<Image>(info.Holder());
		if(!value->IsString()) {
			Nan::ThrowTypeError("not a string");
			return;
		}
		
		obj->path = *Nan::Utf8String(value);
		AsyncData *data = new AsyncData;
		data->req.data = data;
		data->path = obj->GetPath();
		data->obj.Reset(info.Holder());
		
		uv_queue_work(uv_default_loop(), &data->req, LoadImage, FinishedLoading);
		
	}
	
	void Image::GetSrc(Local<String> property, const PropertyCallbackInfo<Value>& info) {
		Image* obj = Image::Unwrap<Image>(info.Holder());
		info.GetReturnValue().Set(Nan::New(obj->GetPath()->c_str()).ToLocalChecked());
	}
	
	void Image::SetData(const Nan::FunctionCallbackInfo<Value> &info) {
		if(info.Length() != 3 || !info[0]->IsUint8ClampedArray() || !checkArgs(info, 2, 1)) {
			Nan::ThrowTypeError("wrong arg");
			return;
		}
		
		Image* obj = Image::Unwrap<Image>(info.Holder());
		
		Local<ArrayBufferView> bufferView = Local<ArrayBufferView>::Cast(info[0]);
		if(!bufferView->HasBuffer()) {
			Nan::ThrowError("array does not have buffer");
			return;
		}
		
		ArrayBuffer::Contents contents = bufferView->Buffer()->GetContents();
		VGint width = info[1]->NumberValue();
		VGint height = info[2]->NumberValue();
		
		if(width * height * 4 != contents.ByteLength()) {
			Nan::ThrowError("lengths do not match");
		}
		
		if(obj->GetImage()) {
			image_cleanup(obj->GetImage());
		}
		
		obj->SetImage(image_create(VG_sABGR_8888, width, height, contents.Data()));
		
	}
	
	image_t* Image::GetImage() {
		return this->image;
	}
	
	void Image::SetImage(image_t *img) {
		this->image = img;
	}
	
	std::string* Image::GetPath() {
		return &this->path;
	}
	
}
