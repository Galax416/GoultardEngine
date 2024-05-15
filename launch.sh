#!/bin/sh


mkdir -p build
cd build
cmake ..
make -j 6 && ./launch-main.sh
