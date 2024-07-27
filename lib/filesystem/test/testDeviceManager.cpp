#include <gtest/gtest.h>

// include file to be tested
#include <DeviceManager.hpp>
#include <Fakesys.hpp>

namespace finder::physical
{
    using namespace finder::physical::test;
    
    TEST(DeviceManagerTest, testDeviceManager)
    {
        FakeSys::init();

        EXPECT_NO_THROW(DeviceManager deviceManager(FakeSys::getWorkingDir()));
    }
}

// other includes