#include <gtest/gtest.h>

#include <EV3_compute.hpp>
#include <EV3_tcp_communication_client.hpp>
#include <thread>

TEST(EV3_compute, DefaultConstructor)
{
    finder::compute::EV3_compute ev3_compute;
    // ev3_compute.start();

    std::this_thread::sleep_for(std::chrono::seconds(1));


    std::cout << "EV3_compute started" << std::endl;
    ::finder::network::tcp::TCPClient tcp_client("localhost", 34001);



    tcp_client.sendMessage("1.0,2.0;3.0,4.0");

    std::string response = tcp_client.receiveMessage();

    EXPECT_EQ(response, "1.0,2.0;3.0,4.0");
}