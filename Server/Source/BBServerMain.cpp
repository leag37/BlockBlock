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
	while(socket.IsOpen())
	{
		NetAddress address;
		int bytes = socket.Receive(address, (void*)&packet, sizeof(Packet));

		if(bytes > 0)
		{
			std::cout << "Received the packet: " << (char*)packet.GetData() << std::endl;
			const char* blah = "got it";

			packet = Packet(0, 1, sizeof("got it"), (void*)blah);
			socket.Send(address, (void*)&packet, sizeof(Packet));
		}
	}

	socket.Close();

	return 0;
}