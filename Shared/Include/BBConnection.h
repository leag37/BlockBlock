// Filename: BBConnection.h
// Author: Gael Huber
#ifndef __BBCONNECTION_H__
#define __BBCONNECTION_H__

#include "BBPlatform.h"
#include "BBPacket.h"
#include "BBSocket.h"
#include "BBTimer.h"

#include <vector>
#include <queue>

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
		* Enqueue an entry to the connection. This will
		* be processed later when the connection.
		* @param packet The packet to enqueue
		*/
		void Enqueue(const Packet& packet);

		/**
		* Dequeue a packet for processing
		* @param packet The packet to populate with data
		* @return True if the dequeue retrieved a packet
		*/
		bool Dequeue(Packet& packet);

		/**
		* Build and send a packet of data through this connection
		* @param messageType The message type for this data packet
		* @param size The size of the data being transfered
		* @param data The pointer to the data
		* @return Returns true if successfully transferred
		*/
		bool Send(uint messageType, uchar size, void* data);

		/**
		* Poll the connection for any data
		* @param packet The packet to receive
		*/
		bool Poll(Packet& packet);

		/**
		* Send a packet to the connected address
		* @param packet The packet to send
		*/
		void SendPacket(const Packet& packet);

		/**
		* Is the connection active
		* @return Returns true if the connection is active
		*/
		bool IsConnected() const;

		/**
		* Get the NetAddress associated with this connection
		* @return The NetAddress for the connection
		*/
		const NetAddress& GetNetAddress() const;

	private:
		/**
		* Check for packets unreceived by the connected address. If there are any
		* unreceived packets, resend them.
		*/


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

		/**
		* The current packet id of the last send message
		*/
		uint _localPacketId;

		/**
		* The highest packet id that has been received by the remote host
		*/
		uint _localAck;

		/**
		* The local host packet ack bitfield
		*/
		uint _localAckBitfield;

		/**
		* The highest received packet id from the remote host
		*/
		uint _remoteAck;

		/**
		* The remote host packet ack bitfield
		*/
		uint _remoteAckBitfield;

		/**
		* 32 most recent packets
		*/
		std::vector<Packet> _sentPackets;

		/**
		* Packet queue
		*/
		std::queue<Packet> _packetQueue;
	};

	/** @} */

}	// Namespace

#endif // __BBCONNECTION_H__