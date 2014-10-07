# Set the minimum required
cmake_minimum_required (VERSION 3.0)
project (BlockBlock)

# Version info
set (BLOCKBLOCK_VERSION_MAJOR 0)
set (BLOCKBLOCK_VERSION_MINOR 1)

# Set up compiler
if(DEFINED COMPILER)
	if(${COMPILER} STREQUAL "g++")
		set(CMAKE_CXX_COMIPLER "usr/bin/g++")
	else()
		set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
		set(COMPILER "clang++")
	endif()
endif()

# Set up common build flags
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

# Set up DEBUG and Release build options
if(DEFINED BUILD)
	if(${BUILD} STREQUAL "debug")
		message("-- Configuring for debug")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
		add_definitions(-DBB_DEBUG)

		# Set output directories
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/debug)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/debug)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/debug)
	elseif(${BUILD} STREQUAL "release")
		message("-- Configuring for release")
		add_definitions(-DBB_RELEASE)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

		# Set output directories
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/release)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/release)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/release)
	endif()
else()
	message("Build type unknown")
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/default)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/default)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/default)
endif()

# Profiling
if(DEFINED PROFILING)
	if(${PROFILING} STREQUAL "true")
		message("Enabling profiling")
		add_definitions(-DBB_PROFILING)
	endif()
endif()

# Enable SIMD intrinsics
if(DEFINED SIMD)
	if(${SIMD} STREQUAL "true")
		message("Enabling SIMD intrinsics")
		add_definitions(-DBB_SIMD)
	endif()
endif()

# Add subdirectories for project configs
add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(Shared)
add_subdirectory(Tests)