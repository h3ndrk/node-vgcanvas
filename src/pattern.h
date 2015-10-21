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


#ifndef __PATTERN_H__
#define __PATTERN_H__

extern "C" {
	#include "canvas-paint.h"
}

#include <nan.h>

using namespace v8;

namespace vgcanvas {
	class Pattern : public Nan::ObjectWrap {
	public:
		Pattern();
		virtual ~Pattern();
		
		paint_t* GetPaint();
		
		static void Init(Local<Object> exports);
		static void New(const Nan::FunctionCallbackInfo<Value> &info);
		
	private:
		Pattern(const Pattern&);
		
		paint_t paint;
	};

}

#endif
