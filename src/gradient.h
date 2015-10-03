#ifndef __GRADIENT_H__
#define __GRADIENT_H__

extern "C" {
	#include "canvas-paint.h"
}

#include <nan.h>

using namespace v8;

namespace vgcanvas {
	class Gradient : public Nan::ObjectWrap {
	public:
		Gradient();
		virtual ~Gradient();
		
		paint_t* GetPaint();
		
		static void Init(Local<Object> exports);
		static void New(const Nan::FunctionCallbackInfo<Value> &info);
		static void AddColorStop(const Nan::FunctionCallbackInfo<Value> &info);
		
	private:
		Gradient(const Gradient&);
		
		paint_t paint;
	};

}

#endif
