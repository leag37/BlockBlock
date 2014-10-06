include_directories(Include ${BlockBlock_SOURCE_DIR}/Shared/Include)

# Define sources
set (BBClient_Sources
	Source/BBClient.cpp
	Source/BBClientMain.cpp
	Source/BBRenderer.cpp
	Source/BBWindow.cpp
)

add_executable(BBClient ${BBClient_Sources})

find_package(GLEW)

# GLFW setup
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_DIR ${BlockBlock_SOURCE_DIR}/External/glfw-3.0.4)
add_subdirectory(${GLFW_DIR} ${GLFW_DIR})

# GLM setup
set(GLM_DIR ${BlockBlock_SOURCE_DIR}/External/glm-0.9.5.4)

# Includes
include_directories(${GLFW_DIR}/include ${GLM_DIR} ${GLEW_INCLUDE_DIRS})

set(TARGET_LIBRARIES glfw ${GLFW_LIBRARIES} BBShared ${GLEW_LIBRARIES})
target_link_libraries(BBClient ${TARGET_LIBRARIES})
