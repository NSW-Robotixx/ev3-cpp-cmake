#include <gtest/gtest.h>

// include header file
#include <EV3_SensorManager.hpp>
#include <Fakesys.hpp>

TEST(SensorManager, Contructor) {
    using namespace finder::physical::test;
    FakeSys::reinit();
    EXPECT_NO_THROW(finder::physical::SensorManager SM = finder::physical::SensorManager{FakeSys::getWorkingDir()});
}