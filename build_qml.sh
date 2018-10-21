#!/bin/bash

# This scripts updates the qml stuff in the build directory without triggering a complete rebuild
rm -r build/qml

cp -r src/qt/qml build
