#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <EV3_Gearbox.hpp>
#include <Fakesys.hpp>

namespace finder::physical
{
    class GearboxManagerTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            finder::physical::test::FakeSys::reinit();
            device_manager = std::make_unique<DeviceManager>(finder::physical::test::FakeSys::getWorkingDir());
            device_manager->reinit();
            gearbox_manager = std::make_unique<GearboxManager>();
        }

        std::unique_ptr<DeviceManager> device_manager;
        std::unique_ptr<GearboxManager> gearbox_manager;
    };

    TEST_F(GearboxManagerTest, TestInitialization)
    {
        EXPECT_NO_THROW(gearbox_manager->calibrate());
    }

    TEST_F(GearboxManagerTest, TestSetGear)
    {
        gearbox_manager->calibrate();
        auto result = gearbox_manager->setGear(GearboxGears::EV3_GEARBOX_GEAR_1);
        EXPECT_TRUE(result);
    }

    TEST_F(GearboxManagerTest, TestGetGear)
    {
        gearbox_manager->calibrate();
        gearbox_manager->setGear(GearboxGears::EV3_GEARBOX_GEAR_2);
        auto result = gearbox_manager->getGear();
        ASSERT_TRUE(result);
        EXPECT_EQ(result.value(), GearboxGears::EV3_GEARBOX_GEAR_2);
    }

    TEST_F(GearboxManagerTest, TestCalibration)
    {
        auto result = gearbox_manager->calibrate();
        EXPECT_TRUE(!result);
    }

    TEST_F(GearboxManagerTest, TestSetGearNotInitialized)
    {
        auto result = gearbox_manager->setGear(GearboxGears::EV3_GEARBOX_GEAR_1);
        EXPECT_TRUE(result);
    }

    TEST_F(GearboxManagerTest, TestGetGearNotInitialized)
    {
        auto result = gearbox_manager->getGear();
        EXPECT_TRUE(result);
    }
} // namespace finder::physical
