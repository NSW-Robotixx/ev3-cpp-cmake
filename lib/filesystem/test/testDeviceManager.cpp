#include <gtest/gtest.h>

// include file to be tested
#include <DeviceManager.hpp>
#include <Fakesys.hpp>

namespace finder::physical
{
    using namespace finder::physical::test;

    TEST(DeviceManagerTest, testDeviceManager)
    {
        DeviceManager deviceManager(FakeSys::getWorkingDir());
        
    }
}

// other includes