include_directories(Include)

set (BBShared_Sources
	Source/BBNetAddress.cpp
	Source/BBPacket.cpp
	Source/BBSocket.cpp
	Source/BBTimer.cpp
)

# Get the list of source files
add_library(BBShared ${BBShared_Sources})