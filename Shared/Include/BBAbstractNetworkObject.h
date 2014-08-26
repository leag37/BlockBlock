// Filename: BBAbstractNetworkObject.h
// Author: Gael Huber
#ifndef __BBABSTRACTNETWORKOBJECT_H__
#define __BBABSTRACTNETWORKOBJECT_H__

#include "BBPlatform.h"
#include "BBConnection.h"

namespace BlockBlock
{
    /** \addtogroup Network
     * @{
     */

    /**
     * Interface responsible for container networked objects. Network objects own references to connections
     * and are responsible for interpreting messages
     */
    class AbstractNetworkObject
    {
        public:
            /**
             * Default constructor
             */
            AbstractNetworkObject();

            /**
            * Constructor with target connection
            * @param connection The connection to use with this network object
            */
            AbstractNetworkObject(Connection* connection);

            /**
             * Destructor
             */
            virtual ~AbstractNetworkObject();

            /**
             * Parse all pending messages for the network object 
             */
            virtual void ParseMessages() = 0;

            /**
             * Send a message to this network object
             * @param messageType The identifier for this network message
             * @param messageSize The size of the message in bytes
             * @param messageData The data ov hte message
             * @return Returns true if the message was sent successfully
             */
            bool SendMessage(uint messageType, uchar messageSize, void* messageData);

            /**
             * Send multiple pieces of data to the network object
             * @param messageTypes The array of message types
             * @param messageSizes The array of message sizes
             * @param messageData The array of data pointers
             * @param messageCount The number of messages being sent
             * @return Returns true if all messages were sent successfully
             */
            bool SendMessages(uint* messageTypes, uchar* messageSizes, void* messageData, uint messageCount);
            
        protected:
            /**
             * The connection referenced by this network object
             */
            Connection* _connection;
    };

    /** @} */

}   // Namespace

#endif // __BBABSTRACTNETWORKOBJECT_H__
