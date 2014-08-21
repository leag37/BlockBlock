
#include "BBConnectionManager.h"
#include "BBPacket.h"
#include "BBSocket.h"
#include "BBTimer.h"

#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>

using namespace BlockBlock;

int main()
{
    ConnectionManager* connectionManager = new ConnectionManager();
    connectionManager->Initialize(0);

    // Open a socket
    //Socket socket = Socket();
    //socket.Open(0);

    // Send address
    //NetAddress toAddress = NetAddress(127, 0, 0, 1, 30000);

    // Timer
    Timer timer;
    if(timer.Start() == false)
    {
        return -1;
    }

    Packet packet;
    NetAddress address = NetAddress(127, 0, 0, 1, 30000);
    connectionManager->CreateConnection(address);

    do
    {
        // Receive all packets
        connectionManager->Update();
        Connection* connection = connectionManager->GetUnboundConnection();

        if(connection)
        {
            while(connection->Dequeue(packet))
            {
                std::cout << "Got reply: " << (const char*)packet.GetData() << std::endl;
            }	

            // Send packets
            if(timer.GetElapsedTimeMs() > MICROSECONDS_PER_SECOND)
            {
                timer.Reset();

                if(connection->Send(1, sizeof("hello"), (void*)("hello")) == false)
                {
                    printf("failed to send packet\n");
                }
                else
                {
                    printf("sent packet\n");
                }
            }
        }

        // Update the timer
        timer.Update();
    } while(timer.GetElapsedTimeMs() >= 0);

    //socket.Close();

    return 0;
}
