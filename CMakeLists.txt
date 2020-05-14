cmake_minimum_required(VERSION "3.14.4")

project(SharedCockpit C CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)

# Add the three targets
add_subdirectory(main)
add_subdirectory(standalone)
add_subdirectory(xplane)