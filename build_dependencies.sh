#!/bin/bash

cd build
cmake -G Ninja  -DCMAKE_BUILD_TYPE=Release -DProtobuf_BUILD_SHARED_LIBS=OFF -DProtobuf_USE_STATIC_LIBS=ON -DGAMENETWORKINGSOCKETS_BUILD_TESTS=OFF -DCMAKE_TOOLCHAIN_FILE=/Users/mitch/Sticitt/OpenSource/vcpkg/scripts/buildsystems/vcpkg.cmake ..
ninja