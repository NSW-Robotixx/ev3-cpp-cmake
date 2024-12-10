#include <gtest/gtest.h>
#include <boost/unordered_map.hpp>

#include <portManager/port/Port.hpp>

#include <Fakesys.hpp>

TEST(Port, CreateFakeSys) {
    using namespace finder::physical::test;
    FakeSys fakesys;
    fakesys.init();
    ASSERT_TRUE(fakesys.isInitialized());
}

TEST(Port, Constructor)
{
    using namespace finder::physical::test;

    ASSERT_ANY_THROW(finder::physical::Port{"/sys/class/lego-sensor/sensor0"});
}

TEST(Port, getPortKey)
{
    using namespace finder::physical::test;

    boost::leaf::result<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
    ASSERT_TRUE(portPath);

    finder::physical::Port port{portPath.value()};

    port.overrideEnabled(false);
    ASSERT_FALSE(portPath);

    port.overrideEnabled(true);

    boost::leaf::result<char> portKey = port.getPortKey();
    ASSERT_TRUE(portKey);
    ASSERT_EQ(portKey.value(), '0');
}

TEST(Port, getPathFunctions)
{
    using namespace finder::physical::test;

    boost::leaf::result<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
    ASSERT_TRUE(portPath);

    finder::physical::Port port{portPath.value()};

    boost::unordered_map<std::string, std::function<boost::leaf::result<std::string>()>> paths = {
        {std::string{""}, [&port]() { return port.getBasePath(); }},
        {std::string{"/address"}, [&port]() { return port.getAddressPath(); }},
        {std::string{"/command"}, [&port]() { return port.getCommandPath(); }},
        {std::string{"/commands"}, [&port]() { return port.getCommandsPath(); }},
    };

    for (const auto& path : paths) {
        boost::leaf::result<std::string> pathValue = path.second();
        ASSERT_TRUE(pathValue);
        ASSERT_EQ(pathValue.value(), portPath.value() + path.first);

        port.overrideEnabled(false);

        pathValue = path.second();
        ASSERT_FALSE(pathValue);

        port.overrideEnabled(true);
    }
}


TEST(Port, setCommand)
{
    using namespace finder::physical::test;

    boost::leaf::result<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
    ASSERT_TRUE(portPath);

    finder::physical::Port port{portPath.value()};

    port.overrideEnabled(false);

    boost::leaf::result<void> status = port.setCommand("test-command");
    ASSERT_FALSE(status);
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
    using namespace finder::physical::test;

    boost::leaf::result<std::string> sensorPortPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
    boost::leaf::result<std::string> motorPortPath = FakeSys::getWorkingDir(EV3_PORT_OUTPUT_A);
    boost::leaf::result<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);

    ASSERT_TRUE(sensorPortPath);
    ASSERT_TRUE(motorPortPath);
    ASSERT_TRUE(portPath);

    finder::physical::Port sensorPort{sensorPortPath.value()};
    finder::physical::Port motorPort{motorPortPath.value()};
    finder::physical::Port unknownPort{portPath.value()};

    sensorPort.overrideEnabled(true);
    motorPort.overrideEnabled(true);
    unknownPort.overrideEnabled(true);
    
    boost::leaf::result<finder::physical::DeviceType> sensorType = sensorPort.getDeviceType();
    boost::leaf::result<finder::physical::DeviceType> motorType = motorPort.getDeviceType();
    boost::leaf::result<finder::physical::DeviceType> unknownType = unknownPort.getDeviceType();

    ASSERT_TRUE(sensorType);
    ASSERT_TRUE(motorType);
    ASSERT_TRUE(unknownType);

    ASSERT_EQ(sensorType.value(), finder::physical::DeviceType::SENSOR);
    ASSERT_EQ(motorType.value(), finder::physical::DeviceType::MOTOR);
    ASSERT_NE(unknownType.value(), finder::physical::DeviceType::UNKNOWN);
}

