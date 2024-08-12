#include <gtest/gtest.h>

#include <EV3_compute.hpp>
#include <EV3_tcp_communication_client.hpp>
#include <thread>

TEST(EV3_compute, DefaultConstructor)
{
    finder::compute::EV3_compute ev3_compute;
    // ev3_compute.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));


    std::cout << "EV3_compute started" << std::endl;
    ::finder::network::tcp::TCPClient tcp_client("localhost", EV3_COMPUTE_PORT);



    tcp_client.sendMessage("1.0,2.0;12.0,15.0");

    std::string response = tcp_client.receiveMessage();

    EXPECT_EQ(response, "1.000000,2.000000;12.000000,15.000000");
}