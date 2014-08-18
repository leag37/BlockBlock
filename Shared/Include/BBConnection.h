// Filename: BBConnection.h
// Author: Gael Huber
#ifndef __BBCONNECTION_H__
#define __BBCONNECTION_H__

#include "BBPlatform.h"
#include "BBPacket.h"
#include "BBSocket.h"
#include "BBTimer.h"

namespace BlockBlock
{
	/** \addtogroup Network
	*	@{
	*/

	/**
	* Timeout period
	*/
	#define CONNECTION_DEFAULT_TIMEOUT (5 * MICROSECONDS_PER_SECOND)

	/**
	* Connection manages inbound and outbound messages between two addresses
	*/
	class Connection
	{
	public:
		/**
		* Default constructor
		*/
		Connection();

		/**
		* Constructor
		* @param socket The socket upon which to communicate
		* @param address The address to send data
		*/
		Connection(const Socket& socket, const NetAddress& address);

		/**
		* Copy constructor
		* @param other The connection object to copy
		*/
		Connection(const Connection& other);

		/**
		* Destructor
		*/
		~Connection();

		/**
		* Poll the connection for any data
		* @param packet The packet to receive
		*/
		bool Poll(Packet& packet);

		/**
		* Send a packet to the connected address
		* @param packet The packet to send
		*/
		void Send(const Packet& packet);

		/**
		* Is the connection active
		* @return Returns true if the connection is active
		*/
		bool IsConnected() const;

	private:
		/**
		* The socket on which to send messages
		*/
		Socket _socket;

		/**
		* The connected network address
		*/
		NetAddress _address;

		/**
		* Timer to ensure the connection is still valid
		*/
		Timer _timer;
	};

	/** @} */

}	// Namespace

#endif // __BBCONNECTION_H__