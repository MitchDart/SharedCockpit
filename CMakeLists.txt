cmake_minimum_required(VERSION "3.14.4")

project(SharedCockpit VERSION 0.1.1)

add_subdirectory(src)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(SharedCockpitConfig.h.in SharedCockpitConfig.h)

target_include_directories(SharedCockpit PUBLIC "${PROJECT_BINARY_DIR}")
