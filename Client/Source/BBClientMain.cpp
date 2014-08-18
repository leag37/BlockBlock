
#include "BBPacket.h"
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
		Packet packet;
		NetAddress fromAddress;
		while(socket.Receive(fromAddress, (void*)&packet, sizeof(Packet)) > 0)
		{
			std::cout << "Got reply: " << (const char*)packet.GetData() << std::endl;
		}

		// Update the timer
		timer.Update();
		
		// Send packets
		if(timer.GetElapsedTimeMs() > MICROSECONDS_PER_SECOND)
		{
			timer.Reset();

			const char* blah = "hello";
			packet = Packet(0, 1, sizeof("hello"), (void*)blah);
			if(socket.Send(toAddress, (void*)&packet, sizeof(Packet)) == false)
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