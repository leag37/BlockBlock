// Filename: BBClient.cpp
// Author: Gael Huber
#include "BBClient.h"

namespace BlockBlock
{
	/**
	 * Default constructor
	 */
	Client::Client()
	{

	}

	/**
	 * Destructor
	 */
	Client::~Client()
	{

	}

	/**
	 * Initialize the client
	 * @return Returns true if the initialization is successful
	 */
	bool Client::Initialize()
	{
		// Create the connection manager to manage all incoming messages
		_connectionManager = new ConnectionManager();
		if(_connectionManager->Initialize(0) == false)
		{
			return false;
		}

		// Create the player
		NetAddress address = NetAddress(127, 0, 0, 1, 30000);
		_player = new NetworkPlayer();
		if(_player->Initialize(address) == false)
		{
			return false;
		}

		return true;
	}

	/**
	 * Shut down the client
	 */
	void Client::Shutdown()
	{
		if(_connectionManager)
		{
			_connectionManager->Shutdown();
			delete _connectionManager;
			_connectionManager = 0;
		}
	}

	/**
	 * Run the client
	 */
	void Client::Run()
	{
		// Setup the main client loop
		bool isRunning = true;
		while(isRunning)
		{
			// Update the connection manager and receive any messages
			if(_player->Update() == false)
			{
				isRunning = false;
			}
		}
	}

}	// Namespace