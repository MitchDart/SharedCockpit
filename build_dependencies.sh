#!/bin/bash

cd libs

echo "Building RxCPP..."
cd RxCpp
mkdir build
cd build
cmake ..
make install
cd ../..