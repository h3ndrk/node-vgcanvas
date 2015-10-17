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
