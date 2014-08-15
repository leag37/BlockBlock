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
		NetAddress(int, int, int, int, short);

		/**
		* Constructor specifying network value equivalent to A.B.C.D
		* @param
		*	int The network address in network format
		* @param
		*	short The network port in network format
		*/
		NetAddress(int, short);

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
		*	int The address in network format
		*/
		int GetNetAddress() const;

		/**
		* Getter for A
		* @return
		*	int Value representative of A
		*/
		int GetA() const;

		/**
		* Getter for B
		* @return
		*	int Value representative of B
		*/
		int GetB() const;

		/**
		* Getter for C
		* @return
		*	int Value representative of C
		*/
		int GetC() const;

		/**
		* Getter for D
		* @return
		*	int Value representative of D
		*/
		int GetD() const;

		/**
		* Get the port in host format
		* @return
		*	short The host port value
		*/
		short GetPort() const;

		/**
		* Get the port in network format
		* @return
		*	short The network port value
		*/
		short GetNetPort() const;

	private:
		/**
		* Network address in host form
		*/
		int _hostAddress;

		/**
		* Network address in network form
		*/
		int _netAddress;

		/**
		* Port in host form
		*/
		short _hostPort;

		/**
		* Port in network form
		*/
		short _netPort;
	};

	/** @} */

}	// Namespace

#endif // __BBNETADDRESS_H__