include_directories(
	Include 
	${BlockBlock_SOURCE_DIR}/Shared/Include
)

# Define sources
set (BBServer_Sources
	Source/BBServerMain.cpp
)

add_executable(BBServer ${BBServer_Sources})
target_link_libraries(BBServer BBShared)