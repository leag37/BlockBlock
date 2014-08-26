// Filename: BBNetworkPlayer.h
// Author: Gael Huber
#ifndef __BBNETWORKPLAYER_H__
#define __BBNETWORKPLAYER_H__

#include "BBAbstractNetworkObject.h"

namespace BlockBlock
{
	/** \addtogroup Network
	* 	@{
	*/

	/**
	 * A network player represents the player state with the current network connection. This manages active
	 * connection, login status, package sending, package receiving, etc.
	 */
	class NetworkPlayer : public AbstractNetworkObject
	{
	public:
		/**
		 * Default constructor
		 */
		NetworkPlayer();

		/**
		 * Network player constructor specifying connection object
		 * @param connection The connection object for this networked player
		 */
		NetworkPlayer(Connection* connection);

		/**
		 * Copy constructor
		 * @param other The player object to copy
		 */
		NetworkPlayer(const NetworkPlayer& other);

		/**
		 * Destructor
		 */
		~NetworkPlayer();

		/**
         * Parse all pending messages for the network object. This will also take care of
         * ensuring that hearbeat messages are sent at a regular interval to maintain a
         * healthy connection.
         */
        void ParseMessages();

        /**
         * Initialize the network player
         * @param address The starting address for the connection (this address may be updated depending
         *	on messages from the connecting socket)
         * @return Returns true if the network player is initialized successfully
         */
		bool Initialize(const NetAddress& address);

		/**
		 * Shut down the player
		 */
		 void Shutdown();

		 /** 
		  * Update the player. This might be managing the network state, sending/receiving
		  * queued messages, etc.
		  * @return Returns true if the update is successful
		  */
		 bool Update();


	private:
	};

	/** @} */

}	// Namespace

#endif // __BBNETWORKPLAYER_H__