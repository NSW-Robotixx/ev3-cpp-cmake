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
    class TCPClient
    {
    public:
        TCPClient(const char *serverIp, int port);
        ~TCPClient();
        void sendMessage(const std::string message);
        std::string receiveMessage();
    private:
        char msg[1500];
        int clientSd;
        struct sockaddr_in sendSockAddr;
    };
} // namespace finder::network::tcp
