#include <gtest/gtest.h>

// include header file
#include <EV3_MotorManager.hpp>
#include <Fakesys.hpp>

TEST(MotorManager, Contructor) {
    using namespace finder::physical::test;
    FakeSys::init();
    finder::physical::MotorManager MM = finder::physical::MotorManager{FakeSys::getWorkingDir()};
}