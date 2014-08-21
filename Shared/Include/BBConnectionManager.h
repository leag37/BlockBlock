// Filename: BBConnectionManager.h
// Author: Gael Huber
#ifndef __BBCONNECTIONMANAGER_H__
#define __BBCONNECTIONMANAGER_H__

#include "BBSingleton.h"
#include "BBNetAddress.h"
#include "BBConnection.h"

#include <unordered_map>

namespace BlockBlock
{
	/** \addtogroup Network
	*	@{
	*/

	/**
	* Manages all existing connections and the sending and receiving of data
	*/
	class ConnectionManager : public Singleton<ConnectionManager>
	{
	public:
		/**
		* Default constructor
		*/
		ConnectionManager();

		/**
		* Destructor
		*/
		~ConnectionManager();

		/**
		* Get the singleton pointer
		* @return The pointer to the singleton instance
		*/
		static ConnectionManager* GetSingletonPtr();

		/**
		* Get a reference to the singleton reference
		* @return The reference to the singleton instance
		*/
		static ConnectionManager& GetSingleton();

		/**
		* Initialize the connection manager
		* @param The default port to use when listening
		* @return Returns true if the initialization is successful
		*/
		bool Initialize(ushort port);

		/**
		* Shutdown the connection manager
		*/
		void Shutdown();

		/**
		* Update the connection manager. This will poll all active connections
		* for messages and create new connections. 
		*/
		void Update();

		/**
		* Create a connection
		* @param address The address on which to create a connection
		* @return The created connection
		*/
		Connection* CreateConnection(const NetAddress& address);

		/**
		* Get an unbound connection
		* @return A pointer to an unbound connection. If none are available, return 0
		*/
		Connection* GetUnboundConnection() const;

		/**
		* Register a bound connection
		* @param connection A pointer to the connection to bind
		* @return Return true if the connection is bound successfully
		*/
		bool BindConnection(Connection* connection);

	private:
		/**
		* The socket on this machine
		*/
		Socket _socket;

		/**
		* Map of existing connections (hashed on the address)
		*/
		std::unordered_map<NetAddress, Connection*> _openConnections;

		/**
		* Unbound connections, these are connections that are not paired with any data outside receiving messages
		*/
		std::unordered_map<NetAddress, Connection*> _unboundConnections;

		/**
		* Map of broken connections
		*/
		std::unordered_map<NetAddress, Connection*> _closedConnections;
	};

	/** @} */

}	// Namespace

#endif // __BBCONNECTIONMANAGER_H__