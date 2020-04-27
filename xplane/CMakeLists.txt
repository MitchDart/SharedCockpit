# Example usage:
#  mkdir build
#  cd build
#  cmake -g "Visual Studio 14 2015" ..

cmake_minimum_required(VERSION 2.8)
project(xplane C CXX)

set(PROJECT_ROOT_DIR ../)

# Libraries
set(XSDKHeaders ${PROJECT_ROOT_DIR}/libs/XSDK/CHeaders)
set(XPLM ${PROJECT_ROOT_DIR}/libs/XSDK/Libraries/Mac/XPLM.Framework)
set(XPWidgets ${PROJECT_ROOT_DIR}/libs/XSDK/Libraries/Mac/XPWidgets.Framework)
find_package(OpenGL REQUIRED)
set(LIBRARIES "XPLM;XPWidgets;${OPENGL_LIBRARIES}")

include_directories(${XSDKHeaders}/XPLM)
include_directories(${XSDKHeaders}/Widgets)
include_directories(${XSDKHeaders}/Wrappers)
include_directories(${OPENGL_INCLUDE_DIRS})

file(GLOB sources *.cpp)

configure_file( ${PROJECT_ROOT_DIR}/SharedCockpitConfig.h.in SharedCockpitConfig.h)

add_library(xplane ${sources})
target_link_libraries(xplane ${LIBRARIES})