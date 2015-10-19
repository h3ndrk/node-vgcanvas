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
		std::cout << "Finished loading " << data->path->c_str() << "\n";
		
		Local<Object> localObj = Nan::New(data->obj);
		Image *obj = Image::Unwrap<Image>(localObj);
		
		obj->SetImage(image_create(data->bitmap));
		image_free_bitmap(data->bitmap);
		
		if(!obj->GetImage()) {
			Nan::ThrowTypeError("Failed to load image");
			data->obj.Reset();
			return;
		}
		
		bool hasProp = localObj->HasRealNamedProperty(Nan::New("onload").ToLocalChecked());
		if(hasProp) {
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
