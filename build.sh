#!/bin/bash
export MAKEFLAGS=-j$(($(grep -c ^processor /proc/cpuinfo)))
export CC="gcc"
export CXX="g++"

mkdir build
cd build
#cmake .. -DSDL_PATH=`pwd`/../lib/SDL-1.2.15/
cmake ..
make "$MAKEFLAGS"
