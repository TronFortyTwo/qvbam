#! /bin/bash
mkdir package
cp build/qvbam build/qml logo.png manifest.json qvbam.desktop qvbam.json ./package -rf
cd package
click build .
cp *.click ..
cd ..
rm -rf package

