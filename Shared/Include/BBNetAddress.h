// Filename: BBNetAddress.h
// Author: Gael Huber
#ifndef __BBNETADDRESS_H__
#define __BBNETADDRESS_H__

#include "BBPlatform.h"

#include <netinet/in.h>
#include <functional>

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
             * @param a A
             * @param b B
             * @param c C
             * @param d D
             * @param port The port in host format
             */
            NetAddress(uint a, uint b, uint c, uint d, ushort port);

            /**
             * Constructor specifying network value equivalent to A.B.C.D
             * @param address The network address in network format
             * @param port The network port in network format
             */
            NetAddress(uint address, ushort port);

            /**
             * Copy constructor
             * @param other The address to copy
             */
            NetAddress(const NetAddress& other);

            /**
             * Destructor
             */
            ~NetAddress();

            /**
             * Assignment operator
             * @param other The address to assign
             * @return The resultant address
             */
            NetAddress& operator=(const NetAddress& other);

            /**
             * Equivalence operator
             * @param other The NetAddress to compare against
             * @return True if both the socket and port are equal
             */
            bool operator==(const NetAddress& other) const;

            /**
             * Getter for the network address
             * @return The address in network format
             */
            uint GetNetAddress() const;

            /**
             * Getter for A
             * @return Value representative of A
             */
            uint GetA() const;

            /**
             * Getter for B
             * @return Value representative of B
             */
            uint GetB() const;

            /**
             * Getter for C
             * @return Value representative of C
             */
            uint GetC() const;

            /**
             * Getter for D
             * @return Value representative of D
             */
            uint GetD() const;

            /**
             * Get the port in host format
             * @return The host port value
             */
            ushort GetPort() const;

            /**
             * Get the port in network format
             * @return The network port value
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

namespace std
{
    /**
     * Hash function specialization for netaddress
     */
    template<>
    struct hash<BlockBlock::NetAddress> {
        /**
         * Uses a simple hash to get a hash value for a NetAddress
         * @param address The NetAddress to hash
         * @return The hash value of the object
         */
        size_t operator()(const BlockBlock::NetAddress& address) const {
            return std::hash<BlockBlock::uint>()(address.GetNetAddress()) ^ std::hash<BlockBlock::ushort>()(address.GetNetPort());
        }
    };
}

#endif // __BBNETADDRESS_H__
