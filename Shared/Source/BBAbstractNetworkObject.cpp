// Filename: BBAbstractNetworkObject.cpp
// Author: Gael Huber
#include "BBAbstractNetworkObject.h"

namespace BlockBlock
{
    /**
     * Default constructor
     */
    AbstractNetworkObject::AbstractNetworkObject()
        :  
        _connection(0)
    {

    }

    /**
    * Constructor with target connection
    * @param connection The connection to use with this network object
    */
    AbstractNetworkObject::AbstractNetworkObject(Connection* connection)
        :
        _connection(connection)
    {

    }

    /**
     * Destructor
     */
    AbstractNetworkObject::~AbstractNetworkObject()
    {
        _connection = 0;
    }

    /**
     * Send a message to this network object
     * @param messageType The identifier for this network message
     * @param messageSize The size of the message in bytes
     * @param messageData The data ov hte message
     * @return Returns true if the message was sent successfully
     */
    bool AbstractNetworkObject::SendMessage(uint messageType, uchar messageSize, void* messageData)
    {
        // If there is a connection object, try to send the message and return the result
        if(_connection)
        {
            return _connection->Send(messageType, messageSize, messageData);
        }

        // No connection object, return false
        return false;
    }

    /**
     * Send multiple pieces of data to the network object
     * @param messageTypes The array of message types
     * @param messageSizes The array of message sizes
     * @param messageData The array of data pointers
     * @param messageCount The number of messages being sent
     * @return Returns true if all messages were sent successfully
     */
    bool AbstractNetworkObject::SendMessages(uint* messageTypes, uchar* messageSizes, void* messageData, uint messageCount)
    {
        // If there is a connection object, try to send the message and return the result
        if(_connection)
        {
            // Store the current index in the message data
            char* data = static_cast<char*>(messageData);

            // Iterate through each message and send each one
            for(uint i = 0; i < messageCount; ++i)
            {
                
                // Cache the message size
                uchar messageSize = messageSizes[i];

                // Send a message
                if(_connection->Send(messageTypes[i], messageSize, static_cast<void*>(data)) == false)
                {
                    return false;
                }

                // Move the data pointer forward to the next message
                data += messageSize;
            }

            // All messages sent properly, return true
            return true;
        }

        // No connection object, return false
        return false;
    }
            
}   // Namespace