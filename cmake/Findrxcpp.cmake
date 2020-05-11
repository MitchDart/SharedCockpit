if (NOT TARGET rxcpp)
	add_subdirectory("../libs/RxCpp" "${CMAKE_BINARY_DIR}/RxCpp")
endif()

MESSAGE( STATUS "ATTEMPT TO LOCATE CMAKE: " ${PROJECT_ROOT_DIR} )

list(APPEND CMAKE_FIND_ROOT_PATH
	${CMAKE_BINARY_DIR}/CMakeFiles/Export/share/rxcpp/cmake)

set(RXCPP_LIBRARIES rxcpp)

MESSAGE( STATUS  ${CMAKE_BINARY_DIR})
set(RxCpp_FOUND true)
