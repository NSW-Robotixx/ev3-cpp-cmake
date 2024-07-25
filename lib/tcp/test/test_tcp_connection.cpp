#include <gtest/gtest.h>

#include <EV3_tcp_communication_client.hpp>
#include <EV3_tcp_communication_server.hpp>

#include <thread>

namespace finder::network::tcp
{
    TEST(TCPConnection, TestConnection)
    {
        std::thread serverThread([]()
        {
            TCPServer server{};
            server.start(54000);
            std::string message = server.receiveMessage();

            EXPECT_EQ(message, "Hello, server!");

            server.sendMessage("Hello, client!");
        });

        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        TCPClient client("localhost", 54000);
        client.sendMessage("Hello, server!");

        std::string response = client.receiveMessage();

        EXPECT_EQ(response, "Hello, client!");

        serverThread.join();
    }
} // namespace finder::network::tcp