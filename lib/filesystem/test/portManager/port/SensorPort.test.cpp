#include <gtest/gtest.h>
#include <portManager/port/SensorPort.hpp>
#include <Fakesys.hpp>

TEST(SensorPort, CreateFakeSys) {
    using namespace finder::physical::test;
    FakeSys fakesys;
    fakesys.init();
    ASSERT_TRUE(fakesys.isInitialized());
}

// TEST(SensorPort, Constructor)
// {
//     using namespace finder::physical::test;

//     finder::physical::SensorPort sensorPort(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
//     absl::StatusOr<finder::physical::DeviceType> deviceType = sensorPort.getDeviceType();
//     ASSERT_TRUE(deviceType.ok());
//     ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::SENSOR);

//     ASSERT_ANY_THROW(finder::physical::SensorPort sensorPort(""));
// }

// TEST(SensorPort, ConstructorWithPort)
// {
//     using namespace finder::physical::test;

//     std::shared_ptr<finder::physical::Port> port = std::make_shared<finder::physical::Port>(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");

//     finder::physical::SensorPort sensorPort(port);

//     absl::StatusOr<finder::physical::DeviceType> deviceType = sensorPort.getDeviceType();
//     ASSERT_TRUE(deviceType.ok());
//     ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::SENSOR);

//     absl::StatusOr<std::string> basePath = sensorPort.getBasePath();
//     ASSERT_TRUE(basePath.ok());
//     ASSERT_EQ(basePath.value(), FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
// }

TEST(SensorPort, setBasePath)
{
    using namespace finder::physical::test;

    
    finder::physical::SensorPort sensorPort{"/sys/class/lego-sensor/sensor0"};

    absl::Status status = sensorPort.setBasePath(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
    ASSERT_TRUE(status.ok());

    absl::StatusOr<finder::physical::DeviceType> deviceType = sensorPort.getDeviceType();
    ASSERT_TRUE(deviceType.ok());
    ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::SENSOR);

    absl::StatusOr<std::string> basePath = sensorPort.getBasePath();
    ASSERT_TRUE(basePath.ok());
    ASSERT_EQ(basePath.value(), FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
}

TEST(SensorPort, getValuePath)
{
    using namespace finder::physical::test;

    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");

    absl::StatusOr<std::string> valuePath = sensorPort.getValuePath(0);
    ASSERT_FALSE(valuePath.ok());

    sensorPort.overrideEnabled(true);

    valuePath = sensorPort.getValuePath(0);
    ASSERT_TRUE(valuePath.ok());
    ASSERT_EQ(valuePath.value(), "/sys/class/lego-sensor/sensor0/value0");
}

TEST(SensorPort, getModePath)
{
    using namespace finder::physical::test;

    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");

    absl::StatusOr<std::string> modePath = sensorPort.getModePath();
    ASSERT_FALSE(modePath.ok());

    sensorPort.overrideEnabled(true);
    modePath = sensorPort.getModePath();
    ASSERT_TRUE(modePath.ok());
    ASSERT_EQ(modePath.value(), "/sys/class/lego-sensor/sensor0/mode");
}

TEST(SensorPort, getModesPath)
{
    using namespace finder::physical::test;

    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");

    absl::StatusOr<std::string> modesPath = sensorPort.getModesPath();
    ASSERT_FALSE(modesPath.ok());

    sensorPort.overrideEnabled(true);
    modesPath = sensorPort.getModesPath();
    ASSERT_TRUE(modesPath.ok());
    ASSERT_EQ(modesPath.value(), "/sys/class/lego-sensor/sensor0/modes");
}

TEST(SensorPort, getNumValuesPath)
{
    using namespace finder::physical::test;

    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");

    absl::StatusOr<std::string> numValuesPath = sensorPort.getNumValuesPath();
    ASSERT_FALSE(numValuesPath.ok());

    sensorPort.overrideEnabled(true);
    numValuesPath = sensorPort.getNumValuesPath();
    ASSERT_TRUE(numValuesPath.ok());
    ASSERT_EQ(numValuesPath.value(), "/sys/class/lego-sensor/sensor0/num_values");
}

TEST(SensorPort, getPollMsPath)
{
    using namespace finder::physical::test;

    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");

    absl::StatusOr<std::string> pollMsPath = sensorPort.getPollMsPath();
    ASSERT_FALSE(pollMsPath.ok());

    sensorPort.overrideEnabled(true);
    pollMsPath = sensorPort.getPollMsPath();
    ASSERT_TRUE(pollMsPath.ok());
    ASSERT_EQ(pollMsPath.value(), "/sys/class/lego-sensor/sensor0/poll_ms");
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

    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");
    std::vector<std::string> modes = sensorPort.getModes();
    ASSERT_EQ(modes.size(), 0);
    sensorPort.overrideEnabled(true);
    modes = sensorPort.getModes();
    ASSERT_EQ(modes.size(), 0);
}

TEST(SensorPort, filestreams)
{
    using namespace finder::physical::test;

    std::filesystem::create_directories(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
    std::ofstream fs_value(FakeSys::getWorkingDir() + "/lego-sensor/sensor0/value0");
    std::ofstream fs_address(FakeSys::getWorkingDir() + "/lego-sensor/sensor0/address");
    std::ofstream fs_mode(FakeSys::getWorkingDir() + "/lego-sensor/sensor0/mode");
    std::ofstream fs_modes(FakeSys::getWorkingDir() + "/lego-sensor/sensor0/modes");
    std::ofstream fs_num_values(FakeSys::getWorkingDir() + "/lego-sensor/sensor0/num_values");
    std::ofstream fs_poll_ms(FakeSys::getWorkingDir() + "/lego-sensor/sensor0/poll_ms");
    std::ofstream fs_commmand(FakeSys::getWorkingDir() + "/lego-sensor/sensor0/command");
    std::ofstream fs_commands(FakeSys::getWorkingDir() + "/lego-sensor/sensor0/commands");


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
    ASSERT_TRUE(deviceType.ok());
    ASSERT_EQ(deviceType.value(), finder::physical::DeviceType::SENSOR);

    absl::StatusOr<std::string> valuePath = sensorPort.getValuePath(0);
    ASSERT_TRUE(valuePath.ok());
    ASSERT_EQ(valuePath.value(), FakeSys::getWorkingDir() + "/lego-sensor/sensor0/value0");
    
    absl::StatusOr<int> value = sensorPort.getValue(0);
    ASSERT_TRUE(value.ok());
    ASSERT_EQ(value.value(), 42);
    
    absl::StatusOr<std::string> address = sensorPort.getAddress();
    ASSERT_TRUE(address.ok());
    ASSERT_EQ(address.value(), "ev3-ports:in1");

    absl::Status status = sensorPort.setMode("test-mode");
    ASSERT_TRUE(status.ok());
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
    ASSERT_TRUE(numValues.ok());
    ASSERT_EQ(numValues.value(), 1);

    sensorPort.overrideEnabled(false);
    numValues = sensorPort.getNumValues();
    ASSERT_FALSE(numValues.ok());

    sensorPort.overrideEnabled(true);
    ASSERT_EQ(sensorPort.getPollMs(), 100);
    sensorPort.overrideEnabled(false);
    ASSERT_EQ(sensorPort.getPollMs(), -1);
    sensorPort.overrideEnabled(true);

    // remove temp files
    std::filesystem::remove_all(FakeSys::getWorkingDir() + "");
}