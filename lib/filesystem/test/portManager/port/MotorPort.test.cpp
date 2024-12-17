#include <gtest/gtest.h>
#include <boost/unordered_map.hpp>

#include <portManager/port/MotorPort.hpp>

#include <Fakesys.hpp>

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

    boost::leaf::result<finder::physical::DeviceType> deviceType = motorPort.getDeviceType();
    ASSERT_TRUE(deviceType);
    ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::MOTOR);
}

TEST(MotorPort, ConstructorWithPort)
{
    using namespace finder::physical::test;

    boost::leaf::result<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_OUTPUT_A);
    ASSERT_TRUE(portPath);

    std::shared_ptr<finder::physical::Port> port = std::make_shared<finder::physical::Port>(portPath.value());
    finder::physical::MotorPort motorPort(port);

    boost::leaf::result<finder::physical::DeviceType> deviceType = motorPort.getDeviceType();
    ASSERT_TRUE(deviceType);
    ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::MOTOR);
}

TEST(MotorPort, getPathFunctions)
{   
    using namespace finder::physical::test;

    boost::leaf::result<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_OUTPUT_A);
    ASSERT_TRUE(portPath);

    finder::physical::MotorPort motorPort(portPath.value());

    boost::unordered_map<std::string, std::function<boost::leaf::result<std::string>()>> paths = {
        {std::string{"/command"}, [&motorPort]() { return motorPort.getCommandPath(); }},
        {std::string{"/commands"}, [&motorPort]() { return motorPort.getCommandsPath(); }},
        {std::string{"/duty_cycle_sp"}, [&motorPort]() { return motorPort.getDutyCyclePath(); }},
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
        boost::leaf::result<std::string> pathValue = path.second();
        ASSERT_TRUE(pathValue);
        ASSERT_EQ(pathValue.value(), portPath.value() + path.first);

        motorPort.overrideEnabled(false);

        pathValue = path.second();
        ASSERT_FALSE(pathValue);

        motorPort.overrideEnabled(true);
    }
}

TEST(MotorPort, filestreams)
{
    using namespace finder::physical::test;

    finder::physical::MotorPort motorPort(FakeSys::getWorkingDir() + "/tacho-motor/motor0");

    motorPort.setSpeed(0);
    EXPECT_TRUE(motorPort.setPositionSp(0));
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
TEST(MotorPort, GetSpeed)
{
    using namespace finder::physical::test;

    finder::physical::MotorPort motorPort(FakeSys::getWorkingDir() + "/tacho-motor/motor0");

    motorPort.setSpeed(100);
    int speed = motorPort.getSpeed();
    ASSERT_EQ(speed, 0);
}

TEST(MotorPort, GetPosition)
{
    using namespace finder::physical::test;

    finder::physical::MotorPort motorPort(FakeSys::getWorkingDir() + "/tacho-motor/motor0");

    motorPort.setPositionSp(200);
    int position = motorPort.getPosition();
    ASSERT_EQ(position, 92);
}

TEST(MotorPort, GetCountPerRotation)
{
    using namespace finder::physical::test;

    finder::physical::MotorPort motorPort(FakeSys::getWorkingDir() + "/tacho-motor/motor0");

    int countPerRotation = motorPort.getCountPerRotation();
    ASSERT_EQ(countPerRotation, 360);
}

TEST(MotorPort, GetMaxSpeed)
{
    using namespace finder::physical::test;

    finder::physical::MotorPort motorPort(FakeSys::getWorkingDir() + "/tacho-motor/motor0");

    int maxSpeed = motorPort.getMaxSpeed();
    ASSERT_EQ(maxSpeed, 1050); // Assuming 1050 is the max speed set in the fake system
}

TEST(MotorPort, GetState)
{
    using namespace finder::physical::test;

    finder::physical::MotorPort motorPort(FakeSys::getWorkingDir() + "/tacho-motor/motor0");

    motorPort.setCommand(finder::physical::MotorCommand::RUN_FOREVER);
    std::vector<finder::physical::MotorState> states = motorPort.getState();
    ASSERT_TRUE(std::find(states.begin(), states.end(), finder::physical::MotorState::RUNNING) != states.end());
}
