// Filename: BBClient.h
// Author: Gael Huber
#ifndef __BBCLIENT_H__
#define __BBCLIENT_H__

#include "BBPlatform.h"
#include "BBConnectionManager.h"
#include "BBNetworkPlayer.h"

namespace BlockBlock
{
	/** \addtogroup Client
	*	@{
	*/

	/**
	 * The class owns a client instance and runs the game simulation for a client.
	 */
	class Client
	{
	public:
		/**
		 * Default constructor
		 */
		Client();

		/**
		 * Destructor
		 */
		~Client();

		/**
		 * Initialize the client
		 * @return Returns true if the initialization is successful
		 */
		bool Initialize();

		/**
		 * Shut down the client
		 */
		void Shutdown();

		/**
		 * Run the client
		 */
		void Run();

	private:
		/**
		 * Manager for connections and incoming messages
		 */
		ConnectionManager* _connectionManager;

		/**
		 * The network player for this connection
		 */
		NetworkPlayer* _player;
	};


	/** @} */
}

#endif // __BBCLIENT_H__