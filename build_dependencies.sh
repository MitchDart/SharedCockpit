#!/bin/bash

cd build
cmake -G Ninja  -DCMAKE_TOOLCHAIN_FILE=/Users/mitch/Sticitt/OpenSource/vcpkg/scripts/buildsystems/vcpkg.cmake ..
ninja