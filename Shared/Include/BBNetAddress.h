// Filename: BBNetAddress.h
// Author: Gael Huber
#ifndef __BBNETADDRESS_H__
#define __BBNETADDRESS_H__

#include "BBPlatform.h"

#include <netinet/in.h>

namespace BlockBlock
{
	/** \addtogroup Network
	*	@{
	*/

	/**
	* Defines a network address of the format A.B.C.D (eg. 127.0.0.1)
	*/
	class NetAddress
	{
	public:
		/**
		* Default constructor
		*/
		NetAddress();

		/**
		* Constructor specifying A.B.C.D to compose network address
		* @param
		*	uint A
		* @param
		*	uint B
		* @param
		*	uint C
		* @param
		*	uint D
		* @param
		*	ushort The port in host format
		*/
		NetAddress(uint, uint, uint, uint, ushort);

		/**
		* Constructor specifying network value equivalent to A.B.C.D
		* @param
		*	uint The network address in network format
		* @param
		*	ushort The network port in network format
		*/
		NetAddress(uint, ushort);

		/**
		* Copy constructor
		* @param
		*	const NetAddress& The address to copy
		*/
		NetAddress(const NetAddress&);

		/**
		* Destructor
		*/
		~NetAddress();

		/**
		* Assignment operator
		* @param
		*	const NetworkAddress& The address to assign
		* @return
		*	NetworkAddress& The resultant address
		*/
		NetAddress& operator=(const NetAddress&);

		/**
		* Getter for the network address
		* @return
		*	uint The address in network format
		*/
		uint GetNetAddress() const;

		/**
		* Getter for A
		* @return
		*	uint Value representative of A
		*/
		uint GetA() const;

		/**
		* Getter for B
		* @return
		*	uint Value representative of B
		*/
		uint GetB() const;

		/**
		* Getter for C
		* @return
		*	uint Value representative of C
		*/
		uint GetC() const;

		/**
		* Getter for D
		* @return
		*	uint Value representative of D
		*/
		uint GetD() const;

		/**
		* Get the port in host format
		* @return
		*	ushort The host port value
		*/
		ushort GetPort() const;

		/**
		* Get the port in network format
		* @return
		*	ushort The network port value
		*/
		ushort GetNetPort() const;

	private:
		/**
		* Network address in host form
		*/
		uint _hostAddress;

		/**
		* Network address in network form
		*/
		uint _netAddress;

		/**
		* Port in host form
		*/
		ushort _hostPort;

		/**
		* Port in network form
		*/
		ushort _netPort;
	};

	/** @} */

}	// Namespace

#endif // __BBNETADDRESS_H__