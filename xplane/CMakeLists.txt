# Example usage:
#  mkdir build
#  cd build
#  cmake -g "Visual Studio 14 2015" ..

cmake_minimum_required(VERSION 2.8)
project(xplane C CXX)

set(PROJECT_ROOT_DIR ../)

configure_file( ${PROJECT_ROOT_DIR}/SharedCockpitConfig.h.in SharedCockpitConfig.h)

add_subdirectory(${PROJECT_ROOT_DIR}/libs/xplane_sdk ${PROJECT_ROOT_DIR}/bin)
add_xplane_plugin(xplane 301 main.cpp)