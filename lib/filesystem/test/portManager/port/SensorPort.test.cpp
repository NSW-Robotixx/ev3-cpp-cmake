#include <gtest/gtest.h>
#include <portManager/port/SensorPort.hpp>
#include <Fakesys.hpp>

TEST(SensorPort, CreateFakeSys) {
    using namespace finder::physical::test;
    FakeSys fakesys;
    fakesys.init();
    ASSERT_TRUE(fakesys.isInitialized());
}

TEST(SensorPort, Constructor)
{
    using namespace finder::physical::test;

    finder::physical::SensorPort sensorPort(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
    ASSERT_EQ(sensorPort.getDeviceType(), finder::physical::DeviceType::SENSOR);

    ASSERT_ANY_THROW(finder::physical::SensorPort sensorPort(""));
}

TEST(SensorPort, ConstructorWithPort)
{
    using namespace finder::physical::test;

    std::shared_ptr<finder::physical::Port> port = std::make_shared<finder::physical::Port>(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");

    finder::physical::SensorPort sensorPort(port);

    ASSERT_EQ(sensorPort.getDeviceType(), finder::physical::DeviceType::SENSOR);
    ASSERT_EQ(sensorPort.getBasePath(), FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
}

TEST(SensorPort, setBasePath)
{
    using namespace finder::physical::test;

    
    finder::physical::SensorPort sensorPort{"/sys/class/lego-sensor/sensor0"};
    sensorPort.setBasePath(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
    ASSERT_EQ(sensorPort.getDeviceType(), finder::physical::DeviceType::SENSOR);
    ASSERT_EQ(sensorPort.getBasePath(), FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
}

TEST(SensorPort, getValuePath)
{
    using namespace finder::physical::test;

    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");
    ASSERT_EQ(sensorPort.getValuePath(0), "");
    sensorPort.overrideEnabled(true);
    ASSERT_EQ(sensorPort.getValuePath(0), "/sys/class/lego-sensor/sensor0/value0");
}

TEST(SensorPort, getModePath)
{
    using namespace finder::physical::test;

    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");
    ASSERT_EQ(sensorPort.getModePath(), "");
    sensorPort.overrideEnabled(true);
    ASSERT_EQ(sensorPort.getModePath(), "/sys/class/lego-sensor/sensor0/mode");
}

TEST(SensorPort, getModesPath)
{
    using namespace finder::physical::test;

    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");
    ASSERT_EQ(sensorPort.getModesPath(), "");
    sensorPort.overrideEnabled(true);
    ASSERT_EQ(sensorPort.getModesPath(), "/sys/class/lego-sensor/sensor0/modes");
}

TEST(SensorPort, getNumValuesPath)
{
    using namespace finder::physical::test;

    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");
    ASSERT_EQ(sensorPort.getNumValuesPath(), "");
    sensorPort.overrideEnabled(true);
    ASSERT_EQ(sensorPort.getNumValuesPath(), "/sys/class/lego-sensor/sensor0/num_values");
}

TEST(SensorPort, getPollMsPath)
{
    using namespace finder::physical::test;

    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");
    ASSERT_EQ(sensorPort.getPollMsPath(), "");
    sensorPort.overrideEnabled(true);
    ASSERT_EQ(sensorPort.getPollMsPath(), "/sys/class/lego-sensor/sensor0/poll_ms");
}

TEST(SensorPort, getValue)
{
    using namespace finder::physical::test;
    FakeSys::reinit();

    finder::physical::SensorPort sensorPort(FakeSys::getWorkingDir() + "/lego-sensor/sensor0");
    sensorPort.overrideEnabled(false);
    ASSERT_EQ(sensorPort.getValue(0), -1);
    sensorPort.overrideEnabled(true);
    ASSERT_EQ(sensorPort.getValue(0), 0);

    ASSERT_EQ(sensorPort.getValue(100), -1);
    ASSERT_EQ(sensorPort.getValue(-1), -1);
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
    fs_commands << "test-commands 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18";
    
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
    ASSERT_EQ(sensorPort.getDeviceType(), finder::physical::DeviceType::SENSOR);
    ASSERT_EQ(sensorPort.getValuePath(0), FakeSys::getWorkingDir() + "/lego-sensor/sensor0/value0");

    ASSERT_EQ(sensorPort.getValue(0), 42);
    ASSERT_EQ(sensorPort.getAddress(), "ev3-ports:in1");

    sensorPort.setMode("test-mode"); 
    std::ifstream mode_file(FakeSys::getWorkingDir() + "/lego-sensor/sensor0/mode");
    std::string mode_str;
    mode_file >> mode_str;
    ASSERT_EQ(mode_str, "test-mode");

    std::vector<std::string> modes = sensorPort.getModes();
    ASSERT_EQ(modes.size(), 3);
    ASSERT_EQ(modes[0], "EV3-IR");
    ASSERT_EQ(modes[1], "EV3-Color");
    ASSERT_EQ(modes[2], "EV3-Ultrasonic");

    ASSERT_EQ(sensorPort.getNumValues(), 1);
    sensorPort.overrideEnabled(false);
    ASSERT_EQ(sensorPort.getNumValues(), -1);
    sensorPort.overrideEnabled(true);

    ASSERT_EQ(sensorPort.getPollMs(), 100);
    sensorPort.overrideEnabled(false);
    ASSERT_EQ(sensorPort.getPollMs(), -1);
    sensorPort.overrideEnabled(true);

    // remove temp files
    std::filesystem::remove_all(FakeSys::getWorkingDir() + "");
}