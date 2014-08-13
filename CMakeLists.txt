# Set the minimum required
cmake_minimum_required (VERSION 3.0)
project (BlockBlock)

# Version info
set (BLOCKBLOCK_VERSION_MAJOR 0)
set (BLOCKBLOCK_VERSION_MINOR 1)

# Set output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add subdirectories for project configs
add_subdirectory(Client)
add_subdirectory(Server)
add_subdirectory(Shared)