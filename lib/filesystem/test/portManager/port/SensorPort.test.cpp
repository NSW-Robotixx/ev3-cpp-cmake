#include <gtest/gtest.h>
#include <absl/container/flat_hash_map.h>

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

    absl::StatusOr<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
    ASSERT_TRUE(portPath.ok());

    finder::physical::SensorPort sensorPort(portPath.value());
    absl::StatusOr<finder::physical::DeviceType> deviceType = sensorPort.getDeviceType();
    ASSERT_TRUE(deviceType.ok());
    ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::SENSOR);

    if constexpr (EV3_THROW_ON_ERROR) {ASSERT_ANY_THROW(finder::physical::SensorPort sensorPort("")); }
}

// TEST(SensorPort, ConstructorWithPort)
// {
//     using namespace finder::physical::test;

//     absl::StatusOr<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
//     ASSERT_TRUE(portPath.ok());

//     std::shared_ptr<finder::physical::Port> port = std::make_shared<finder::physical::Port>(portPath.value());

//     finder::physical::SensorPort sensorPort(port);

//     absl::StatusOr<finder::physical::DeviceType> deviceType = sensorPort.getDeviceType();
//     ASSERT_TRUE(deviceType.ok());
//     ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::SENSOR);

//     absl::StatusOr<std::string> basePath = sensorPort.getBasePath();
//     ASSERT_TRUE(basePath.ok());
//     ASSERT_EQ(basePath.value(), portPath.value());
// }

// TEST(SensorPort, setBasePath)
// {
//     using namespace finder::physical::test;

//     absl::StatusOr<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
//     ASSERT_TRUE(portPath.ok());
    
//     finder::physical::SensorPort sensorPort{portPath.value()};

//     absl::StatusOr<std::string> newPortPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_2);
//     ASSERT_TRUE(newPortPath.ok());

//     absl::Status status = sensorPort.setBasePath(newPortPath.value());
//     ASSERT_TRUE(status.ok());

//     absl::StatusOr<finder::physical::DeviceType> deviceType = sensorPort.getDeviceType();
//     ASSERT_TRUE(deviceType.ok());
//     ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::SENSOR);

//     absl::StatusOr<std::string> basePath = sensorPort.getBasePath();
//     ASSERT_TRUE(basePath.ok());
//     ASSERT_EQ(basePath.value(), newPortPath.value());
// }

TEST(SensorPort, getPathFunctions)
{
    using namespace finder::physical::test;

    absl::StatusOr<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
    ASSERT_TRUE(portPath.ok());

    finder::physical::SensorPort sensorPort(portPath.value());

    absl::flat_hash_map<std::string, std::function<absl::StatusOr<std::string>()>> paths = {
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
        absl::StatusOr<std::string> pathValue = path.second();
        ASSERT_TRUE(pathValue.ok());
        ASSERT_EQ(pathValue.value(), portPath.value() + path.first);

        sensorPort.overrideEnabled(false);

        pathValue = path.second();
        ASSERT_FALSE(pathValue.ok());

        sensorPort.overrideEnabled(true);
    }
}

TEST(SensorPort, getValue)
{
    using namespace finder::physical::test;
    FakeSys::reinit();

    finder::physical::SensorPort sensorPort(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
    sensorPort.overrideEnabled(false);

    absl::StatusOr<int> value = sensorPort.getValue(0);
    ASSERT_FALSE(value.ok());

    sensorPort.overrideEnabled(true);
    value = sensorPort.getValue(0);
    ASSERT_TRUE(value.ok());
    ASSERT_EQ(value.value(), 0);

    value = sensorPort.getValue(100);
    ASSERT_FALSE(value.ok());

    value = sensorPort.getValue(-1);
    ASSERT_FALSE(value.ok());
}

TEST(SensorPort, getModes)
{
    using namespace finder::physical::test;

    absl::StatusOr<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
    ASSERT_TRUE(portPath.ok());

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
    using namespace finder::physical::test;

    FakeSys::reinit();

    absl::StatusOr<std::string> portPath = FakeSys::getWorkingDir(EV3_PORT_INPUT_1);
    ASSERT_TRUE(portPath.ok()) << "Failed to get port path";

    std::ofstream fs_value(portPath.value() + "/value0");
    std::ofstream fs_address(portPath.value() + "/address");
    std::ofstream fs_mode(portPath.value() + "/mode");
    std::ofstream fs_modes(portPath.value() + "/modes");
    std::ofstream fs_num_values(portPath.value() + "/num_values");
    std::ofstream fs_poll_ms(portPath.value() + "/poll_ms");
    std::ofstream fs_commmand(portPath.value() + "/command");
    std::ofstream fs_commands(portPath.value() + "/commands");

    fs_value << "42";
    fs_address << "ev3-ports:in1";
    fs_mode << "";
    fs_modes << "EV3-IR EV3-Color EV3-Ultrasonic";
    fs_num_values << "1";
    fs_poll_ms << "100";
    fs_commands << "";
    
    fs_value.close();
    fs_address.close();
    fs_mode.close();
    fs_modes.close();
    fs_num_values.close();
    fs_poll_ms.close();
    fs_commmand.close();
    fs_commands.close();

    finder::physical::SensorPort sensorPort(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
    // sensorPort.setBasePath(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
    absl::StatusOr<finder::physical::DeviceType> deviceType = sensorPort.getDeviceType();
    ASSERT_TRUE(deviceType.ok()) << "Failed to get device type";
    ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::SENSOR);

    absl::StatusOr<std::string> valuePath = sensorPort.getValuePath(0);
    ASSERT_TRUE(valuePath.ok()) << "Failed to get value path";
    ASSERT_EQ(valuePath.value(), FakeSys::getWorkingDir() + "/lego-sensor/sensor0/value0");
    
    absl::StatusOr<int> value = sensorPort.getValue(0);
    ASSERT_TRUE(value.ok()) << "Failed to get value";
    ASSERT_EQ(value.value(), 42);
    
    absl::StatusOr<std::string> address = sensorPort.getAddress();
    ASSERT_TRUE(address.ok()) << "Failed to get address";
    ASSERT_EQ(address.value(), "ev3-ports:in1");

    absl::Status status = sensorPort.setMode("test-mode");
    ASSERT_TRUE(status.ok()) << "Failed to set mode";
    std::ifstream mode_file(FakeSys::getWorkingDir() + "/lego-sensor/sensor0/mode");
    std::string mode_str;
    mode_file >> mode_str;
    ASSERT_EQ(mode_str, "test-mode");

    std::vector<std::string> modes = sensorPort.getModes();
    ASSERT_EQ(modes.size(), 3);
    ASSERT_EQ(modes[0], "EV3-IR");
    ASSERT_EQ(modes[1], "EV3-Color");
    ASSERT_EQ(modes[2], "EV3-Ultrasonic");

    absl::StatusOr<int> numValues = sensorPort.getNumValues();
    ASSERT_TRUE(numValues.ok()) << "Failed to get num values";
    ASSERT_EQ(numValues.value(), 1);

    sensorPort.overrideEnabled(false);
    numValues = sensorPort.getNumValues();
    ASSERT_FALSE(numValues.ok()) << "Failed to get num values";

    sensorPort.overrideEnabled(true);
    ASSERT_EQ(sensorPort.getPollMs(), 100);
    sensorPort.overrideEnabled(false);
    ASSERT_EQ(sensorPort.getPollMs(), -1);
    sensorPort.overrideEnabled(true);

    // remove temp files
    std::filesystem::remove_all(FakeSys::getWorkingDir() + "");
}