// Filename: BBSocket.cpp
// Author: Gael Huber
#include "BBSocket.h"

namespace BlockBlock
{
	/**
	* Default constructor
	*/
	Socket::Socket()
		:	_socket(-1)
	{

	}

	/**
	* Copy constructor
	* @param other The socket to copy
	*/
	Socket::Socket(const Socket& other)
		:	_socket(other._socket)
	{

	}

	/**
	* Destructor
	*/
	Socket::~Socket()
	{

	}

	/**
	* Assignment operator
	* @param other The socket to copy
	* @return The resultant socket
	*/
	Socket& Socket::operator=(const Socket& other)
	{
		_socket = other._socket;
		return *this;
	}

	/**
	* Open a socket on a specified port
	* @param port The port number. If 0 is specified, any port is used
	* @return Returns true if the port is successfully open
	*/
	bool Socket::Open(ushort port)
	{
		// If the socket is already open it, return false
		if(_socket > -1)
		{
			return false;
		}

		// TODO: Detect IP address
		NetAddress socketAddress = NetAddress(127, 0, 0, 1, port);

		// Open the socket
		sockaddr_in address;
		memset((char*)&address, 0, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = socketAddress.GetNetAddress();
		address.sin_port = socketAddress.GetNetPort();

		_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if(_socket < 0)
		{
			printf("failed to create socket\n");
			return false;
		}

		if(bind(_socket, (struct sockaddr*) &address, sizeof(address)) < 0)
		{
			printf("failed to bind socket\n");
			return false;
		}

		// Set the socket to non-blocking
		int nonBlocking = 1;
		if(fcntl(_socket, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
		{
			printf("failed to set to non-blocking\n");
			return false;
		}

		return true;
	}

	/**
	* Close any open socket
	*/
	void Socket::Close()
	{
		if(_socket > -1)
		{
			close(_socket);
		}
	}

	/**
	* Returns whether the socket is currently open
	* @return Returns true if there is an open socket, false otherwise
	*/
	bool Socket::IsOpen() const
	{
		return _socket != 0;
	}

	/**
	* Send a packet to a target NetAddress
	* @param toAddress The network address to send the data
	* @param data A pointer to the data to send
	* @param size The length of the data to send
	* @return Returns true if successfully sent
	*/
	bool Socket::Send(const NetAddress& toAddress, void* data, int size)
	{
		// If the socket is not open, return false
		if(IsOpen() == false)
		{
			return false;
		}

		// Build the outbound socket address
		sockaddr_in toSocket;
		memset((char*)&toSocket, 0, sizeof(toSocket));
		toSocket.sin_family = AF_INET;
		toSocket.sin_addr.s_addr = toAddress.GetNetAddress();
		toSocket.sin_port = toAddress.GetNetPort();

		return sendto(_socket, data, size, 0, (struct sockaddr*)&toSocket, sizeof(sockaddr_in)) == size;
	}

	/**
	* Receive data over the socket
	* @param fromAddress The sender of the packet
	* @param data A pointer to the data to receive
	* @param size The maximum size of the data to receive
	* @return int The number of bytes read
	*/
	int Socket::Receive(NetAddress& fromAddress, void* data, int maxSize)
	{
		if(IsOpen() == false)
		{
			return -1;
		}

		sockaddr_in fromSocket;
		socklen_t fromSocketSize = sizeof(fromSocket);
		int fromSize = recvfrom(_socket, data, maxSize, 0, (struct sockaddr*)&fromSocket, &fromSocketSize);

		// Get the address data
		if(fromSize >= 0)
		{
			// The address can be reconstituted from the existing port and address
			fromAddress = NetAddress(fromSocket.sin_addr.s_addr, fromSocket.sin_port);
		}

		// Return the number of bytes received
		return fromSize;
	}

}	// Namespace