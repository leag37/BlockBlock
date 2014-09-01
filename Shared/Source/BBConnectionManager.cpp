// Filename: BBConnectionManager.cpp
// Author: Gael Huber
#include "BBConnectionManager.h"

namespace BlockBlock
{
    ConnectionManager::ConnectionManager()
    {

    }

    /**
     * Destructor
     */
    ConnectionManager::~ConnectionManager()
    {

    }

    /**
     * Get the singleton pointer
     * @return The pointer to the singleton instance
     */
    ConnectionManager* ConnectionManager::GetSingletonPtr()
    {
        return _instance;
    }

    /**
     * Get a reference to the singleton reference
     * @return The reference to the singleton instance
     */
    ConnectionManager& ConnectionManager::GetSingleton()
    {
        return *_instance;
    }

    /**
     * Initialize the connection manager
     * @param port The default port to use when listening
     * @return Returns true if the initialization is successful
     */
    bool ConnectionManager::Initialize(ushort port)
    {
        // Create the host socket
        return _socket.Open(port);
    }

    /**
     * Shutdown the connection manager
     */
    void ConnectionManager::Shutdown()
    {
        // Close the socket
        _socket.Close();
    }

    /**
     * Update the connection manager. This will poll all active connections
     * for messages and create new connections. 
     */
    void ConnectionManager::Update()
    {
        // While there are valid messages on the socket, interpret them
        NetAddress address;
        Packet packet;
        // We must receive at least sizeof(uint) bytes to read the game identifier from the packet

        while(_socket.Receive(address, (void*)&packet, sizeof(Packet)) > (int)sizeof(uint))
        {
            // First, check whether the packet's gameId is the same as the expected game id
            if(packet.GetGameId() != GAME_IDENTIFIER)
            {
                continue;
            }

            // Try to find an existing connection
            std::unordered_map<NetAddress, Connection*>::iterator connectionItr = _openConnections.find(address);
            Connection* connection = 0;

            // If the connection is not found in the open list, check the closed list
            if(connectionItr == _openConnections.end())
            {
                connectionItr = _closedConnections.find(address);

                // If it is not found in the closed list, create it and add it
                if(connectionItr == _closedConnections.end())
                {
                    connection = new Connection(_socket, address);
                    _openConnections[address] = connection;
                    _unboundConnections[address] = connection;
                }
                else
                {
                    connection = connectionItr->second;
                }
            }
            else
            {
                connection = connectionItr->second;
            }

            // Now that we have a connection, pass the packet data along to the connection
            connection->Enqueue(packet);
        }
    }

    /**
     * Create a connection
     * @param address The address on which to create a connection
     * @return The created connection
     */
    Connection* ConnectionManager::CreateConnection(const NetAddress& address)
    {
        Connection* connection = new Connection(_socket, address);
        _unboundConnections[address] = connection;
        return connection;
    }

    /**
     * Get an unbound connection
     * @return A pointer to an unbound connection. If none are available, return 0
     */
    Connection* ConnectionManager::GetUnboundConnection() const
    {
        if(_unboundConnections.size() == 0)
        {
            return 0;
        }

        return _unboundConnections.begin()->second;
    }

    /**
     * Register a bound connection
     * @param connection A pointer to the connection to bind
     * @return Return true if the connection is bound successfully
     */
    bool ConnectionManager::BindConnection(Connection* connection)
    {
        // Ensure the connection is still unbound
        std::unordered_map<NetAddress, Connection*>::iterator itr = _unboundConnections.find(connection->GetNetAddress());
        if(itr != _unboundConnections.end())
        {
            _unboundConnections.erase(itr);
            return true;
        }
        else
        {
            return false;
        }
    }

}	// Namespace
