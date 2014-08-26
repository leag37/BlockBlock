// Filename: BBNetworkPlayer.cpp
// Author: Gael Huber
#include "BBNetworkPlayer.h"

namespace BlockBlock
{
	/**
	* Default constructor
	*/
	NetworkPlayer::NetworkPlayer()
	{

	}

	/**
	* Network player constructor specifying connection object
	* @param connection The connection object for this networked player
	*/
	NetworkPlayer::NetworkPlayer(Connection* connection)
	{

	}

	/**
	 * Copy constructor
	 * @param other The player object to copy
	 */
	NetworkPlayer::NetworkPlayer(const NetworkPlayer& other)
	{
	}

	/**
	* Destructor
	*/
	NetworkPlayer::~NetworkPlayer()
	{

	}

	/**
	* Parse all pending messages for the network object. This will also take care of
	* ensuring that hearbeat messages are sent at a regular interval to maintain a
	* healthy connection.
	*/
	void NetworkPlayer::ParseMessages()
	{
	}

	/**
	* Initialize the network player
	* @param address The starting address for the connection (this address may be updated depending
	*	on messages from the connecting socket)
	* @return Returns true if the network player is initialized successfully
	*/
	bool NetworkPlayer::Initialize(const NetAddress& address)
	{
		return false;
	}

	/**
	* Shut down the player
	*/
	void NetworkPlayer::Shutdown()
	{

	}

	/** 
	* Update the player. This might be managing the network state, sending/receiving
	* queued messages, etc.
	* @return Returns true if the update is successful
	*/
	bool NetworkPlayer::Update()
	{
		return false;
	}

}	// namespace