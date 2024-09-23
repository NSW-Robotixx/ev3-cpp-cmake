#ifndef __EV3_TCP_COMMUNICATION_SERVER_HPP__
#define __EV3_TCP_COMMUNICATION_SERVER_HPP__

#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

#define IP_ADDRESS "localhost"

namespace finder::network::tcp
{
    /// @brief Tcp server class
    class TCPServer
    {
    public:
        TCPServer();
        ~TCPServer();

        /// @brief Start the server
        /// @param port Port to start the server
        void start(int port);

        /// @brief Stop the server
        void stop();

        /// @brief Send a message to the client
        /// @param message Message to send
        void sendMessage(const std::string message);
        
        /// @brief Receive a message from the client
        /// @return Message received
        std::string receiveMessage();
    private:
        int serverSd;
        int newSd;
        struct sockaddr_in servAddr;
        struct sockaddr_in newSockAddr;
        socklen_t newSockAddrSize;
        struct timeval start1, end1;
        int bytesRead, bytesWritten;
        char msg[1500];
    };

    
}

#endif // __EV3_TCP_COMMUNICATION_SERVER_HPP__