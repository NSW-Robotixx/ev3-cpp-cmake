#include <gtest/gtest.h>

#include <physical/portManager/port/MotorPort.hpp>

TEST(MotorPort, DefaultConstructor)
{
    finder::physical::MotorPort motorPort;
    ASSERT_EQ(motorPort.getDeviceType(), finder::physical::DeviceType::MOTOR);
}

TEST(MotorPort, Constructor)
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");
    ASSERT_EQ(motorPort.getDeviceType(), finder::physical::DeviceType::MOTOR);
}

TEST(MotorPort, ConstructorWithPort)
{
    std::shared_ptr<finder::physical::Port> port = std::make_shared<finder::physical::Port>("/sys/class/tacho-motor/motor0");
    finder::physical::MotorPort motorPort(port);
    ASSERT_EQ(motorPort.getDeviceType(), finder::physical::DeviceType::MOTOR);
}

TEST(MotorPort, getCommandPath)
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");
    ASSERT_EQ(motorPort.getCommandPath(), "");
    motorPort.overrideEnabled(true);
    ASSERT_EQ(motorPort.getCommandPath(), "/sys/class/tacho-motor/motor0/command");
}

TEST(MotorPort, getDutyCyclePath)
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");
    ASSERT_EQ(motorPort.getDutyCyclePath(), "");
    motorPort.overrideEnabled(true);
    ASSERT_EQ(motorPort.getDutyCyclePath(), "/sys/class/tacho-motor/motor0/duty_cycle_sp");
}

TEST(MotorPort, getPositionSpPath)
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");
    ASSERT_EQ(motorPort.getPositionSpPath(), "");
    motorPort.overrideEnabled(true);
    ASSERT_EQ(motorPort.getPositionSpPath(), "/sys/class/tacho-motor/motor0/position_sp");
}

TEST(MotorPort, getSpeedPath)
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");
    ASSERT_EQ(motorPort.getSpeedPath(), "");
    motorPort.overrideEnabled(true);
    ASSERT_EQ(motorPort.getSpeedPath(), "/sys/class/tacho-motor/motor0/speed_sp");
}
TEST(MotorPort, getStatePath)
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");
    ASSERT_EQ(motorPort.getStatePath(), "");
    motorPort.overrideEnabled(true);
    ASSERT_EQ(motorPort.getStatePath(), "/sys/class/tacho-motor/motor0/state");
}

TEST(MotorPort, getStopActionPath)
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");
    ASSERT_EQ(motorPort.getStopActionPath(), "");
    motorPort.overrideEnabled(true);
    ASSERT_EQ(motorPort.getStopActionPath(), "/sys/class/tacho-motor/motor0/stop_action");
}

TEST(MotorPort, getCountPerRotationPath)
{
    finder::physical::MotorPort motorPort("/sys/class/tacho-motor/motor0");
    ASSERT_EQ(motorPort.getCountPerRotationPath(), "");
    motorPort.overrideEnabled(true);
    ASSERT_EQ(motorPort.getCountPerRotationPath(), "/sys/class/tacho-motor/motor0/count_per_rot");
}

TEST(MotorPort, filestreams)
{



    finder::physical::MotorPort motorPort("./test/motor0");

    motorPort.setSpeed(0);
    motorPort.setPositionSp(0);
    motorPort.setDutyCycle(0);
    motorPort.setPolarity(finder::physical::MotorPolarity::INVERSED);
    motorPort.setStopAction(finder::physical::MotorStopAction::HOLD);
    
    std::ifstream fs_speed_read("./test/motor0/speed_sp");
    std::ifstream fs_position_sp_read("./test/motor0/position_sp");
    std::ifstream fs_duty_cycle_read("./test/motor0/duty_cycle_sp");
    std::ifstream fs_state_read("./test/motor0/state");
    std::ifstream fs_polarity_read("./test/motor0/polarity");
    std::ifstream fs_stop_action_read("./test/motor0/stop_action");

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
    ASSERT_EQ(state, "0");
    ASSERT_EQ(polarity, "1");
    ASSERT_EQ(stop_action, "2");
    ASSERT_EQ(motorPort.getCountPerRotation(), 360);
}