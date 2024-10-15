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
    absl::Status status = port.setBasePath(fakesys.getWorkingDir() + "/lego-sensor/sensor0");
    ASSERT_TRUE(status.ok());
    port.overrideEnabled(false);
    // ASSERT_EQ(port.getPortKey(), 255);

    port.overrideEnabled(true);

    absl::StatusOr<char> portKey = port.getPortKey();
    ASSERT_TRUE(portKey.ok());
    ASSERT_EQ(portKey.value(), '0');
}

TEST(Port, getBasePath)
{
    finder::physical::Port port{"/sys/class/lego-sensor/sensor0"};
    absl::Status status = port.setBasePath("/sys/class/lego-sensor/sensor0");
    ASSERT_TRUE(status.ok());
    absl::StatusOr<std::string> basePath = port.getBasePath();
    ASSERT_TRUE(basePath.ok());
    EXPECT_EQ(basePath.value(), "");

    port.overrideEnabled(true);
    
    basePath = port.getBasePath();
    ASSERT_TRUE(basePath.ok());
    EXPECT_EQ(basePath.value(), "/sys/class/lego-sensor/sensor0");
}

TEST(Port, getAddressPath)
{
    finder::physical::Port port{"sys/class/lego-sensor/sensor0"};
    absl::Status status = port.setBasePath("/sys/class/lego-sensor/sensor0");
    ASSERT_TRUE(status.ok());

    absl::StatusOr<std::string> addressPath = port.getAddressPath();
    ASSERT_TRUE(addressPath.ok());
    EXPECT_EQ(addressPath.value(), "");
    port.overrideEnabled(true);

    addressPath = port.getAddressPath();
    ASSERT_TRUE(addressPath.ok());
    EXPECT_EQ(addressPath.value(), "/sys/class/lego-sensor/sensor0/address");
}

TEST(Port, getCommandPath)
{
    finder::physical::Port port{"sys/class/lego-sensor/sensor0"};
    absl::Status status = port.setBasePath("/sys/class/lego-sensor/sensor0");
    ASSERT_TRUE(status.ok());

    absl::StatusOr<std::string> commandPath = port.getCommandPath();
    ASSERT_TRUE(commandPath.ok());
    EXPECT_EQ(commandPath.value(), "");
    port.overrideEnabled(true);

    commandPath = port.getCommandPath();
    ASSERT_TRUE(commandPath.ok());
    EXPECT_EQ(commandPath.value(), "/sys/class/lego-sensor/sensor0/command");
}

TEST(Port, getCommandsPath)
{
    finder::physical::Port port{"sys/class/lego-sensor/sensor0"};
    absl::Status status = port.setBasePath("/sys/class/lego-sensor/sensor0");
    ASSERT_TRUE(status.ok());

    absl::StatusOr<std::string> commandsPath = port.getCommandsPath();
    ASSERT_TRUE(commandsPath.ok());
    EXPECT_EQ(commandsPath.value(), "");
    port.overrideEnabled(true);

    commandsPath = port.getCommandsPath();
    ASSERT_TRUE(commandsPath.ok());
    EXPECT_EQ(commandsPath.value(), "/sys/class/lego-sensor/sensor0/commands");
}

TEST(Port, getAddress)
{
    using namespace finder::physical::test;

    finder::physical::Port port{"sys/class/lego-sensor/sensor0"};
    absl::Status status = port.setBasePath(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
    ASSERT_TRUE(status.ok());

    absl::StatusOr<std::string> address = port.getAddress();
    ASSERT_TRUE(address.ok());
    EXPECT_EQ(address.value(), "ev3-ports:in1");
    port.overrideEnabled(false);

    address = port.getAddress();
    ASSERT_TRUE(address.ok());
    EXPECT_EQ(address.value(), "");
}

TEST(Port, setCommand)
{
    using namespace finder::physical::test;

    finder::physical::Port port{"sys/class/lego-sensor/sensor0"};
    absl::Status status = port.setBasePath(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
    ASSERT_TRUE(status.ok());
    port.overrideEnabled(false);
    status = port.setCommand("test-command");
    ASSERT_FALSE(status.ok());
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
    
    absl::StatusOr<finder::physical::DeviceType> sensorType = sensorPort.getDeviceType();
    absl::StatusOr<finder::physical::DeviceType> motorType = motorPort.getDeviceType();
    absl::StatusOr<finder::physical::DeviceType> unknownType = unknownPort.getDeviceType();

    ASSERT_TRUE(sensorType.ok());
    ASSERT_TRUE(motorType.ok());
    ASSERT_TRUE(unknownType.ok());

    ASSERT_EQ(sensorType.value(), finder::physical::DeviceType::SENSOR);
    ASSERT_EQ(motorType.value(), finder::physical::DeviceType::MOTOR);
    ASSERT_EQ(unknownType.value(), finder::physical::DeviceType::UNKNOWN);
}

