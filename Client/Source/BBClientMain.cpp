#include "BBSocket.h"

#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

using namespace BlockBlock;

int main()
{
	// Open a socket
	Socket socket = Socket();
	socket.Open(0);

	// Send address
	NetAddress toAddress = NetAddress(127, 0, 0, 1, 30000);

	char c = ' ';
	do
	{
		// Receive all packets
		unsigned char packet_data[256];
		unsigned int max_packet_size = sizeof(packet_data);
		NetAddress fromAddress;
		while(socket.Receive(fromAddress, (void*)packet_data, max_packet_size) > 0)
		{
			std::cout << "Got reply: " << packet_data << std::endl;
		}

		// Get input
		std::cin.ignore();
		c = std::cin.get();

		// Send packets
		if(c != 'x')
		{
			for(int i = 0; i < 5; ++i)
			{
				const char* blah = "hello";
				if(socket.Send(toAddress, (void*)blah, sizeof("hello")) == false)
				{
					printf("failed to send packet\n");
				}
				else
				{
					printf("sent packet\n");
				}
			}
		}
	} while(c != 'x');

	socket.Close();

	return 0;
}