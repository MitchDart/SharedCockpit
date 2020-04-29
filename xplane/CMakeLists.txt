# Example usage:
#  mkdir build
#  cd build
#  cmake -g "Visual Studio 14 2015" ..

cmake_minimum_required(VERSION 2.8)
project(xplane C CXX)

set(PROJECT_ROOT_DIR ../)

configure_file( ${PROJECT_ROOT_DIR}/SharedCockpitConfig.h.in SharedCockpitConfig.h)

include_directories(include)

# Dear ImGui
set(IMGUI_DIR ${PROJECT_ROOT_DIR}/libs/imgx/imgui)
include_directories(${IMGUI_DIR} .)

# imgwindow
set(IMGWINDOW_DIR ${PROJECT_ROOT_DIR}/libs/imgx/src)
include_directories(${IMGWINDOW_DIR})

#main lib
include_directories(${PROJECT_ROOT_DIR}/main/include)

find_package(OpenGL REQUIRED)
set(LIBRARIES "${OPENGL_gl_LIBRARY}")

add_subdirectory(${PROJECT_ROOT_DIR}/libs/xplane_sdk ${PROJECT_ROOT_DIR}/bin)
add_xplane_plugin(xplane 301 src/main.cpp src/xplane_environment.cpp src/imgwindow_adapter.cpp src/osx_clipboard.cpp ${IMGWINDOW_DIR}/imgwindow.cpp ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_widgets.cpp)
target_link_libraries(xplane main ${LIBRARIES})
