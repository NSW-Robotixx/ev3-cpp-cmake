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

namespace finder::network::tcp
{
    /// @brief Tcp client class
    class TCPClient
    {
    public:
        /// @brief Constructor
        /// @param serverIp Hostname of the server
        /// @param port Port to connect
        TCPClient(const char *serverIp, int port);

        ~TCPClient();

        /// @brief Send a message to the server
        /// @param message Message to send
        void sendMessage(const std::string message);

        /// @brief Receive a message from the server
        /// @return Message received
        std::string receiveMessage();
    private:
        char msg[1500];
        int clientSd;
        struct sockaddr_in sendSockAddr;
    };
} // namespace finder::network::tcp
