#include <gtest/gtest.h>
#include <Logger.test.cpp>
#include <PortManager.test.cpp>
#include <Screen.test.cpp>
#include <Vector2.test.cpp>
// #include <Vector3.test.cpp>
#include <Window.test.cpp>
#include <WindowManager.test.cpp>

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
