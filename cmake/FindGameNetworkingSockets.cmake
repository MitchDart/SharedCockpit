set(PROJECT_ROOT_DIR ../)

if(NOT TARGET GameNetworkingSockets)
	add_subdirectory("${PROJECT_ROOT_DIR}/libs/GameNetworkingSockets" "${CMAKE_BINARY_DIR}/GameNetworkingSockets")
endif()

set(GameNetworkingSockets_INCLUDE_DIRS
	"${PROJECT_ROOT_DIR}/libs/GameNetworkingSockets/src"
	"${CMAKE_BINARY_DIR}/GameNetworkingSockets"
	)
set(GameNetworkingSockets_LIBRARIES GameNetworkingSockets)
set(GameNetworkingSockets_FOUND true)
