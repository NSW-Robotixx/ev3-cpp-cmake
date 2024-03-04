#include <gtest/gtest.h>
#include <console/Logger.test.cpp>
#include <test2.cpp>
#include <src.test.cpp>
#include <physical/portManager/port/Port.test.cpp>
#include <physical/portManager/PortManager.test.cpp>
#include <physical/portManager/port/SensorPort.test.cpp>
#include <physical/portManager/port/MotorPort.test.cpp>
#include <math/Vector3.test.cpp>
// #include <math/Vector2.test.cpp>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
