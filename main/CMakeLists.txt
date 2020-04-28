cmake_minimum_required(VERSION 2.8)
project(main C CXX)

set(PROJECT_ROOT_DIR ../)

# Dear ImGui
set(IMGUI_DIR ${PROJECT_ROOT_DIR}/libs/imgx/imgui)
include_directories(${IMGUI_DIR} .)

find_package(rxcpp CONFIG)

include_directories(include)

file(GLOB sources src/*.cpp)

add_library(main ${sources})
target_link_libraries(main rxcpp)