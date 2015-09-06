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
#CFLAGS += `pkg-config --cflags gtk+-2.0`
#CFLAGS += `pkg-config --cflags libqrencode`
CFLAGS += -I/opt/vc/include
CFLAGS += -I/opt/vc/include/interface/vmcs_host/linux
CFLAGS += -I/opt/vc/include/interface/vcos/pthreads

LIBS += -lm
#LIBS += `pkg-config --libs gtk+-2.0`
#LIBS += `pkg-config --libs libqrencode`

#gcc -O2 -Wall $(INCLUDEFLAGS) -c libshapes.c
#gcc -O2 -Wall $(INCLUDEFLAGS) -c oglinit.c

.PHONY: all qr_code_generator init clean

all: bin/obj/libshape.o bin/obj/oglinit.o

#all: home-infoscreen

#home-infoscreen: init bin/obj/home-infoscreen.o
#	$(CC) bin/obj/home-infoscreen.o $(CFLAGS) -o bin/home-infoscreen $(LIBS)

init:
	mkdir -p bin
	mkdir -p bin/obj

bin/obj/libshape.o: src/libshape.c
	$(CC) $(CFLAGS) -c -o bin/obj/libshape.o src/libshape.c $(LIBS)

bin/obj/oglinit.o: src/oglinit.c
	$(CC) $(CFLAGS) -c -o bin/obj/oglinit.o src/oglinit.c $(LIBS)
