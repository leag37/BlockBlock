include_directories(Include ${BlockBlock_SOURCE_DIR}/Shared/Include)

# Define sources
set (BBClient_Sources
	Source/BBClient.cpp
	Source/BBClientMain.cpp
)

add_executable(BBClient ${BBClient_Sources})

# GLFW setup
set(GLFW_DIR ${BlockBlock_SOURCE_DIR}/External/glfw-3.0.4)
add_subdirectory(${GLFW_DIR} ${GLFW_DIR})
include_directories(${GLFW_DIR}/include)

set(TARGET_LIBRARIES glfw ${GLFW_LIBRARIES} BBShared)
#target_link_libraries(BBClient glfw ${GLFW_LIBRARIES})
#target_link_libraries(BBClient BBShared)
target_link_libraries(BBClient ${TARGET_LIBRARIES})
