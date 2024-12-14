#include <gtest/gtest.h>
#include <boost/unordered_map.hpp>

#include <portManager/port/SensorPort.hpp>
#include <Fakesys.hpp>
#include "../../EV3_conf.hpp"


TEST(SensorPort, CreateFakeSys) {
    using namespace finder::physical::test;
    FakeSys fakesys;
    fakesys.init();
    ASSERT_TRUE(fakesys.isInitialized());
}

TEST(SensorPort, Constructor)
{
    using namespace finder::physical::test;

    boost::leaf::result<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
    ASSERT_TRUE(portPath);

    finder::physical::SensorPort sensorPort(portPath.value());
    boost::leaf::result<finder::physical::DeviceType> deviceType = sensorPort.getDeviceType();
    ASSERT_TRUE(deviceType);
    ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::SENSOR);
}

// TEST(SensorPort, ConstructorWithPort)
// {
//     using namespace finder::physical::test;

//     boost::leaf::result<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
//     ASSERT_TRUE(portPath);

//     std::shared_ptr<finder::physical::Port> port = std::make_shared<finder::physical::Port>(portPath.value());

//     finder::physical::SensorPort sensorPort(port);

//     boost::leaf::result<finder::physical::DeviceType> deviceType = sensorPort.getDeviceType();
//     ASSERT_TRUE(deviceType);
//     ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::SENSOR);

//     boost::leaf::result<std::string> basePath = sensorPort.getBasePath();
//     ASSERT_TRUE(basePath);
//     ASSERT_EQ(basePath.value(), portPath.value());
// }

// TEST(SensorPort, setBasePath)
// {
//     using namespace finder::physical::test;

//     boost::leaf::result<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
//     ASSERT_TRUE(portPath);
    
//     finder::physical::SensorPort sensorPort{portPath.value()};

//     boost::leaf::result<std::string> newPortPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_2);
//     ASSERT_TRUE(newPortPath);

//     absl::Status status = sensorPort.setBasePath(newPortPath.value());
//     ASSERT_TRUE(status);

//     boost::leaf::result<finder::physical::DeviceType> deviceType = sensorPort.getDeviceType();
//     ASSERT_TRUE(deviceType);
//     ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::SENSOR);

//     boost::leaf::result<std::string> basePath = sensorPort.getBasePath();
//     ASSERT_TRUE(basePath);
//     ASSERT_EQ(basePath.value(), newPortPath.value());
// }

TEST(SensorPort, getPathFunctions)
{
    using namespace finder::physical::test;

    boost::leaf::result<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
    ASSERT_TRUE(portPath);

    finder::physical::SensorPort sensorPort(portPath.value());

    std::map<std::string, std::function<boost::leaf::result<std::string>()>> paths = {
        {std::string{"/command"}, [&sensorPort]() { return sensorPort.getCommandPath(); }},
        {std::string{"/commands"}, [&sensorPort]() { return sensorPort.getCommandsPath(); }},
        {std::string{"/address"}, [&sensorPort]() { return sensorPort.getAddressPath(); }},
        {std::string{"/mode"}, [&sensorPort]() { return sensorPort.getModePath(); }},
        {std::string{"/modes"}, [&sensorPort]() { return sensorPort.getModesPath(); }},
        {std::string{"/num_values"}, [&sensorPort]() { return sensorPort.getNumValuesPath(); }},
        {std::string{"/poll_ms"}, [&sensorPort]() { return sensorPort.getPollMsPath(); }},
        {std::string{"/value0"}, [&sensorPort]() { return sensorPort.getValuePath(0); }},
    };



    using namespace finder::physical::test;

    for (const auto &path : paths)
    {
        boost::leaf::result<std::string> pathValue = path.second();
        ASSERT_TRUE(pathValue);
        ASSERT_EQ(pathValue.value(), portPath.value() + path.first);

        spdlog::trace("Checking path for: " + path.first);
        sensorPort.overrideEnabled(false);

        pathValue = path.second();
        ASSERT_FALSE(pathValue);

        sensorPort.overrideEnabled(true);
    }
}

TEST(SensorPort, getValue)
{
    using namespace finder::physical::test;
    FakeSys::reinit();

    finder::physical::SensorPort sensorPort(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
    spdlog::trace("Overriding enabled = false");
    sensorPort.overrideEnabled(false);

    spdlog::trace("getting value0 from sensor");
    boost::leaf::result<int> value = sensorPort.getValue(0);
    ASSERT_FALSE(value);

    sensorPort.overrideEnabled(true);
    value = sensorPort.getValue(0);
    ASSERT_TRUE(value);
    ASSERT_EQ(value.value(), 0);

    value = sensorPort.getValue(100);
    ASSERT_FALSE(value);

    value = sensorPort.getValue(-1);
    ASSERT_FALSE(value);
}

TEST(SensorPort, getModes)
{
    using namespace finder::physical::test;

    boost::leaf::result<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
    ASSERT_TRUE(portPath);

    finder::physical::SensorPort sensorPort(portPath.value());
    std::vector<std::string> modes = sensorPort.getModes();
    sensorPort.overrideEnabled(false);
    ASSERT_EQ(modes.size(), 3);

    sensorPort.overrideEnabled(true);
    modes = sensorPort.getModes();
    ASSERT_EQ(modes.size(), 0);
}

TEST(SensorPort, filestreams)
{
    spdlog::set_level(spdlog::level::trace);

    using namespace finder::physical::test;

    FakeSys::reinit();

    boost::leaf::result<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
    ASSERT_TRUE(portPath) << "Failed to get port path";

    spdlog::trace("Manually opening port files");
    std::ofstream fs_value(portPath.value() + "/value0");
    std::ofstream fs_address(portPath.value() + "/address");
    std::ofstream fs_mode(portPath.value() + "/mode");
    std::ofstream fs_modes(portPath.value() + "/modes");
    std::ofstream fs_num_values(portPath.value() + "/num_values");
    std::ofstream fs_poll_ms(portPath.value() + "/poll_ms");
    std::ofstream fs_commmand(portPath.value() + "/command");
    std::ofstream fs_commands(portPath.value() + "/commands");

    spdlog::trace("Writing test values to port files");
    fs_value << "42";
    fs_address << "ev3-ports:in1";
    fs_mode << "";
    fs_modes << "EV3-IR EV3-Color EV3-Ultrasonic";
    fs_num_values << "1";
    fs_poll_ms << "100";
    fs_commands << "";
    
    spdlog::trace("Closing port files");
    fs_value.close();
    fs_address.close();
    fs_mode.close();
    fs_modes.close();
    fs_num_values.close();
    fs_poll_ms.close();
    fs_commmand.close();
    fs_commands.close();

    spdlog::trace("Creating sensor port");
    finder::physical::SensorPort sensorPort(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
    // sensorPort.setBasePath(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");

    spdlog::trace("Getting device type");
    boost::leaf::result<finder::physical::DeviceType> deviceType = sensorPort.getDeviceType();
    ASSERT_TRUE(deviceType) << "Failed to get device type";
    ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::SENSOR);

    boost::leaf::result<std::string> valuePath = sensorPort.getValuePath(0);
    ASSERT_TRUE(valuePath) << "Failed to get value path";
    ASSERT_EQ(valuePath.value(), FakeSys::getWorkingDir() + "/lego-sensor/sensor0/value0");
    
    boost::leaf::result<int> value = sensorPort.getValue(0);
    ASSERT_TRUE(value) << "Failed to get value";
    ASSERT_EQ(value.value(), 42);
    
    boost::leaf::result<std::string> address = sensorPort.getAddress();
    ASSERT_TRUE(address) << "Failed to get address";
    ASSERT_EQ(address.value(), "ev3-ports:in1");

    spdlog::trace("Setting mode for sensor");
    boost::leaf::result status = sensorPort.setMode("test-mode");
    ASSERT_TRUE(status) << "Failed to set mode";
    std::ifstream mode_file(FakeSys::getWorkingDir() + "/lego-sensor/sensor0/mode");
    std::string mode_str;
    mode_file >> mode_str;
    ASSERT_EQ(mode_str, "test-mode");

    spdlog::trace("Getting mode from sensor");
    std::vector<std::string> modes = sensorPort.getModes();
    ASSERT_EQ(modes.size(), 3);
    ASSERT_EQ(modes[0], "EV3-IR");
    ASSERT_EQ(modes[1], "EV3-Color");
    ASSERT_EQ(modes[2], "EV3-Ultrasonic");

    spdlog::trace("Getting num values from sensor");
    boost::leaf::result<int> numValues = sensorPort.getNumValues();
    ASSERT_TRUE(numValues) << "Failed to get num values";
    ASSERT_EQ(numValues.value(), 1);


    spdlog::trace("Getting num values from disabled sensor");
    sensorPort.overrideEnabled(false);
    numValues = sensorPort.getNumValues();
    ASSERT_FALSE(numValues) << "Successfully failed to get num values";

    sensorPort.overrideEnabled(true);
    spdlog::trace("Trying to get pollMs with enabled port");
    ASSERT_EQ(sensorPort.getPollMs(), 100);
    sensorPort.overrideEnabled(false);
    spdlog::trace("Trying to get pollMs with disabled port");
    ASSERT_EQ(sensorPort.getPollMs(), -1);
    sensorPort.overrideEnabled(true);

    // remove temp files
    spdlog::debug("Removing temporary files");
    ASSERT_NO_FATAL_FAILURE(std::filesystem::remove_all(FakeSys::getWorkingDir() + ""));
}