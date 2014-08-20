#include "BBConnectionManager.h"
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
	ConnectionManager* connectionManager = new ConnectionManager();
	connectionManager->Initialize(30000);
	//Socket socket = Socket();
	//socket.Open(30000);

	Packet packet;

	// Create a connection
	//Connection connection;
	//uint connectionAddress = 0;

	while(true)
	{
		connectionManager->Update();

		Connection* connection = connectionManager->GetUnboundConnection();
		if(connection)
		{
			while(connection->Dequeue(packet))
			{
				printf("Received packet: %s\n", (char*)packet.GetData());
				connection->Send(1, sizeof("got it"), (void*)("got it"));
				//connection->SendPacket(packet);
			}
		}
	}

	//socket.Close();

	return 0;
}