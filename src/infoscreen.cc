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

#include <nan.h>

using namespace v8;

namespace infoscreen {

bool checkArgs(const Nan::FunctionCallbackInfo<Value> &args, int expect) {

  if(args.Length() != expect) {
    Nan::ThrowTypeError("Wrong number of args");
    return false;
  }

  for(int i = 0; i < expect; i++) {
    if(!args[i]->IsNumber()) {
      Nan::ThrowTypeError("Wrong arg");
      return false;
    }
  }

  return true;

}

void Init(const Nan::FunctionCallbackInfo<Value>& args) {
  canvas__init();
}

void SwapBuffers(const Nan::FunctionCallbackInfo<Value>& args) {
  egl_swap_buffers();
}

void Cleanup(const Nan::FunctionCallbackInfo<Value>& args) {
  canvas__cleanup();
}

void FillRect(const Nan::FunctionCallbackInfo<Value>& args) {
  if(!checkArgs(args, 4))
    return;

  canvas_fillRect(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue());
}

void ClearRect(const Nan::FunctionCallbackInfo<Value>& args) {
  if(!checkArgs(args, 4))
    return;

  canvas_clearRect(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue());
}

void SetFillStyle(const Nan::FunctionCallbackInfo<Value>& args) {
  if(!checkArgs(args, 4))
    return;

  canvas_fillStyle_color(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue());
}

void GetScreenWidth(const Nan::FunctionCallbackInfo<Value>& args) {
  args.GetReturnValue().Set(Nan::New(egl_get_width()));
}

void GetScreenHeight(const Nan::FunctionCallbackInfo<Value>& args) {
  args.GetReturnValue().Set(Nan::New(egl_get_height()));
}

void ModuleInit(Local<Object> exports) {
  exports->Set(Nan::New("init").ToLocalChecked(), Nan::New<FunctionTemplate>(Init)->GetFunction());
  exports->Set(Nan::New("swapBuffers").ToLocalChecked(), Nan::New<FunctionTemplate>(SwapBuffers)->GetFunction());
  exports->Set(Nan::New("cleanup").ToLocalChecked(), Nan::New<FunctionTemplate>(Cleanup)->GetFunction());

  exports->Set(Nan::New("fillRect").ToLocalChecked(), Nan::New<FunctionTemplate>(FillRect)->GetFunction());
  exports->Set(Nan::New("clearRect").ToLocalChecked(), Nan::New<FunctionTemplate>(ClearRect)->GetFunction());
  exports->Set(Nan::New("setFillStyle").ToLocalChecked(), Nan::New<FunctionTemplate>(SetFillStyle)->GetFunction());

  exports->Set(Nan::New("getScreenWidth").ToLocalChecked(), Nan::New<FunctionTemplate>(GetScreenWidth)->GetFunction());
  exports->Set(Nan::New("getScreenHeight").ToLocalChecked(), Nan::New<FunctionTemplate>(GetScreenHeight)->GetFunction());

}

NODE_MODULE(vgcanvas, ModuleInit)

}
