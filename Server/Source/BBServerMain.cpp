#include "BBSocket.h"

#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

using namespace BlockBlock;

int main()
{
	Socket socket = Socket();
	socket.Open(30000);

	while(socket.IsOpen())
	{
		unsigned char packet_data[256];

		unsigned int max_packet_size = sizeof(packet_data);

		NetAddress address;
		int bytes = socket.Receive(address, (void*)packet_data, max_packet_size);

		if(bytes > 0)
		{
			std::cout << "Received the packet: " << packet_data << std::endl;
			const char* blah = "got it";

			socket.Send(address, (void*)blah, sizeof("got it"));
		}
	}

	socket.Close();

	return 0;
}