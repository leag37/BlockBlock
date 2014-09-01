// Filename: BBSocket.h
// Author: Gael Huber
#ifndef __BBSOCKET_H__
#define __BBSOCKET_H__

#include "BBPlatform.h"
#include "BBNetAddress.h"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

namespace BlockBlock
{
    /** \addtogroup Network
     *	@{
     */

    /**
     * This class owns a UDP network socket and manages the sending and receiving of data
     */
    class Socket
    {
        public:
            /**
             * Default constructor
             */
            Socket();

            /**
             * Copy constructor
             * @param other The socket to copy
             */
            Socket(const Socket& other);

            /**
             * Destructor
             */
            ~Socket();

            /**
             * Assignment operator
             * @param other The socket to copy
             * @return The resultant socket
             */
            Socket& operator=(const Socket& other);

            /**
             * Open a socket on a specified port
             * @param port The port number. If 0 is specified, any port is used
             * @return Returns true if the port is successfully open
             */
            bool Open(ushort port);

            /**
             * Close any open socket
             */
            void Close();

            /**
             * Returns whether the socket is currently open
             * @return Returns true if there is an open socket, false otherwise
             */
            bool IsOpen() const;

            /**
             * Send a packet to a target NetAddress
             * @param toAddress The network address to send the data
             * @param data A pointer to the data to send
             * @param size The length of the data to send
             * @return Returns true if successfully sent
             */
            bool Send(const NetAddress& toAddress, void* data, int size);

            /**
             * Receive data over the socket
             * @param fromAddress The sender of the packet
             * @param data A pointer to the data to receive
             * @param maxSize The maximum size of the data to receive
             * @return The number of bytes read
             */
            int Receive(NetAddress& fromAddress, void* data, int maxSize);

        private:
            /**
             * A handle to the socket
             */
            int _socket;
    };

    /** @} */
}	// Namespace

#endif // __BBSOCKET_H__
