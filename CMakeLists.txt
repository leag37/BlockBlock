# Set the minimum required
cmake_minimum_required (VERSION 3.0)
project (BlockBlock)

# Version info
set (BLOCKBLOCK_VERSION_MAJOR 0)
set (BLOCKBLOCK_VERSION_MINOR 1)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE})

# Set compiler flags
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

# Add subdirectories for project configs
add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(Shared)