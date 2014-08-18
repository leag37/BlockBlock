// Filename: BBNetAddress.cpp
// Author: Gael Huber
#include "BBNetAddress.h"

// TEMP
#include <iostream>
// END TEMP

namespace BlockBlock
{
	/**
	* Default constructor
	*/
	NetAddress::NetAddress()
		:	_hostAddress(0),
			_netAddress(0),
			_hostPort(0),
			_netPort(0)
	{

	}

	/**
	* Constructor specifying A.B.C.D to compose network address
	* @param a A
	* @param b B
	* @param c C
	* @param d D
	* @param port The port in host format
	*/
	NetAddress::NetAddress(uint a, uint b, uint c, uint d, ushort port)
		:	_hostAddress(a << 24 | b << 16 | c << 8 | d),
			_netAddress(htonl(_hostAddress)),
			_hostPort(port),
			_netPort(htons(_hostPort))
	{
	}

	/**
	* Constructor specifying network value equivalent to A.B.C.D
	* @param address The network address in network format
	* @param port The network port in network format
	*/
	NetAddress::NetAddress(uint address, ushort port)
		:	_hostAddress(ntohl(address)),
			_netAddress(address),
			_hostPort(ntohs(port)),
			_netPort(port)
	{
		
	}

	/**
	* Copy constructor
	* @param other The address to copy
	*/
	NetAddress::NetAddress(const NetAddress& other)
		:	_hostAddress(other._hostAddress),
			_netAddress(other._netAddress),
			_hostPort(other._hostPort),
			_netPort(other._netPort)
	{

	}

	/**
	* Destructor
	*/
	NetAddress::~NetAddress()
	{

	}

	/**
	* Assignment operator
	* @param other The address to assign
	* @return The resultant address
	*/
	NetAddress& NetAddress::operator=(const NetAddress& other)
	{
		_hostAddress = other._hostAddress;
		_netAddress = other._netAddress;
		_hostPort = other._hostPort;
		_netPort = other._netPort;
		return *this;
	}

	/**
	* Getter for the network address
	* @return The address in network format
	*/
	uint NetAddress::GetNetAddress() const
	{
		return _netAddress;
	}

	/**
	* Getter for A
	* @return Value representative of A
	*/
	uint NetAddress::GetA() const
	{
		return _hostAddress >> 24;
	}

	/**
	* Getter for B
	* @return Value representative of B
	*/
	uint NetAddress::GetB() const
	{
		return (_hostAddress >> 16) & 0x000000FF;
	}

	/**
	* Getter for C
	* @return Value representative of C
	*/
	uint NetAddress::GetC() const
	{
		return (_hostAddress >> 8) & 0x000000FF;
	}

	/**
	* Getter for D
	* @return Value representative of D
	*/
	uint NetAddress::GetD() const
	{
		return _hostAddress & 0x000000FF;
	}

	/**
	* Get the port in host format
	* @return The host port value
	*/
	ushort NetAddress::GetPort() const
	{
		return _hostPort;
	}

	/**
	* Get the port in network format
	* @return The network port value
	*/
	ushort NetAddress::GetNetPort() const
	{
		return _netPort;
	}

}	// Namespace