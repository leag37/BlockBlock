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
		:	_localPacketId(0),
			_localAck(0),
			_localAckBitfield(0),
			_remoteAck(0),
			_remoteAckBitfield(0)
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
			_localPacketId(0),
			_localAck(0),
			_localAckBitfield(0),
			_remoteAck(0),
			_remoteAckBitfield(0)
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
			_localPacketId(other._localPacketId),
			_localAck(other._localAck),
			_localAckBitfield(other._localAckBitfield),
			_remoteAck(other._remoteAck),
			_remoteAckBitfield(other._remoteAckBitfield),
			_sentPackets(other._sentPackets)
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

		// Update the received packet id
		uint packetId = packet.GetPacketId();
		if(packetId > _remoteAck)
		{
			// Shift the bitfield by the difference
			_remoteAckBitfield <<= packetId - _remoteAck;
			_remoteAckBitfield |= 1;

			_remoteAck = packetId;
		}

		// Update the bitfield for received packets
		else if(_remoteAck - 32 >= packetId)
		{
			_remoteAckBitfield |= 1 << (_remoteAck - packetId);
		}

		// Check for unreceived packets.
		// First, we must update the _localAck to represent what the remote host knows
		// it has received (or not) from the local host. This is done by updating
		// the localAck and localAckBitfield
		uint localAck = packet.GetAck();
		uint localAckBitfield = packet.GetAckBitfield();
		if(localAck > _localAck)
		{
			_localAckBitfield <<= localAck - _localAck;
			_localAckBitfield |= localAckBitfield;
		}
		else if(_localAck - 32 >= localAck)
		{
			_localAckBitfield |= 1 << (_localAck - localAck);
		}
		
		// Iterate through (up to) the last 32 packets sent
		for(int i = _sentPackets.size() - 1; i >= 24; --i)
		{
			// If the packet has not been received and is within 10 packets of the end, 
			// resend the packet and mark it as received
			if((_localAckBitfield & (1 << i)) == 0)
			{
				Send(_sentPackets[i].GetMessageType(), _sentPackets[i].GetDataSize(), _sentPackets[i].GetData());
				_localAckBitfield |= 1 << i;
			}
		}
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
		// Build the packet
		Packet packet = Packet(_localPacketId++, _remoteAck, _remoteAckBitfield, messageType, size, data);

		// If the number of backlogged packets is 32, shift forward and push new packet to back
		if(_sentPackets.size() == 32)
		{
			_sentPackets.erase(_sentPackets.begin());
		}
		_sentPackets.push_back(packet);

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