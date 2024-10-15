#include <gtest/gtest.h>

#include <portManager/port/MotorPort.hpp>

#include <Fakesys.hpp>

TEST(MotorPort, CreateFakeSys) {
    using namespace finder::physical::test;
    FakeSys fakesys;
    fakesys.init();
    ASSERT_TRUE(fakesys.isInitialized());

}

TEST(MotorPort, Constructor)
{
    using namespace finder::physical::test;

    finder::physical::MotorPort motorPort(FakeSys::getWorkingDir() + "/tacho-motor/motor0");

    absl::StatusOr<finder::physical::DeviceType> deviceType = motorPort.getDeviceType();
    ASSERT_TRUE(deviceType.ok());
    ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::MOTOR);
}

TEST(MotorPort, ConstructorWithPort)
{
    using namespace finder::physical::test;

    std::shared_ptr<finder::physical::Port> port = std::make_shared<finder::physical::Port>(FakeSys::getWorkingDir() + "/tacho-motor/motor0");
    finder::physical::MotorPort motorPort(port);

    absl::StatusOr<finder::physical::DeviceType> deviceType = motorPort.getDeviceType();
    ASSERT_TRUE(deviceType.ok());
    ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::MOTOR);
}

TEST(MotorPort, getCommandPath)
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");

    absl::StatusOr<std::string> commandPath = motorPort.getCommandPath();
    ASSERT_FALSE(commandPath.ok());

    motorPort.overrideEnabled(true);
    commandPath = motorPort.getCommandPath();
    ASSERT_TRUE(commandPath.ok());
    ASSERT_EQ(commandPath.value(), "/sys/class/tacho-motor/motor0/command");
}

TEST(MotorPort, getDutyCyclePath)
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");

    absl::StatusOr<std::string> dutyCyclePath = motorPort.getDutyCyclePath();
    ASSERT_FALSE(dutyCyclePath.ok());

    motorPort.overrideEnabled(true);
    dutyCyclePath = motorPort.getDutyCyclePath();
    ASSERT_TRUE(dutyCyclePath.ok());
    ASSERT_EQ(dutyCyclePath.value(), "/sys/class/tacho-motor/motor0/duty_cycle_sp");
}

TEST(MotorPort, getPositionPath) 
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");
    
    absl::StatusOr<std::string> positionPath = motorPort.getPositionPath();
    ASSERT_FALSE(positionPath.ok());

    motorPort.overrideEnabled(true);
    positionPath = motorPort.getPositionPath();
    ASSERT_TRUE(positionPath.ok());
    ASSERT_EQ(positionPath.value(), "/sys/class/tacho-motor/motor0/position");
}

TEST(MotorPort, getPositionSpPath)
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");
    
    absl::StatusOr<std::string> positionSpPath = motorPort.getPositionSpPath();
    ASSERT_FALSE(positionSpPath.ok());

    motorPort.overrideEnabled(true);
    positionSpPath = motorPort.getPositionSpPath();
    ASSERT_TRUE(positionSpPath.ok());
    ASSERT_EQ(positionSpPath.value(), "/sys/class/tacho-motor/motor0/position_sp");
}

TEST(MotorPort, getSpeedPath) 
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");
    
    absl::StatusOr<std::string> speedPath = motorPort.getSpeedPath();
    ASSERT_FALSE(speedPath.ok());

    motorPort.overrideEnabled(true);
    speedPath = motorPort.getSpeedPath();
    ASSERT_TRUE(speedPath.ok());
    ASSERT_EQ(speedPath.value(), "/sys/class/tacho-motor/motor0/speed");
}

TEST(MotorPort, getSpeedSpPath)
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");
    
    absl::StatusOr<std::string> speedSpPath = motorPort.getSpeedSpPath();
    ASSERT_FALSE(speedSpPath.ok());
    
    motorPort.overrideEnabled(true);
    speedSpPath = motorPort.getSpeedSpPath();
    ASSERT_TRUE(speedSpPath.ok());
    ASSERT_EQ(speedSpPath.value(), "/sys/class/tacho-motor/motor0/speed_sp");
}
TEST(MotorPort, getStatePath)
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");
    
    absl::StatusOr<std::string> statePath = motorPort.getStatePath();
    ASSERT_FALSE(statePath.ok());

    motorPort.overrideEnabled(true);
    statePath = motorPort.getStatePath();
    ASSERT_TRUE(statePath.ok());
    ASSERT_EQ(statePath.value(), "/sys/class/tacho-motor/motor0/state");
}

TEST(MotorPort, getStopActionPath)
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");
    
    absl::StatusOr<std::string> stopActionPath = motorPort.getStopActionPath();
    ASSERT_FALSE(stopActionPath.ok());

    motorPort.overrideEnabled(true);
    stopActionPath = motorPort.getStopActionPath();
    ASSERT_TRUE(stopActionPath.ok());
    ASSERT_EQ(stopActionPath.value(), "/sys/class/tacho-motor/motor0/stop_action");
}

TEST(MotorPort, getCountPerRotationPath)
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");
    
    absl::StatusOr<std::string> countPerRotationPath = motorPort.getCountPerRotationPath();
    ASSERT_FALSE(countPerRotationPath.ok());

    motorPort.overrideEnabled(true);
    countPerRotationPath = motorPort.getCountPerRotationPath();
    ASSERT_TRUE(countPerRotationPath.ok());
    ASSERT_EQ(countPerRotationPath.value(), "/sys/class/tacho-motor/motor0/count_per_rot");
}

TEST(MotorPort, filestreams)
{
    using namespace finder::physical::test;

    finder::physical::MotorPort motorPort(FakeSys::getWorkingDir() + "/tacho-motor/motor0");

    motorPort.setSpeed(0);
    motorPort.setPositionSp(0);
    motorPort.setDutyCycle(0);
    motorPort.setPolarity(finder::physical::MotorPolarity::INVERSED);
    motorPort.setStopAction(finder::physical::MotorStopAction::HOLD);
    
    std::ifstream fs_speed_read(FakeSys::getWorkingDir() + "/tacho-motor/motor0/speed_sp");
    std::ifstream fs_position_sp_read(FakeSys::getWorkingDir() + "/tacho-motor/motor0/position_sp");
    std::ifstream fs_duty_cycle_read(FakeSys::getWorkingDir() + "/tacho-motor/motor0/duty_cycle_sp");
    std::ifstream fs_state_read(FakeSys::getWorkingDir() + "/tacho-motor/motor0/state");
    std::ifstream fs_polarity_read(FakeSys::getWorkingDir() + "/tacho-motor/motor0/polarity");
    std::ifstream fs_stop_action_read(FakeSys::getWorkingDir() + "/tacho-motor/motor0/stop_action");

    ASSERT_TRUE(fs_speed_read.is_open());
    ASSERT_TRUE(fs_position_sp_read.is_open());
    ASSERT_TRUE(fs_duty_cycle_read.is_open());
    ASSERT_TRUE(fs_state_read.is_open());
    ASSERT_TRUE(fs_polarity_read.is_open());
    ASSERT_TRUE(fs_stop_action_read.is_open());

    std::string speed;
    std::string position_sp;
    std::string duty_cycle;
    std::string state;
    std::string polarity;
    std::string stop_action;

    fs_speed_read >> speed;
    fs_position_sp_read >> position_sp;
    fs_duty_cycle_read >> duty_cycle;
    fs_state_read >> state;
    fs_polarity_read >> polarity;
    fs_stop_action_read >> stop_action;

    ASSERT_EQ(speed, "0");
    ASSERT_EQ(position_sp, "0");
    ASSERT_EQ(duty_cycle, "0");
    ASSERT_EQ(state, "running");
    ASSERT_EQ(polarity, "inversed");
    ASSERT_EQ(stop_action, "hold");
    ASSERT_EQ(motorPort.getCountPerRotation(), 360);
}