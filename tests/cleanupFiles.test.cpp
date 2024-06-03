#include <gtest/gtest.h>

#include <filesystem>


TEST(SensorPort, cleanUp)
{
    std::filesystem::remove_all("./test");

    ASSERT_FALSE(std::filesystem::exists("./test/lego-sensor/sensor0/value0"));
}