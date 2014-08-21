// Filename: BBPacket.cpp
// Author: Gael Huber
#include "BBPacket.h"

#include <string.h>
#include <iostream>

namespace BlockBlock
{
    /**
     * Default constructor
     */
    Packet::Packet()
        :	_gameId(GAME_IDENTIFIER)
    {

    }

    /**
     * Constructor specifying packet ID, data size, and data
     * @param packetId The packet ID for this packet
     * @param ack The most recent acknowledged packet
     * @param ackBitfield The bitfield of the last 32 packets
     * @param messageType The message type for this packet
     * @param dataSize The size of the data in this packet
     * @param data A pointer to the data being transfered to this packet
     */
    Packet::Packet(uint packetId, uint ack, uint ackBitfield, uint messageType, uchar dataSize, void* data)
        :	_gameId(GAME_IDENTIFIER),
        _packetId(packetId),
        _ack(ack),
        _ackBitfield(ackBitfield),
        _messageType(messageType)
    {
        _data[0] = dataSize;
        memcpy(&(_data[1]), data, dataSize);
    }

    /**
     * Copy constructor
     * @param other The packet to copy
     */
    Packet::Packet(const Packet& other)
        :	_gameId(other._gameId),
        _packetId(other._packetId),
        _ack(other._ack),
        _ackBitfield(other._ackBitfield),
        _messageType(other._messageType)
    {
        memcpy(_data, other._data, DATA_PACKET_SIZE);
    }

    /**
     * Destructor
     */
    Packet::~Packet()
    {

    }

    /**
     * Assignment operator
     * @param other The packet to assign
     * @return The resultant packet
     */
    Packet& Packet::operator=(const Packet& other)
    {
        _gameId = other._gameId;
        _packetId = other._packetId;
        _ack = other._ack;
        _ackBitfield = other._ackBitfield;
        _messageType = other._messageType;
        memcpy(_data, other._data, DATA_PACKET_SIZE);
        return *this;
    }

    /**
     * Get the game id
     * @return The game id for this packet
     */
    uint Packet::GetGameId() const
    {
        return _gameId;
    }

    /**
     * Get the packet id
     * @return The unique packet id for this packet
     */
    uint Packet::GetPacketId() const
    {
        return _packetId;
    }

    /**
     * Get the ack for this packet
     * @return The ack value for this packet
     */
    uint Packet::GetAck() const
    {
        return _ack;
    }

    /**
     * Get the ack bitfield for this packet
     * @return The ack bitfield for this packet
     */
    uint Packet::GetAckBitfield() const
    {
        return _ackBitfield;
    }

    /**
     * Get the message type for this packet
     * @return The message type for this packet
     */
    uint Packet::GetMessageType() const
    {
        return _messageType;
    }

    /**
     * Get packet data size
     * @return The size of the data in the packet
     */
    uchar Packet::GetDataSize() const
    {
        return _data[0];
    }

    /**
     * Get the data in the packet
     * @return A pointer to the data in the packet
     */
    void* Packet::GetData() const
    {
        return (void*)&_data[1];
    }

}	// Namespace
