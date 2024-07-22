#include <gtest/gtest.h>

// include tests in subdirectories
// #include <portManager/port/MotorPort.test.cpp>
// #include <portManager/port/SensorPort.test.cpp>
// #include <portManager/port/Port.test.cpp>

#include <portManager/PortManager.hpp>

TEST(PortManager, readPorts)
{
    using namespace finder::physical;

    PortManager DM = PortManager{"./fakesys"};

    DM.readPorts();

    ASSERT_EQ(DM.getNumberOfDevices(), 4);
} 