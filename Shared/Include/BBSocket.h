// Filename: BBSocket.h
// Author: Gael Huber
#ifndef __BBSOCKET_H__
#define __BBSOCKET_H__

#include "BBPlatform.h"
#include "BBNetAddress.h"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

namespace BlockBlock
{
	/** \addtogroup Network
	*	@{
	*/

	/**
	* This class owns a UDP network socket and manages the sending and receiving of data
	*/
	class Socket
	{
	public:
		/**
		* Default constructor
		*/
		Socket();

		/**
		* Copy constructor
		* @param
		*	const Socket& The socket to copy
		*/
		Socket(const Socket&);

		/**
		* Destructor
		*/
		~Socket();

		/**
		* Assignment operator
		* @param
		*	const Socket& The socket to copy
		* @return
		*	Socket& The resultant socket
		*/
		Socket& operator=(const Socket&);

		/**
		* Open a socket on a specified port
		* @param
		*	short The port number. If 0 is specified, any port is used
		* @return
		*	bool Returns true if the port is successfully open
		*/
		bool Open(short);

		/**
		* Close any open socket
		*/
		void Close();

		/**
		* Returns whether the socket is currently open
		* @return
		*	Returns true if there is an open socket, false otherwise
		*/
		bool IsOpen() const;

		/**
		* Send a packet to a target NetAddress
		* @param
		*	const NetAddress& The network address to send the data
		* @param
		*	void* A pointer to the data to send
		* @param
		* 	int The length of the data to send
		*/
		bool Send(const NetAddress&, void*, int);

		/**
		* Receive data over the socket
		* @param
		*	NetAddress& The sender of the packet
		* @param
		*	void* A pointer to the data to receive
		* @param
		*	int The maximum size of the data to receive
		* @return
		*	int The number of bytes read
		*/
		int Receive(NetAddress&, void*, int);

	//private:
		/**
		* A handle to the socket
		*/
		int _socket;
	};

	/** @} */
}	// Namespace

#endif // __BBSOCKET_H__