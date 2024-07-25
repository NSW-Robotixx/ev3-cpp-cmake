#include <EV3_tcp_communication_client.hpp>

namespace finder::network::tcp
{
    TCPClient::TCPClient(const char *serverIp, int port)
    {
        //setup a socket and connection tools
        struct hostent* host = gethostbyname(serverIp);
        bzero((char*)&sendSockAddr, sizeof(sendSockAddr));
        sendSockAddr.sin_family = AF_INET;
        sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
        sendSockAddr.sin_port = htons(port);
        clientSd = socket(AF_INET, SOCK_STREAM, 0);
        std::cout << "try to connect...";
        int status = connect(clientSd, (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
        if(status < 0)
        {
            std::cerr << "Error connecting to socket!" << std::endl;
            exit(0);
        }
        std::cout << "Connected to the server!" << std::endl;
    }

    TCPClient::~TCPClient()
    {
        close(clientSd);
        std::cout << "Connection closed" << std::endl;
    }

    void TCPClient::sendMessage(const std::string message)
    {
        // clear the buffer
        memset(&msg, 0, sizeof(msg));
        // copy message to buffer
        strcpy(msg, message.c_str());

        send(clientSd, (char*)&msg, strlen(msg), 0);
    }

    std::string TCPClient::receiveMessage()
    {
        char msg[1500];
        memset(&msg, 0, sizeof(msg));
        recv(clientSd, (char*)&msg, sizeof(msg), 0);
        if(strcmp(msg, "exit") == 0)
        {
            close(clientSd);
            std::cout << "Server has quit the session" << std::endl;
        }
        return std::string(msg);
    }

} // namespace finder::network::tcp