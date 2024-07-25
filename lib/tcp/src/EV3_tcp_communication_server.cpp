#include <EV3_tcp_communication_server.hpp>

namespace finder::network::tcp
{
    TCPServer::TCPServer()
    {
    }

    TCPServer::~TCPServer()
    {
    }

    void TCPServer::start(int port)
    {
        //setup a socket and connection tools
        bzero((char*)&servAddr, sizeof(servAddr));
        servAddr.sin_family = AF_INET;
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servAddr.sin_port = htons(port);
        //open stream oriented socket with internet address
        //also keep track of the socket descriptor
        serverSd = socket(AF_INET, SOCK_STREAM, 0);
        if(serverSd < 0)
        {
            std::cerr << "Error establishing the server socket" << std::endl;
            exit(0);
        }
        //bind the socket to its local address
        int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, 
            sizeof(servAddr));
        if(bindStatus < 0)
        {
            std::cerr << "Error binding socket to local address" << std::endl;
            exit(0);
        }
        std::cout << "Waiting for a client to connect..." << std::endl;
        //listen for up to 5 requests at a time
        listen(serverSd, 5);
        //receive a request from client using accept
        //we need a new address to connect with the client
        newSockAddrSize = sizeof(newSockAddr);
        //accept, create a new socket descriptor to 
        //handle the new connection with client
        newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
        if(newSd < 0)
        {
            std::cerr << "Error accepting request from client!" << std::endl;
            exit(1);
        }
        std::cout << "Connected with client!" << std::endl;
        //lets keep track of the session time
        gettimeofday(&start1, NULL);
        //also keep track of the amount of data sent as well
        bytesRead = 0;
        bytesWritten = 0;
    }

    void TCPServer::stop()
    {
        close(serverSd);
        close(newSd);
    }

    void TCPServer::sendMessage(const std::string message)
    {
        memset(&msg, 0, sizeof(message));
        strcpy(msg, message.c_str());
        bytesWritten += send(newSd, (char*)msg, strlen(msg), 0);
    }

    std::string TCPServer::receiveMessage()
    {
        // clear the message buffer
        memset(&msg, 0, sizeof(msg));

        bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);

        if (strcmp(msg, "exit") == 0)
        {
            this->stop();
            return "exit";
        }

        std::cout << "Received: " << msg << std::endl;

        return std::string(msg);
    }

} // namespace finder::network::tcp