#include "BBSocket.h"
#include "BBTimer.h"

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

	// Timer
	Timer timer;
	if(timer.Start() == false)
	{
		return -1;
	}

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

		// Update the timer
		timer.Update();
		
		// Send packets
		if(timer.GetElapsedTimeMs() > MICROSECONDS_PER_SECOND)
		{
			timer.Reset();

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
	} while(timer.GetElapsedTimeMs() >= 0);

	socket.Close();

	return 0;
}