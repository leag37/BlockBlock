#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if(handle <= 0)
	{
		printf("failed ot create socket\n");
		return 1;
	}

	unsigned short port = 30000;

	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = 0;

	if(bind(handle, (const sockaddr*) &address, sizeof(sockaddr_in)) < 0)
	{
		printf("failed to bind socket\n");
		return 1;
	}

	std::cout << "port: " << ntohs(address.sin_port) << std::endl; 

	// Set the socket to non-blocking
	int nonBlocking = 1;
	if(fcntl(handle, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
	{
		printf("failed to set to non-blocking\n");
		return 1;
	}

	sockaddr_in from;
	from.sin_family = AF_INET;
	from.sin_addr.s_addr = htonl(127 << 24 | 0 << 16 | 0 << 8 | 1);
	from.sin_port = htons(30000);

	char c = ' ';
	do
	{
		// Receive all packets
		unsigned char packet_data[256];
		unsigned int max_packet_size = sizeof(packet_data);
		socklen_t fromLength = 0;
		sockaddr_in newFrom;
		while(recvfrom(handle, (void*)packet_data, max_packet_size, 0, (sockaddr*)&newFrom, &fromLength) > 0)
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
				int sent_bytes = sendto(handle, "hello", sizeof("hello"), 0, (sockaddr*)&from, sizeof(sockaddr_in));
				if(sent_bytes != sizeof("hello"))
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

	close(handle);

	return 0;
}