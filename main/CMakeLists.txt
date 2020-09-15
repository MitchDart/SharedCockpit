cmake_minimum_required(VERSION 2.8)
project(main C CXX)

set(PROJECT_ROOT_DIR ../)

# Dear ImGui
set(IMGUI_DIR ${PROJECT_ROOT_DIR}/libs/imgx/imgui)
include_directories(${IMGUI_DIR} .)

include_directories(${PROJECT_ROOT_DIR}/libs/GameNetworkingSockets/include)

find_package(rxcpp CONFIG REQUIRED)

add_library(main 
	"include/chat/chat_client.hpp"
	"include/chat/chat_view_model.h"
	"include/chat/chat_window.h"
	"include/chat/connection_manager.h"
	"include/flight_controller/flight_controller.h"
	"include/flight_recorder/flight_recorder_controller.h"
	"include/flight_recorder/flight_recorder_window.h"
	"include/network_controller/client.h" 
	"include/network_controller/server.h"
	"include/network_controller/network_controller.h"
	"include/network_controller/client_window.h"
	"include/network_controller/server_window.h"
	"include/network_controller/peer.h"
	"include/network_controller/network_state_enums.h"
	"include/coordinator.h"
	"include/dataref.h"
	"include/environment.h"
	"include/first_window.h"
	"include/frames.h"
	"include/imgui_window.h"
	"include/utils.h"
    "include/imgui_logger.h"
	

	"src/coordinator.cpp"
	"src/dataref.cpp"
	"src/first_window.cpp"
	"src/imgui_window.cpp"
	"src/flight_recorder/flight_recorder_window.cpp" 
	"src/flight_recorder/flight_recorder_controller.cpp" 
	"src/chat/chat_view_model.cpp"
	"src/chat/chat_window.cpp" 
	"src/network_controller/client.cpp" 
	"src/network_controller/server.cpp"
	"src/network_controller/network_controller.cpp"
	"src/network_controller/client_window.cpp"
	"src/network_controller/server_window.cpp"
	"src/imgui_logger.cpp"
   "include/chat/chat_events.h"
   )

include_directories(include include/chat)

target_link_libraries(main rxcpp GameNetworkingSockets_s)
