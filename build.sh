#!/bin/bash
export MAKEFLAGS=-j3 #$(($(grep -c ^processor /proc/cpuinfo) - 1))
export CC="clang"
export CXX="g++"

if [[ ! -f lib/SDL-1.2.15/build/.libs/libSDL.a ]]; then
	cd lib
	tar xf SDL-1.2.15.tar.gz
	cd SDL-1.2.15/
	patch  -p 1 -f < ../SDL1.patch
	./autogen.sh && ./configure --enable-input-tslib=off CXXFLAGS="-Ofast -std=gnu++11" CFLAGS="-Ofast" && make
	cd ../..
fi
mkdir build
cd build
cmake .. -DSDL_PATH=`pwd`/../lib/SDL-1.2.15/
make -j3

