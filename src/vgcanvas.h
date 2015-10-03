#ifndef __VGCANVAS_H__
#define __VGCANVAS_H__

#include <nan.h>

namespace vgcanvas {
	bool checkArgs(const Nan::FunctionCallbackInfo<v8::Value> &info, int expect, int offset);
}

#endif
