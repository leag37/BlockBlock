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
			_address(address)
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
			_timer(other._timer)
	{

	}

	/**
	* Destructor
	*/
	Connection::~Connection()
	{

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
	void Connection::Send(const Packet& packet)
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
}	// Namespace