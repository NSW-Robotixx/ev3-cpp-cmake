#include <gtest/gtest.h>

#include <physical/portManager/port/SensorPort.hpp>

TEST(SensorPort, DefaultConstructor)
{
    finder::physical::SensorPort sensorPort;
    ASSERT_EQ(sensorPort.getDeviceType(), finder::physical::DeviceType::SENSOR);
} 

TEST(SensorPort, Constructor)
{
    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");
    ASSERT_EQ(sensorPort.getDeviceType(), finder::physical::DeviceType::SENSOR);
}

TEST(SensorPort, ConstructorWithPort)
{
    std::shared_ptr<finder::physical::Port> port = std::make_shared<finder::physical::Port>("/sys/class/lego-sensor/sensor0");
    finder::physical::SensorPort sensorPort(port);
    ASSERT_EQ(sensorPort.getDeviceType(), finder::physical::DeviceType::SENSOR);
}

TEST(SensorPort, getValuePath)
{
    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");
    ASSERT_EQ(sensorPort.getValuePath(0), "");
    sensorPort.overrideEnabled(true);
    ASSERT_EQ(sensorPort.getValuePath(0), "/sys/class/lego-sensor/sensor0/value0");
}

TEST(SensorPort, getModePath)
{
    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");
    ASSERT_EQ(sensorPort.getModePath(), "");
    sensorPort.overrideEnabled(true);
    ASSERT_EQ(sensorPort.getModePath(), "/sys/class/lego-sensor/sensor0/mode");
}

TEST(SensorPort, getModesPath)
{
    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");
    ASSERT_EQ(sensorPort.getModesPath(), "");
    sensorPort.overrideEnabled(true);
    ASSERT_EQ(sensorPort.getModesPath(), "/sys/class/lego-sensor/sensor0/modes");
}

TEST(SensorPort, getNumValuesPath)
{
    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");
    ASSERT_EQ(sensorPort.getNumValuesPath(), "");
    sensorPort.overrideEnabled(true);
    ASSERT_EQ(sensorPort.getNumValuesPath(), "/sys/class/lego-sensor/sensor0/num_values");
}

TEST(SensorPort, getPollMsPath)
{
    finder::physical::SensorPort sensorPort("/sys/class/lego-sensor/sensor0");
    ASSERT_EQ(sensorPort.getPollMsPath(), "");
    sensorPort.overrideEnabled(true);
    ASSERT_EQ(sensorPort.getPollMsPath(), "/sys/class/lego-sensor/sensor0/poll_ms");
}

TEST(SensorPort, filestreams)
{
    std::filesystem::create_directories("./test/sensor0");
    std::ofstream fs_value("./test/sensor0/value0");
    std::ofstream fs_address("./test/sensor0/address");
    std::ofstream fs_mode("./test/sensor0/mode");
    std::ofstream fs_modes("./test/sensor0/modes");
    std::ofstream fs_num_values("./test/sensor0/num_values");
    std::ofstream fs_poll_ms("./test/sensor0/poll_ms");
    std::ofstream fs_commmand("./test/sensor0/command");
    std::ofstream fs_commands("./test/sensor0/commands");


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

    finder::physical::SensorPort sensorPort("./test/sensor0");
    sensorPort.setBasePath("./test/sensor0");
    ASSERT_EQ(sensorPort.getDeviceType(), finder::physical::DeviceType::SENSOR);
    ASSERT_EQ(sensorPort.getValuePath(0), "./test/sensor0/value0");

    ASSERT_EQ(sensorPort.getValue(0), 42);
    ASSERT_EQ(sensorPort.getAddress(), "ev3-ports:in1");

    sensorPort.setMode("test-mode"); 
    std::ifstream mode_file("./test/sensor0/mode");
    std::string mode_str;
    mode_file >> mode_str;
    ASSERT_EQ(mode_str, "test-mode");

    std::vector<std::string> modes = sensorPort.getModes();
    ASSERT_EQ(modes.size(), 3);
    ASSERT_EQ(modes[0], "EV3-IR");
    ASSERT_EQ(modes[1], "EV3-Color");
    ASSERT_EQ(modes[2], "EV3-Ultrasonic");

    ASSERT_EQ(sensorPort.getNumValues(), 1);
    ASSERT_EQ(sensorPort.getPollMs(), 100);
}

TEST(SensorPort, cleanUp)
{
    std::filesystem::remove_all("./test");

    ASSERT_FALSE(std::filesystem::exists("./test/sensor0/value0"));
}