// Filename: BBPacket.h
// Author: Gael Huber
#ifndef __BBPACKET_H__
#define __BBPACKET_H__

#include "BBPlatform.h"

namespace BlockBlock
{
	/** \addtogroup Network
	*	@{
	*/

	/**
	* The size of the data portion of the packet
	*/
	#define DATA_PACKET_SIZE 104

	/**
	* Packets are used to send and receive data sent over the network.
	* The basic format of a packet is as follows:
	*	uint32 		GAME_ID 	- A "unique" integer that allows us to prune out known irrelevant packets
	*	uint32 		PACKET_ID 	- A unique counter that indicates the approximate "time" a packet was sent
	*   uint32		MESSAGE_TYPE- A message id represents the identifier for this message so it can be properly
	*								handled by the receiver of the packet (eg. MOVE, ACTION, PAUSE, etc.)
	*	uchar[104]	DATA 		- The first byte in this packet is the number of valid bytes in the packet.
	*								Any subsequent bytes of the remaining 103 bytes are data values
	* The total size of each packet is 128 bytes, which can store up to 10 additional integer values + 3 loose bytes
	*/
	class Packet
	{
	public:
		/**
		* Default constructor
		*/
		Packet();

		/**
		* Constructor specifying packet ID, data size, and data
		* @param
		*	uint The packet ID for this packet
		* @param
		*	uint The message type for this packet
		* @param
		*	uchar The size of the data in this packet
		* @param
		*	void* A pointer to the data being transfered to this packet
		*/
		Packet(uint, uint, uchar, void*);

		/**
		* Copy constructor
		* @param
		*	const Packet& The packet to copy
		*/
		Packet(const Packet&);

		/**
		* Destructor
		*/
		~Packet();

		/**
		* Assignment operator
		* @param
		*	const Packet& The packet to assign
		* @return
		*	Packet& The resultant packet
		*/
		Packet& operator=(const Packet&);

	private:
		/**
		* The game ID
		*/
		uint _gameId;

		/**
		* The packet ID for this packet
		*/
		uint _packetId;

		/**
		* The message type for this packet
		*/
		uint _messageType;

		/**
		* The data stored within this packet
		*/
		uchar _data[DATA_PACKET_SIZE];
	};

	/** @} */

}	// Namespace

#endif // __BBPACKET_H__