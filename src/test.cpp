#include <gtest/gtest.h>
#include <initFiles.test.cpp>
// #include <Bitmaps.test.cpp>
#include <ButtonNotifier.test.cpp>
#include <DeviceManager.test.cpp>
#include <LocationEngine.test.cpp>
#include <Logger.test.cpp>
#include <MotorManager.test.cpp>
#include <MotorPort.test.cpp>
#include <MovementEngine.test.cpp>
#include <Port.test.cpp>
#include <PortManager.test.cpp>
#include <RobotMovement.test.cpp>
#include <Screen.test.cpp>
#include <SensorManager.test.cpp>
#include <SensorPort.test.cpp>
#include <ServerManager.test.cpp>
// #include <UserInterface.test.cpp>
#include <Vector2.test.cpp>
// #include <Vector3.test.cpp>
// #include <WebComponentBase.test.cpp>
// #include <webServer.test.cpp>
#include <Window.test.cpp>
#include <WindowManager.test.cpp>
#include <Line.test.cpp>
#include <AStar.test.cpp>
#include <ObstacleManager.test.cpp>
#include <SmoothPath.test.cpp>
#include <MovementParser.test.cpp>
// #include <GearboxEngine.test.cpp>
// #include <cleanupFiles.test.cpp>
#include <GraphicalInterface.test.cpp>

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
