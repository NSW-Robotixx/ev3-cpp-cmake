#include <gtest/gtest.h>

#include <spdlog/spdlog.h>

#include <EV3_Gearbox.hpp>

namespace finder::physical
{
    TEST(GearboxManagerTest, TestGearboxManager)
    {
        GearboxManager gearbox_manager = GearboxManager();
        gearbox_manager.calibrate();
    }
} // namespace finder::physical