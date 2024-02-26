#include <gtest/gtest.h>

#include <console/Logger.hpp>
#include <physical/portManager/PortManager.hpp>

TEST(PortManager, readPorts)
{
    using namespace finder::physical;

    PortManager DM = PortManager{};

    DM.readPorts();

    ASSERT_EQ(DM.getNumberOfDevices(), 0);
} 