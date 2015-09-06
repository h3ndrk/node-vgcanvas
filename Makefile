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
CFLAGS += -I/opt/vc/include
CFLAGS += -I/opt/vc/include/interface/vmcs_host/linux
CFLAGS += -I/opt/vc/include/interface/vcos/pthreads
CFLAGS += -I./etc

LIBS += -lm
LIBS += -L/opt/vc/lib
LIBS += -lGLESv2
LIBS += -lEGL
LIBS += -lbcm_host
LIBS += -lpthread
LIBS += -ljpeg

.PHONY: all home-infoscreen init clean

all: init home-infoscreen

home-infoscreen: init bin/obj/home-infoscreen.o bin/obj/libshapes.o bin/obj/oglinit.o
	$(CC) $(CFLAGS) bin/obj/home-infoscreen.o bin/obj/libshapes.o bin/obj/oglinit.o -o bin/home-infoscreen $(LIBS)

init:
	mkdir -p bin/obj

bin/obj/home-infoscreen.o: src/home-infoscreen.c
	$(CC) $(CFLAGS) -c -o bin/obj/home-infoscreen.o src/home-infoscreen.c $(LIBS)

bin/obj/libshapes.o: src/libshapes.c
	$(CC) $(CFLAGS) -c -o bin/obj/libshapes.o src/libshapes.c $(LIBS)

bin/obj/oglinit.o: src/oglinit.c
	$(CC) $(CFLAGS) -c -o bin/obj/oglinit.o src/oglinit.c $(LIBS)

clean:
	rm -Rf bin
