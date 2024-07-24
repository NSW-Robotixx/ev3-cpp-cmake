#include <gtest/gtest.h>

// include tests in subdirectories
// #include <portManager/port/MotorPort.test.cpp>
// #include <portManager/port/SensorPort.test.cpp>
// #include <portManager/port/Port.test.cpp>

#include <portManager/PortManager.hpp>

#include <Fakesys.hpp>

TEST(PortManager, readPorts)
{
    using namespace finder::physical;
    using namespace finder::physical::test;

    FakeSys::init();

    PortManager DM = PortManager{FakeSys::getWorkingDir()};

    DM.readPorts();

    ASSERT_EQ(DM.getNumberOfDevices(), 8);
} 