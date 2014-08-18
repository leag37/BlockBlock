#include "BBConnection.h"
#include "BBPacket.h"
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

	Packet packet;

	// Create a connection
	Connection connection;
	uint connectionAddress = 0;

	while(socket.IsOpen())
	{
		NetAddress address;
		int bytes = 0;
		
		if(connectionAddress == 0)
		{
			bytes = socket.Receive(address, (void*)&packet, sizeof(Packet));

			// Create a connection
			if(bytes > 0)
			{
				printf("Establishing connection\n");
				connection = Connection(socket, address);
				connectionAddress = address.GetNetAddress();
			}
		}
		else
		{
			bytes = connection.Poll(packet) ? 1 : 0;

			if(bytes == 1)
			{
				printf("GOT STUFF\n");
			}

			if(connection.IsConnected() == false)
			{
				printf("Connection lost\n");
			}
		}

		if(bytes > 0)
		{
			std::cout << "Received the packet: " << (char*)packet.GetData() << std::endl;
			const char* blah = "got it";

			packet = Packet(0, 1, sizeof("got it"), (void*)blah);
			connection.Send(packet);
		}
	}

	socket.Close();

	return 0;
}