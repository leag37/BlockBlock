// Filename: BBSocket.cpp
// Author: Gael Huber
#include "BBSocket.h"

namespace BlockBlock
{
	/**
	* Default constructor
	*/
	Socket::Socket()
		:	_socket(0)
	{

	}

	/**
	* Copy constructor
	* @param
	*	const Socket& The socket to copy
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
	* @param
	*	const Socket& The socket to copy
	* @return
	*	Socket& The resultant socket
	*/
	Socket& Socket::operator=(const Socket& other)
	{
		_socket = other._socket;
		return *this;
	}

}	// Namespace