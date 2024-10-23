#include <gtest/gtest.h>

#include <portManager/port/MotorPort.hpp>

#include <Fakesys.hpp>

#include <absl/container/flat_hash_map.h>
#include <functional>

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

    absl::StatusOr<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_OUTPUT_A);
    ASSERT_TRUE(portPath.ok());

    std::shared_ptr<finder::physical::Port> port = std::make_shared<finder::physical::Port>(portPath.value());
    finder::physical::MotorPort motorPort(port);

    absl::StatusOr<finder::physical::DeviceType> deviceType = motorPort.getDeviceType();
    ASSERT_TRUE(deviceType.ok());
    ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::MOTOR);
}

TEST(MotorPort, getPathFunctions)
{   
    using namespace finder::physical::test;

    absl::StatusOr<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_OUTPUT_A);
    ASSERT_TRUE(portPath.ok());

    finder::physical::MotorPort motorPort(portPath.value());

    absl::flat_hash_map<std::string, std::function<absl::StatusOr<std::string>()>> paths = {
        {std::string{"/command"}, [&motorPort]() { return motorPort.getCommandPath(); }},
        {std::string{"/commands"}, [&motorPort]() { return motorPort.getCommandsPath(); }},
        {std::string{"/duty_cycle"}, [&motorPort]() { return motorPort.getDutyCyclePath(); }},
        {std::string{"/position"}, [&motorPort]() { return motorPort.getPositionPath(); }},
        {std::string{"/position_sp"}, [&motorPort]() { return motorPort.getPositionSpPath(); }},
        {std::string{"/speed"}, [&motorPort]() { return motorPort.getSpeedPath(); }},
        {std::string{"/speed_sp"}, [&motorPort]() { return motorPort.getSpeedSpPath(); }},
        {std::string{"/state"}, [&motorPort]() { return motorPort.getStatePath(); }},
        {std::string{"/stop_action"}, [&motorPort]() { return motorPort.getStopActionPath(); }},
        {std::string{"/count_per_rot"}, [&motorPort]() { return motorPort.getCountPerRotationPath(); }},
    };



    using namespace finder::physical::test;

    for (const auto &path : paths)
    {
        absl::StatusOr<std::string> pathValue = path.second();
        ASSERT_TRUE(pathValue.ok());
        ASSERT_EQ(pathValue.value(), portPath.value() + path.first);

        motorPort.overrideEnabled(false);

        pathValue = path.second();
        ASSERT_FALSE(pathValue.ok());

        motorPort.overrideEnabled(true);
    }
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