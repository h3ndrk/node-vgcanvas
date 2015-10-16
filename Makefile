# Copyright (C) 2015 NIPE-SYSTEMS
# Copyright (C) 2015 Hauke Oldsen
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

CC = gcc

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -I /opt/vc/include
CFLAGS += -I /opt/vc/include/interface/vmcs_host/linux
CFLAGS += -I /opt/vc/include/interface/vcos/pthreads
CFLAGS += -I /usr/include/freetype2
# CFLAGS += -I./etc
CFLAGS += -fgnu89-inline # fix for vcos compiler warnings

LIBS += -lm
LIBS += -L /opt/vc/lib
LIBS += -lGLESv2
LIBS += -lEGL
LIBS += -lopenmaxil
LIBS += -lbcm_host
LIBS += -lvcos
LIBS += -lvchiq_arm
LIBS += -lpthread
LIBS += -lrt
LIBS += -lfreetype
LIBS += -lfreeimage
# LIBS += -lbcm_host
# LIBS += -lpthread
# LIBS += -ljpeg

PROGRAM_NAME = home-infoscreen

SRC += $(PROGRAM_NAME).c
SRC += canvas-beginPath.c
SRC += canvas-bezierCurveTo.c
SRC += canvas-clearRect.c
SRC += canvas-globalAlpha.c
SRC += canvas-lineCap.c
SRC += canvas-lineDashOffset.c
SRC += canvas-lineJoin.c
SRC += canvas-lineTo.c
SRC += canvas-lineWidth.c
SRC += canvas-moveTo.c
SRC += canvas-quadraticCurveTo.c
SRC += canvas-arc.c
SRC += canvas-rect.c
SRC += canvas-setLineDash.c
SRC += canvas-closePath.c
SRC += canvas-clip.c
SRC += canvas-kerning.c
SRC += canvas-save.c
SRC += canvas-restore.c
SRC += canvas-measureText.c
SRC += canvas-miterLimit.c
SRC += canvas.c
SRC += canvas-paint.c
SRC += canvas-font.c
SRC += canvas-fill.c
SRC += canvas-fillStyle.c
SRC += canvas-fillRect.c
SRC += canvas-fillText.c
SRC += canvas-rotate.c
SRC += canvas-scale.c
SRC += canvas-stroke.c
SRC += canvas-strokeStyle.c
SRC += canvas-strokeRect.c
SRC += canvas-strokeText.c
SRC += canvas-drawImage.c
SRC += canvas-textAlign.c
SRC += canvas-textBaseline.c
SRC += canvas-translate.c
SRC += egl-util.c
SRC += font-util.c
SRC += image-util.c

OBJS = $(addprefix bin/obj/, $(SRC:%.c=%.o))

.PHONY: all $(PROGRAM_NAME) fonttoopenvg init clean

all: init $(PROGRAM_NAME)

fonttoopenvg: src/fonttoopenvg.cpp
	g++ -I/usr/include/freetype2 src/fonttoopenvg.cpp -o font2openvg -lfreetype
	
font: src/font.c
	gcc -I/usr/include/freetype2 src/font.c -o font -lfreetype

$(PROGRAM_NAME): init $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o bin/$(PROGRAM_NAME) $(LIBS)

init:
	mkdir -p bin/obj

bin/obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

clean:
	rm -Rf bin
