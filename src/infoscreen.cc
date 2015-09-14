/**
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

extern "C" {
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <assert.h>
  #include "EGL/egl.h"
  #include "GLES/gl.h"
  #include "bcm_host.h"
  #include "VG/openvg.h"
  #include "VG/vgu.h"
  #include "VG/vgext.h"

  #include "egl-util.h"
  #include "canvas.h"
}

#include <iostream>
#include <node.h>


using namespace v8;

namespace infoscreen {

bool checkArgs(const FunctionCallbackInfo<Value> &args, int expect) {
  Isolate *isolate = args.GetIsolate();

  if(args.Length() != expect) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of args")));
    return false;
  }

  for(int i = 0; i < expect; i++) {
    if(!args[i]->IsNumber()) {
      isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arg")));
      return false;
    }
  }

  return true;

}

void Init(const FunctionCallbackInfo<Value>& args) {
  canvas__init();
}

void SwapBuffers(const FunctionCallbackInfo<Value>& args) {
  egl_swap_buffers();
}

void Cleanup(const FunctionCallbackInfo<Value>& args) {
  canvas__cleanup();
}

void FillRect(const FunctionCallbackInfo<Value>& args) {
  if(!checkArgs(args, 4))
    return;

  canvas_fillRect(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue());
}

void ClearRect(const FunctionCallbackInfo<Value>& args) {
  if(!checkArgs(args, 4))
    return;

  canvas_clearRect(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue());
}

void SetFillStyle(const FunctionCallbackInfo<Value>& args) {
  if(!checkArgs(args, 4))
    return;

  canvas_fillStyle_color(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue());
}

void GetScreenWidth(const FunctionCallbackInfo<Value>& args) {
  args.GetReturnValue().Set(Number::New(args.GetIsolate(), egl_get_width()));
}

void GetScreenHeight(const FunctionCallbackInfo<Value>& args) {
  args.GetReturnValue().Set(Number::New(args.GetIsolate(), egl_get_height()));
}

void ModuleInit(Local<Object> exports) {
  NODE_SET_METHOD(exports, "init", Init);
  NODE_SET_METHOD(exports, "swapBuffers", SwapBuffers);
  NODE_SET_METHOD(exports, "cleanup", Cleanup);
  NODE_SET_METHOD(exports, "fillRect", FillRect);
  NODE_SET_METHOD(exports, "clearRect", ClearRect);
  NODE_SET_METHOD(exports, "setFillStyle", SetFillStyle);

  NODE_SET_METHOD(exports, "getScreenWidth", GetScreenWidth);
  NODE_SET_METHOD(exports, "getScreenHeight", GetScreenHeight);
}

NODE_MODULE(vgcanvas, ModuleInit)

}
