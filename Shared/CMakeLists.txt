include_directories(Include)

set (BBShared_Sources
	Source/BBAbstractNetworkObject.cpp
	Source/BBConnection.cpp
	Source/BBConnectionManager.cpp
	Source/BBNetAddress.cpp
	Source/BBNetworkPlayer.cpp
	Source/BBPacket.cpp
	Source/BBSocket.cpp
	Source/BBTimer.cpp
)

# Get the list of source files
add_library(BBShared ${BBShared_Sources})