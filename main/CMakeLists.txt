cmake_minimum_required(VERSION 2.8)
project(main C CXX)

set(PROJECT_ROOT_DIR ../)

# Dear ImGui
set(IMGUI_DIR ${PROJECT_ROOT_DIR}/libs/imgx/imgui)
include_directories(${IMGUI_DIR} .)

include_directories(include)

#Need to include this for RxCPP. Not sure if this is needed for all OSs
include_directories(/usr/local/include)

#RxCPP
find_package(rxcpp CONFIG REQUIRED)
find_package(GameNetworkingSockets REQUIRED)

add_library(main 
	"src/coordinator.cpp"
	"src/dataref.cpp"
	"src/first_window.cpp"
	"src/imgui_window.cpp"
	"src/flight_recorder/flight_recorder_window.cpp" 
	"src/flight_recorder/flight_recorder_controller.cpp" )
target_link_libraries(main rxcpp GameNetworkingSockets)
