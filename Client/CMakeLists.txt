include_directories(Include ${BlockBlock_SOURCE_DIR}/Shared/Include)

# Define sources
set (BBClient_Sources
	Source/BBClientMain.cpp
)

add_executable(BBClient ${BBClient_Sources})
target_link_libraries(BBClient BBShared)