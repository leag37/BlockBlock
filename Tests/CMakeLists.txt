# CMake file for Tests sub-project

include_directories(
	Include
	${BlockBlock_SOURCE_DIR}/Shared/Include
)

set (BBTests_Sources
	Source/BBTest.cpp
	Source/BBTestMain.cpp
	Source/BBTestSuite.cpp
	Source/BBTestVector.cpp
)

add_executable(BBTests ${BBTests_Sources})
target_link_libraries(BBTests BBShared)