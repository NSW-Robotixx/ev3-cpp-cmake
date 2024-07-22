#include <gtest/gtest.h>

#include "Fakesys.hpp"

#ifndef FAKESYS_PATH
#define FAKESYS_PATH "./fakesys"
#endif

namespace finder::physical::test
{
    TEST(FakeSys, testInit) {
        FakeSys::init();
        ASSERT_TRUE(FakeSys::isInitialized());

        // test if the sensor directories are created
        ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/lego-sensor/sensor0"));
        ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/lego-sensor/sensor1"));
        ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/lego-sensor/sensor2"));
        ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/lego-sensor/sensor3"));

        // test if the motor directories are created
        ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor0"));
        ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor1"));
        ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor2"));
        ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor3"));

        // test if the sensor files are correctly created
        for (int i = 0; i < 4; i++) {
            //check if the value files are created
            for (int j = 0; j < 10; j++) {
                ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/lego-sensor/sensor" + std::to_string(i) + "/value" + std::to_string(j)));
            }
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/lego-sensor/sensor" + std::to_string(i) + "/address"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/lego-sensor/sensor" + std::to_string(i) + "/mode"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/lego-sensor/sensor" + std::to_string(i) + "/modes"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/lego-sensor/sensor" + std::to_string(i) + "/num_values"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/lego-sensor/sensor" + std::to_string(i) + "/poll_ms"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/lego-sensor/sensor" + std::to_string(i) + "/command"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/lego-sensor/sensor" + std::to_string(i) + "/commands"));
        }

        // test if the motor files are correctly created
        for (int i = 0; i < 4; i++) {
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/address"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/command"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/commands"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/count_per_rot"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/duty_cycle"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/duty_cycle_sp"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/polarity"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/position"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/position_sp"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/max_speed"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/speed"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/speed_sp"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/ramp_up_sp"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/ramp_down_sp"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/state"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/stop_action"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/stop_actions"));
            ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir() + "/tacho-motor/motor" + std::to_string(i) + "/time_sp"));
        }
    }

    TEST(FakeSys, testDeinit) {
        FakeSys::deinit();
        ASSERT_FALSE(FakeSys::isInitialized());
        ASSERT_FALSE(std::filesystem::exists(FakeSys::getWorkingDir()));
    }
    TEST(FakeSys, testReinit) {
        FakeSys::reinit();
        ASSERT_TRUE(FakeSys::isInitialized());
        ASSERT_TRUE(std::filesystem::exists(FakeSys::getWorkingDir()));
    }

    TEST(FakeSys, testSetGyroSensor) {
        FakeSys::init();
        ASSERT_TRUE(FakeSys::isInitialized());
        FakeSys::setGyroSensorValue(100, 0);
        FakeSys::setGyroSensorMode("GYRO-ANG");
        FakeSys::setGyroSensorNumValues(2);
        FakeSys::setGyroSensorPollMs(200);
        std::ifstream fileValue0(FakeSys::getWorkingDir() + "/lego-sensor/sensor0/value0");
        std::ifstream fileMode(FakeSys::getWorkingDir() + "/lego-sensor/sensor0/mode");
        std::ifstream fileNumValues(FakeSys::getWorkingDir() + "/lego-sensor/sensor0/num_values");
        std::ifstream filePollMs(FakeSys::getWorkingDir() + "/lego-sensor/sensor0/poll_ms");
        std::string value0, mode, numValues, pollMs;
        fileValue0 >> value0;
        fileMode >> mode;
        fileNumValues >> numValues;
        filePollMs >> pollMs;

        fileValue0.close();
        fileMode.close();
        fileNumValues.close();
        filePollMs.close();

        ASSERT_EQ(std::stoi(value0), 100);
        ASSERT_EQ(mode, "GYRO-ANG");
        ASSERT_EQ(std::stoi(numValues), 2);
        ASSERT_EQ(std::stoi(pollMs), 200);
    }
}