# Example usage:
#  mkdir build
#  cd build
#  cmake -g "Visual Studio 14 2015" ..

cmake_minimum_required(VERSION 2.8)
project(standalone C CXX)


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVK_PROTOTYPES /Zi")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_PROTOTYPES /Zi")

set(PROJECT_ROOT_DIR ../)

# Dear ImGui
set(IMGUI_DIR ${PROJECT_ROOT_DIR}/libs/imgx/imgui)
include_directories(${IMGUI_DIR} .)

# Libraries
find_package(rxcpp REQUIRED)
find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})
set(LIBRARIES ";${Vulkan_LIBRARY};rxcpp")

#main lib
include_directories(${PROJECT_ROOT_DIR}/main/include)

#standalone include
include_directories(include)

file(GLOB sources src/*.cpp)

configure_file( ${PROJECT_ROOT_DIR}/SharedCockpitConfig.h.in SharedCockpitConfig.h)

add_executable(standalone ${sources} ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_widgets.cpp)
target_link_libraries(standalone main glfw GameNetworkingSockets_s ${LIBRARIES})