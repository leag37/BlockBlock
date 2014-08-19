// Filename: BBConnection.cpp
// Author: Gael Huber
#include "BBConnection.h"

#include <iostream>

namespace BlockBlock
{
	/**
	* Default constructor
	*/
	Connection::Connection()
		:	_lastSentPacketId(0)
	{
		_timer.Start();
	}

	/**
	* Constructor
	* @param socket The socket upon which to communicate
	* @param address The address to send data
	*/
	Connection::Connection(const Socket& socket, const NetAddress& address)
		:	_socket(socket),
			_address(address),
			_lastSentPacketId(0)
	{
		_timer.Start();	
	}

	/**
	* Copy constructor
	* @param other The connection object to copy
	*/
	Connection::Connection(const Connection& other)
		:	_socket(other._socket),
			_address(other._address),
			_timer(other._timer),
			_lastSentPacketId(other._lastSentPacketId)
	{

	}

	/**
	* Destructor
	*/
	Connection::~Connection()
	{

	}

	/**
	* Enqueue an entry to the connection. This will
	* be processed later when the connection.
	* @param packet The packet to enqueue
	*/
	void Connection::Enqueue(const Packet& packet)
	{
		// For each enqueued entry, reset the timer
		_timer.Reset();
		_packetQueue.push(packet);
	}

	/**
	* Dequeue a packet for processing
	* @param packet The packet to populate with data
	* @return True if the dequeue retrieved a packet
	*/
	bool Connection::Dequeue(Packet& packet)
	{
		if(_packetQueue.empty() == true)
		{
			return false;
		}
		
		packet = _packetQueue.front();
		_packetQueue.pop();
		return true;
	}

	/**
	* Build and send a packet of data through this connection
	* @param messageType The message type for this data packet
	* @param size The size of the data being transfered
	* @param data The pointer to the data
	* @return Returns true if successfully transferred
	*/
	bool Connection::Send(uint messageType, uchar size, void* data)
	{
		Packet packet = Packet(++_lastSentPacketId, messageType, size, data);
		return _socket.Send(_address, (void*)&packet, sizeof(Packet));
	}

	/**
	* Poll the connection for any data
	* @param packet The packet to receive
	*/
	bool Connection::Poll(Packet& packet)
	{
		_timer.Update();

		NetAddress address;
		// Attempt to poll socket
		if(_socket.Receive(address, (void*)&packet, sizeof(Packet)) > 0)
		{
			// If the from address is the same as the stored address, update the timer and return true
			if(address.GetNetAddress() == _address.GetNetAddress())
			{
				_timer.Reset();
				return true;
			}
		}
		return false;
	}

	/**
	* Send a packet to the connected address
	* @param packet The packet to send
	*/
	void Connection::SendPacket(const Packet& packet)
	{
		_socket.Send(_address, (void*)&packet, sizeof(Packet));
	}

	/**
	* Is the connection active
	* @return Returns true if the connection is active and has received a message within the
	*	last 5 seconds
	*/
	bool Connection::IsConnected() const
	{
		return _timer.GetElapsedTimeMs() < CONNECTION_DEFAULT_TIMEOUT;
	}

	/**
	* Get the NetAddress associated with this connection
	* @return The NetAddress for the connection
	*/
	const NetAddress& Connection::GetNetAddress() const
	{
		return _address;
	}

}	// Namespace