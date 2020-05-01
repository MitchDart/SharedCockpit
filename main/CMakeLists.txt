cmake_minimum_required(VERSION 2.8)
project(main C CXX)

set(PROJECT_ROOT_DIR ../)

# Dear ImGui
set(IMGUI_DIR ${PROJECT_ROOT_DIR}/libs/imgx/imgui)
include_directories(${IMGUI_DIR} .)

include_directories(include)

#Need to include this for RxCPP. Not sure if this is needed for all OSs
include_directories(/usr/local/include)

file(GLOB sources src/*.cpp)

#RxCPP
find_package(rxcpp CONFIG REQUIRED)

add_library(main ${sources})
target_link_libraries(main rxcpp)