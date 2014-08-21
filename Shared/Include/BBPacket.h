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
     * The size of the data portion of the packet in bytes
     */
#define DATA_PACKET_SIZE 104

    /**
     * Packets are used to send and receive data sent over the network.
     * The basic format of a packet is as follows:
     *	uint32 		GAME_ID 	- A "unique" integer that allows us to prune out known irrelevant packets
     *	uint32 		PACKET_ID 	- A unique counter that indicates the approximate "time" a packet was sent
     *	uint32		ACK			- The most recent acknowledged packet id received
     * 	uint32		ACK_BITFIELD- The bitfield that represents the past 32 packets and whether they have
     *								been acknowledged
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
             * @param packetId The packet ID for this packet
             * @param ack The most recent acknowledged packet
             * @param ackBitfield The bitfield of the last 32 packets
             * @param messageType The message type for this packet
             * @param dataSize The size of the data in this packet
             * @param data A pointer to the data being transfered to this packet
             */
            Packet(uint packetId, uint ack, uint ackBitfield, uint messageType, uchar dataSize, void* data);

            /**
             * Copy constructor
             * @param other The packet to copy
             */
            Packet(const Packet& other);

            /**
             * Destructor
             */
            ~Packet();

            /**
             * Assignment operator
             * @param other The packet to assign
             * @return The resultant packet
             */
            Packet& operator=(const Packet& other);

            /**
             * Get the game id
             * @return The game id for this packet
             */
            uint GetGameId() const;

            /**
             * Get the packet id
             * @return The unique packet id for this packet
             */
            uint GetPacketId() const;

            /**
             * Get the ack for this packet
             * @return The ack value for this packet
             */
            uint GetAck() const;

            /**
             * Get the ack bitfield for this packet
             * @return The ack bitfield for this packet
             */
            uint GetAckBitfield() const;

            /**
             * Get the message type for this packet
             * @return The message type for this packet
             */
            uint GetMessageType() const;

            /**
             * Get packet data size
             * @return The size of the data in the packet
             */
            uchar GetDataSize() const;

            /**
             * Get the data in the packet
             * @return A pointer to the data in the packet
             */
            void* GetData() const;

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
             * The most recent acknowledged packet ID
             */
            uint _ack;

            /**
             * The bitfield of the last 32 packet ids and whether they have been acknowledged
             */
            uint _ackBitfield;

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
