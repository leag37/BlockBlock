// Filename: BBNetAddress.cpp
// Author: Gael Huber
#include "BBNetAddress.h"

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
	* @param
	*	int A
	* @param
	*	int B
	* @param
	*	int C
	* @param
	*	int D
	* @param
	*	short The port in host format
	*/
	NetAddress::NetAddress(int a, int b, int c, int d, short port)
		:	_hostAddress(a << 24 | b << 16 | c << 8 | d),
			_netAddress(htonl(_hostAddress)),
			_hostPort(port),
			_netPort(htons(_hostPort))
	{
	}

	/**
	* Constructor specifying network value equivalent to A.B.C.D
	* @param
	*	int The network address in network format
	* @param
	*	short The network port in network format
	*/
	NetAddress::NetAddress(int address, short port)
		:	_hostAddress(ntohl(address)),
			_netAddress(address),
			_hostPort(ntohs(port)),
			_netPort(port)
	{

	}

	/**
	* Copy constructor
	* @param
	*	const NetAddress& The address to copy
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
	* @param
	*	const NetworkAddress& The address to assign
	* @return
	*	NetworkAddress& The resultant address
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
	* @return
	*	int The address in network format
	*/
	int NetAddress::GetNetAddress() const
	{
		return _netAddress;
	}

	/**
	* Getter for A
	* @return
	*	int Value representative of A
	*/
	int NetAddress::GetA() const
	{
		return _hostAddress >> 24;
	}

	/**
	* Getter for B
	* @return
	*	int Value representative of B
	*/
	int NetAddress::GetB() const
	{
		return (_hostAddress >> 16) & 0x000000FF;
	}

	/**
	* Getter for C
	* @return
	*	int Value representative of C
	*/
	int NetAddress::GetC() const
	{
		return (_hostAddress >> 8) & 0x000000FF;
	}

	/**
	* Getter for D
	* @return
	*	int Value representative of D
	*/
	int NetAddress::GetD() const
	{
		return _hostAddress & 0x000000FF;
	}

	/**
	* Get the port in host format
	* @return
	*	short The host port value
	*/
	short NetAddress::GetPort() const
	{
		return _hostPort;
	}

	/**
	* Get the port in network format
	* @return
	*	short The network port value
	*/
	short NetAddress::GetNetPort() const
	{
		return _netPort;
	}

}	// Namespace