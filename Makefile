# Copyright (C) 2015 NIPE-SYSTEMS
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
# LIBS += -lbcm_host
# LIBS += -lpthread
# LIBS += -ljpeg

PROGRAM_NAME = home-infoscreen

SRC += $(PROGRAM_NAME).c
SRC += egl-util.c
SRC += canvas.c
SRC += color.c
SRC += canvas-clearRect.c
SRC += canvas-lineWidth.c
# SRC += font.c

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
