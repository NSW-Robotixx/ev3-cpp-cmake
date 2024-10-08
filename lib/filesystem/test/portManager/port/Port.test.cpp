#include <gtest/gtest.h>

#include <portManager/port/Port.hpp>

#include <Fakesys.hpp>

TEST(Port, CreateFakeSys) {
    using namespace finder::physical::test;
    FakeSys fakesys;
    fakesys.init();
    ASSERT_TRUE(fakesys.isInitialized());
}

TEST(Port, getPortKey)
{
    using namespace finder::physical::test;
    FakeSys fakesys;

    finder::physical::Port port{"/sys/class/lego-sensor/sensor0"};
    port.setBasePath(fakesys.getWorkingDir() + "/lego-sensor/sensor0");
    port.overrideEnabled(false);
    // ASSERT_EQ(port.getPortKey(), 255);

    port.overrideEnabled(true);

    ASSERT_EQ(port.getPortKey(), '0');
}

TEST(Port, getBasePath)
{
    finder::physical::Port port{"sys/class/lego-sensor/sensor0"};
    port.setBasePath("/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getBasePath(), "");
    port.overrideEnabled(true);
    EXPECT_EQ(port.getBasePath(), "/sys/class/lego-sensor/sensor0");
}

TEST(Port, getAddressPath)
{
    finder::physical::Port port{"sys/class/lego-sensor/sensor0"};
    port.setBasePath("/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getAddressPath(), "");
    port.overrideEnabled(true);
    EXPECT_EQ(port.getAddressPath(), "/sys/class/lego-sensor/sensor0/address");
}

TEST(Port, getCommandPath)
{
    finder::physical::Port port{"sys/class/lego-sensor/sensor0"};
    port.setBasePath("/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getCommandPath(), "");
    port.overrideEnabled(true);
    EXPECT_EQ(port.getCommandPath(), "/sys/class/lego-sensor/sensor0/command");
}

TEST(Port, getCommandsPath)
{
    finder::physical::Port port{"sys/class/lego-sensor/sensor0"};
    port.setBasePath("/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getCommandsPath(), "");
    port.overrideEnabled(true);
    EXPECT_EQ(port.getCommandsPath(), "/sys/class/lego-sensor/sensor0/commands");
}

TEST(Port, getAddress)
{
    using namespace finder::physical::test;

    finder::physical::Port port{"sys/class/lego-sensor/sensor0"};
    port.setBasePath(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
    EXPECT_EQ(port.getAddress(), "ev3-ports:in1");
    port.overrideEnabled(false);
    EXPECT_EQ(port.getAddress(), "");
}

TEST(Port, setCommand)
{
    using namespace finder::physical::test;

    finder::physical::Port port{"sys/class/lego-sensor/sensor0"};
    port.setBasePath(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
    EXPECT_EQ(port.setCommand("test"), true);
    port.overrideEnabled(false);
    EXPECT_EQ(port.setCommand("test"), false);
}

// TEST(Port, getCommands)
// {
//     finder::physical::Port port{"sys/class/lego-sensor/sensor0"};
//     port.setBasePath("./test/tacho-motor/sensor0");
//     std::vector<std::string> commands = port.getCommands();
//     for (std::string& command : commands) {
//         std::cout << command << std::endl;
//     }
//     ASSERT_EQ(commands.size(), 0);
//     port.overrideEnabled(false);
//     commands = port.getCommands();
//     ASSERT_EQ(commands.size(), 0);
// }

TEST(Port, getDeviceType)
{
    finder::physical::Port sensorPort{"/sys/class/lego-sensor/senso0"};
    finder::physical::Port motorPort{"sys/class/lego-motor/motor0"};
    finder::physical::Port unknownPort{"/sys/class/lego-unknown/unknown0"};

    sensorPort.overrideEnabled(true);
    motorPort.overrideEnabled(true);
    unknownPort.overrideEnabled(true);
    
    ASSERT_EQ(sensorPort.getDeviceType(), finder::physical::DeviceType::SENSOR);
    ASSERT_EQ(motorPort.getDeviceType(), finder::physical::DeviceType::MOTOR);
    ASSERT_EQ(unknownPort.getDeviceType(), finder::physical::DeviceType::UNKNOWN);
}

