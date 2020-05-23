cmake_minimum_required(VERSION 2.8)
project(main C CXX)

set(PROJECT_ROOT_DIR ../)

# Dear ImGui
set(IMGUI_DIR ${PROJECT_ROOT_DIR}/libs/imgx/imgui)
include_directories(${IMGUI_DIR} .)

find_package(rxcpp CONFIG REQUIRED)

add_subdirectory(${PROJECT_ROOT_DIR}/libs/GameNetworkingSockets ${PROJECT_ROOT_DIR}/libs/GameNetworkingSockets/build)

add_library(main 
	"src/coordinator.cpp"
	"src/dataref.cpp"
	"src/first_window.cpp"
	"src/imgui_window.cpp"
	"src/flight_recorder/flight_recorder_window.cpp" 
	"src/flight_recorder/flight_recorder_controller.cpp" 
	"src/chat/chat_view_model.cpp"
	"src/chat/chat_window.cpp" 
	 "include/chat/connection_manager.h")

include_directories(include include/chat)

target_link_libraries(main rxcpp GameNetworkingSockets::static)
