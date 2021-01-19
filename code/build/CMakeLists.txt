cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(boids)

find_package(Torch REQUIRED)

set(Torch_DIR C:/libtorch1.7/share/cmake/Torch)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")




add_library(boids SHARED export_wrapper.cpp export_wrapper.h boids.cpp boids.h)

target_link_libraries(boids ${TORCH_LIBRARIES})




set_property(TARGET boids PROPERTY CXX_STANDARD 14)

if (MSVC)
	file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
	add_custom_command(TARGET boids
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${TORCH_DLLS}
		$<TARGET_FILE_DIR:x64)
endif (MSVC)