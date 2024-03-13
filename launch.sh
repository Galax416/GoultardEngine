#!/bin/sh


mkdir -p build
cd build
cmake ..
make -j
./launch-TP1.sh
