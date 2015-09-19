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
	#include "egl-util.h"
	#include "canvas.h"
}

#include <nan.h>

using namespace v8;

namespace infoscreen {

	bool checkArgs(const Nan::FunctionCallbackInfo<Value> &args, int expect) {

		if(args.Length() < expect) {
			Nan::ThrowTypeError("Not enough args");
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
	
	void GetFillStyle(const Nan::FunctionCallbackInfo<Value>& args) {
		color_t color = canvas_getState()->fillColor;
		
		Local<Array> array = Nan::New<Array>(4);
		
		array->Set(0, Nan::New(color.red));
		array->Set(1, Nan::New(color.green));
		array->Set(2, Nan::New(color.blue));
		array->Set(3, Nan::New(color.alpha));
		
		args.GetReturnValue().Set(array);
	}

	void GetScreenWidth(const Nan::FunctionCallbackInfo<Value>& args) {
		args.GetReturnValue().Set(Nan::New(egl_get_width()));
	}

	void GetScreenHeight(const Nan::FunctionCallbackInfo<Value>& args) {
		args.GetReturnValue().Set(Nan::New(egl_get_height()));
	}

	void SetLineWidth(const Nan::FunctionCallbackInfo<Value>& args) {
		if(!checkArgs(args, 1))
		return;

		canvas_lineWidth(args[0]->NumberValue());
	}
	
	void GetLineWidth(const Nan::FunctionCallbackInfo<Value>& args) {
		canvas_state_t *state = canvas_getState();
		
		args.GetReturnValue().Set(Nan::New(state->lineWidth));
	}

	void SetLineCap(const Nan::FunctionCallbackInfo<Value>& args) {
		if(args.Length() != 1 || !args[0]->IsString()) {
			Nan::ThrowTypeError("wrong arg");
			return;
		}

		std::string value(*Nan::Utf8String(args[0]));
		canvas_line_cap_t type = CANVAS_LINE_CAP_BUTT;

		if(value == "round")
		type = CANVAS_LINE_CAP_ROUND;
		else if(value == "butt")
		type = CANVAS_LINE_CAP_BUTT;
		else if(value == "square")
		type = CANVAS_LINE_CAP_SQUARE;

		canvas_lineCap(type);
	}
	
	void GetLineCap(const Nan::FunctionCallbackInfo<Value>& args) {
		canvas_state_t *state = canvas_getState();
		
		switch(state->lineCap)
		{
			case CANVAS_LINE_CAP_ROUND:
				args.GetReturnValue().Set(Nan::New("round").ToLocalChecked());
				break;
			case CANVAS_LINE_CAP_BUTT:
				args.GetReturnValue().Set(Nan::New("butt").ToLocalChecked());
				break;
			case CANVAS_LINE_CAP_SQUARE:
				args.GetReturnValue().Set(Nan::New("square").ToLocalChecked());
				break;
		}
		
	}

	void SetLineJoin(const Nan::FunctionCallbackInfo<Value>& args) {
		if(args.Length() != 1 || !args[0]->IsString()) {
			Nan::ThrowTypeError("wrong arg");
			return;
		}

		std::string value(*Nan::Utf8String(args[0]));
		canvas_line_join_t type = CANVAS_LINE_JOIN_MITER;

		if(value == "miter")
		type = CANVAS_LINE_JOIN_MITER;
		else if(value == "round")
		type = CANVAS_LINE_JOIN_ROUND;
		else if(value == "bevel")
		type = CANVAS_LINE_JOIN_BEVEL;

		canvas_lineJoin(type);
	}
	
	void GetLineJoin(const Nan::FunctionCallbackInfo<Value>& args) {
		canvas_state_t *state = canvas_getState();
		
		switch(state->lineJoin)
		{
			case CANVAS_LINE_JOIN_BEVEL:
				args.GetReturnValue().Set(Nan::New("bevel").ToLocalChecked());
				break;
			case CANVAS_LINE_JOIN_MITER:
				args.GetReturnValue().Set(Nan::New("miter").ToLocalChecked());
				break;
			case CANVAS_LINE_JOIN_ROUND:
				args.GetReturnValue().Set(Nan::New("round").ToLocalChecked());
				break;
		}
		
	}

	void SetStrokeStyle(const Nan::FunctionCallbackInfo<Value>& args) {
		if(!checkArgs(args, 4))
		return;

		canvas_strokeStyle_color(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue());
	}
	
	void GetStrokeStyle(const Nan::FunctionCallbackInfo<Value>& args) {
		color_t color = canvas_getState()->strokeColor;
		
		Local<Array> array = Nan::New<Array>(4);
		
		array->Set(0, Nan::New(color.red));
		array->Set(1, Nan::New(color.green));
		array->Set(2, Nan::New(color.blue));
		array->Set(3, Nan::New(color.alpha));
		
		args.GetReturnValue().Set(array);
	}

	void StrokeRect(const Nan::FunctionCallbackInfo<Value>& args) {
		if(!checkArgs(args, 4))
		return;

		canvas_strokeRect(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue());

	}

	void BeginPath(const Nan::FunctionCallbackInfo<Value>& args) {
		canvas_beginPath();
	}

	void ClosePath(const Nan::FunctionCallbackInfo<Value>& args) {
		canvas_closePath();
	}

	void MoveTo(const Nan::FunctionCallbackInfo<Value>& args) {
		if(!checkArgs(args, 2))
		return;

		canvas_moveTo(args[0]->NumberValue(), args[1]->NumberValue());
	}

	void LineTo(const Nan::FunctionCallbackInfo<Value>& args) {
		if(!checkArgs(args, 2))
		return;

		canvas_lineTo(args[0]->NumberValue(), args[1]->NumberValue());
	}

	void Stroke(const Nan::FunctionCallbackInfo<Value>& args) {
		canvas_stroke();
	}

	void Fill(const Nan::FunctionCallbackInfo<Value>& args) {
		canvas_fill();
	}

	void QuadraticCurveTo(const Nan::FunctionCallbackInfo<Value>& args) {
		if(!checkArgs(args, 4))
			return;

		canvas_quadraticCurveTo(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue());
	}

	void BezierCurveTo(const Nan::FunctionCallbackInfo<Value>& args) {
		if(!checkArgs(args, 6))
			return;

		canvas_bezierCurveTo(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue(), args[4]->NumberValue(), args[5]->NumberValue());
	}
	
	void Arc(const Nan::FunctionCallbackInfo<Value>& args) {
		if(!checkArgs(args, 5))
			return;
			
		bool acw = false;
		if(args.Length() > 5 && args[5]->IsBoolean())
			acw = args[5]->BooleanValue();
			
		canvas_arc(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue(), args[4]->NumberValue(), acw);
	}
	
	void Rect(const Nan::FunctionCallbackInfo<Value>& args) {
		if(!checkArgs(args, 4))
			return;
			
		canvas_rect(args[0]->NumberValue(), args[1]->NumberValue(), args[2]->NumberValue(), args[3]->NumberValue());
	}
	
	void SetLineDash(const Nan::FunctionCallbackInfo<Value>& args) {
		if(args.Length() != 1 || !args[0]->IsArray()) {
			Nan::ThrowTypeError("wrong arg");
			return;
		}
		
		Local<Array> ar = Local<Array>::Cast(args[0]);
		
		VGfloat data[ar->Length()];
		
		for(uint32_t i = 0; i < ar->Length(); i++) {
			data[i] = ar->Get(i)->NumberValue();
		}
		
		canvas_setLineDash(ar->Length(), data);
	}
	
	void GetLineDash(const Nan::FunctionCallbackInfo<Value>& args) {
		canvas_state_t *state = canvas_getState();
		VGfloat *pattern = state->dashPattern;
		VGint count = state->dashCount;
		
		Local<Array> array = Nan::New<Array>(count);
		
		for(int i = 0; i < count; i++) {
			array->Set(i, Nan::New(pattern[i]));
		}
		
		args.GetReturnValue().Set(array);
	}
	
	void SetLineDashOffset(const Nan::FunctionCallbackInfo<Value>& args) {
		if(!checkArgs(args, 1))
			return;
		
		canvas_lineDashOffset(args[0]->NumberValue());
	}
	
	void GetLineDashOffset(const Nan::FunctionCallbackInfo<Value>& args) {
		canvas_state_t *state = canvas_getState();
		
		args.GetReturnValue().Set(Nan::New(state->dashOffset));
	}
	
	void Clip(const Nan::FunctionCallbackInfo<Value>& args) {
		canvas_clip();
	}
	
	void Save(const Nan::FunctionCallbackInfo<Value>& args) {
		canvas_save();
	}
	
	void Restore(const Nan::FunctionCallbackInfo<Value>& args) {
		canvas_restore();
	}
	
	void SetGlobalAlpha(const Nan::FunctionCallbackInfo<Value>& args) {
		if(!checkArgs(args, 1))
			return;
			
		canvas_globalAlpha(args[0]->NumberValue());
	}
	
	void GetGlobalAlpha(const Nan::FunctionCallbackInfo<Value>& args) {
		args.GetReturnValue().Set(Nan::New(canvas_getState()->globalAlpha));
	}
	
	void ModuleInit(Local<Object> exports) {
		exports->Set(Nan::New("init").ToLocalChecked(), Nan::New<FunctionTemplate>(Init)->GetFunction());
		exports->Set(Nan::New("swapBuffers").ToLocalChecked(), Nan::New<FunctionTemplate>(SwapBuffers)->GetFunction());
		exports->Set(Nan::New("cleanup").ToLocalChecked(), Nan::New<FunctionTemplate>(Cleanup)->GetFunction());

		exports->Set(Nan::New("fillRect").ToLocalChecked(), Nan::New<FunctionTemplate>(FillRect)->GetFunction());
		exports->Set(Nan::New("clearRect").ToLocalChecked(), Nan::New<FunctionTemplate>(ClearRect)->GetFunction());
		exports->Set(Nan::New("strokeRect").ToLocalChecked(), Nan::New<FunctionTemplate>(StrokeRect)->GetFunction());

		exports->Set(Nan::New("setFillStyle").ToLocalChecked(), Nan::New<FunctionTemplate>(SetFillStyle)->GetFunction());
		exports->Set(Nan::New("setStrokeStyle").ToLocalChecked(), Nan::New<FunctionTemplate>(SetStrokeStyle)->GetFunction());
		exports->Set(Nan::New("getFillStyle").ToLocalChecked(), Nan::New<FunctionTemplate>(GetFillStyle)->GetFunction());
		exports->Set(Nan::New("getStrokeStyle").ToLocalChecked(), Nan::New<FunctionTemplate>(GetStrokeStyle)->GetFunction());

		exports->Set(Nan::New("getScreenWidth").ToLocalChecked(), Nan::New<FunctionTemplate>(GetScreenWidth)->GetFunction());
		exports->Set(Nan::New("getScreenHeight").ToLocalChecked(), Nan::New<FunctionTemplate>(GetScreenHeight)->GetFunction());

		exports->Set(Nan::New("setLineWidth").ToLocalChecked(), Nan::New<FunctionTemplate>(SetLineWidth)->GetFunction());
		exports->Set(Nan::New("setLineCap").ToLocalChecked(), Nan::New<FunctionTemplate>(SetLineCap)->GetFunction());
		exports->Set(Nan::New("setLineJoin").ToLocalChecked(), Nan::New<FunctionTemplate>(SetLineJoin)->GetFunction());
		exports->Set(Nan::New("setLineDash").ToLocalChecked(), Nan::New<FunctionTemplate>(SetLineDash)->GetFunction());
		exports->Set(Nan::New("setLineDashOffset").ToLocalChecked(), Nan::New<FunctionTemplate>(SetLineDashOffset)->GetFunction());

		exports->Set(Nan::New("getLineWidth").ToLocalChecked(), Nan::New<FunctionTemplate>(GetLineWidth)->GetFunction());
		exports->Set(Nan::New("getLineCap").ToLocalChecked(), Nan::New<FunctionTemplate>(GetLineCap)->GetFunction());
		exports->Set(Nan::New("getLineJoin").ToLocalChecked(), Nan::New<FunctionTemplate>(GetLineJoin)->GetFunction());
		exports->Set(Nan::New("getLineDash").ToLocalChecked(), Nan::New<FunctionTemplate>(GetLineDash)->GetFunction());
		exports->Set(Nan::New("getLineDashOffset").ToLocalChecked(), Nan::New<FunctionTemplate>(GetLineDashOffset)->GetFunction());

		exports->Set(Nan::New("setGlobalAlpha").ToLocalChecked(), Nan::New<FunctionTemplate>(SetGlobalAlpha)->GetFunction());
		exports->Set(Nan::New("getGlobalAlpha").ToLocalChecked(), Nan::New<FunctionTemplate>(GetGlobalAlpha)->GetFunction());

		exports->Set(Nan::New("beginPath").ToLocalChecked(), Nan::New<FunctionTemplate>(BeginPath)->GetFunction());
		exports->Set(Nan::New("closePath").ToLocalChecked(), Nan::New<FunctionTemplate>(ClosePath)->GetFunction());
		exports->Set(Nan::New("moveTo").ToLocalChecked(), Nan::New<FunctionTemplate>(MoveTo)->GetFunction());
		exports->Set(Nan::New("lineTo").ToLocalChecked(), Nan::New<FunctionTemplate>(LineTo)->GetFunction());
		exports->Set(Nan::New("stroke").ToLocalChecked(), Nan::New<FunctionTemplate>(Stroke)->GetFunction());
		exports->Set(Nan::New("fill").ToLocalChecked(), Nan::New<FunctionTemplate>(Fill)->GetFunction());

		exports->Set(Nan::New("quadraticCurveTo").ToLocalChecked(), Nan::New<FunctionTemplate>(QuadraticCurveTo)->GetFunction());
		exports->Set(Nan::New("bezierCurveTo").ToLocalChecked(), Nan::New<FunctionTemplate>(BezierCurveTo)->GetFunction());
		exports->Set(Nan::New("arc").ToLocalChecked(), Nan::New<FunctionTemplate>(Arc)->GetFunction());
		exports->Set(Nan::New("rect").ToLocalChecked(), Nan::New<FunctionTemplate>(Rect)->GetFunction());
		
		exports->Set(Nan::New("clip").ToLocalChecked(), Nan::New<FunctionTemplate>(Clip)->GetFunction());
		
		exports->Set(Nan::New("save").ToLocalChecked(), Nan::New<FunctionTemplate>(Save)->GetFunction());
		exports->Set(Nan::New("restore").ToLocalChecked(), Nan::New<FunctionTemplate>(Restore)->GetFunction());

	}

}

NODE_MODULE(vgcanvas, infoscreen::ModuleInit)
