#include "BBNetAddress.h"

#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

using namespace BlockBlock;

int main()
{
	int handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if(handle < 0)
	{
		printf("failed ot create socket\n");
		return 1;
	}

	NetAddress homeAddress = NetAddress(127, 0, 0, 0, 30000);

	sockaddr_in address;
	memset((char*)&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = homeAddress.GetNetAddress();
	address.sin_port = homeAddress.GetNetPort();	

	std::cout << "address: " << address.sin_addr.s_addr << std::endl;

	if(bind(handle, (struct sockaddr*) &address, sizeof(address)) < 0)
	{
		printf("failed to bind socket\n");
		return 1;
	}

	// Set the socket to non-blocking
	/*int nonBlocking = 1;
	if(fcntl(handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
	{
		printf("failed to set to non-blocking\n");
		return 1;
	}*/

	while(true)
	{
		unsigned char packet_data[256];

		unsigned int max_packet_size = sizeof(packet_data);

		sockaddr_in from;
		socklen_t fromLength = sizeof(from);

		int bytes = recvfrom(handle, (char*)packet_data, max_packet_size, 0, (struct sockaddr*)&from, &fromLength);

		std::cout << "received " << bytes << std::endl;
		if(bytes > 0)
		{
			unsigned int from_address = ntohl(from.sin_addr.s_addr);
			unsigned int from_port = ntohs(from.sin_port);

			std::cout << "Received the packet: " << packet_data << std::endl;

			sendto(handle, "got it", sizeof("got it"), 0, (sockaddr*)&from, sizeof(sockaddr_in));
		}
		else
		{
			std::cout << "Received nothing" << std::endl;
		}
	}

	close(handle);

	return 0;
}