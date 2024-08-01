#include <gtest/gtest.h>
#include <initFiles.test.cpp>
// #include <Bitmaps.test.cpp>
#include <ButtonNotifier.test.cpp>
#include <LocationEngine.test.cpp>
#include <MovementEngine.test.cpp>
#include <RobotMovement.test.cpp>
#include <Screen.test.cpp>
#include <ServerManager.test.cpp>
// #include <UserInterface.test.cpp>
// #include <WebComponentBase.test.cpp>
// #include <webServer.test.cpp>
#include <Window.test.cpp>
#include <WindowManager.test.cpp>
#include <ObstacleManager.test.cpp>
#include <SmoothPath.test.cpp>
#include <MovementParser.test.cpp>
// #include <GearboxEngine.test.cpp>

// #include <filesystem/include/test_EV3_filesystem.cpp>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  
  EXPECT_EQ(7 * 6, 42);
}
