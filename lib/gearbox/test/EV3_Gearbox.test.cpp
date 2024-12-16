#include <gtest/gtest.h>

#include <spdlog/spdlog.h>

#include <EV3_Gearbox.hpp>
#include <Fakesys.hpp>

namespace finder::physical
{
    TEST(GearboxManagerTest, TestGearboxManager)
    {
        using namespace finder::physical::test;

        finder::physical::test::FakeSys::init();

        DeviceManager device_manager = DeviceManager(FakeSys::getWorkingDir());

        GearboxManager gearbox_manager = GearboxManager();
        gearbox_manager.calibrate();
    }
} // namespace finder::physical