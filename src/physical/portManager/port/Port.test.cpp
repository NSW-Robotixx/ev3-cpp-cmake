#include <gtest/gtest.h>

#include <physical/portManager/port/Port.hpp>

TEST(Port, getPortKey)
{
    finder::physical::Port port;
    port.setBasePath("/sys/class/lego-sensor/sensor0");
    ASSERT_EQ(port.getPortKey(), 0);
}

TEST(Port, getBasePath)
{
    finder::physical::Port port;
    port.setBasePath("/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getBasePath(), "/sys/class/lego-sensor/sensor0");
}

TEST(Port, getAddressPath)
{
    finder::physical::Port port;
    port.setBasePath("/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getAddressPath(), "/sys/class/lego-sensor/sensor0/address");
}

TEST(Port, getCommandPath)
{
    finder::physical::Port port;
    port.setBasePath("/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getCommandPath(), "/sys/class/lego-sensor/sensor0/command");
}

TEST(Port, getCommandsPath)
{
    finder::physical::Port port;
    port.setBasePath("/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getCommandPath(), "/sys/class/lego-sensor/sensor0/commands");
}

TEST(Port, getDeviceType)
{
    finder::physical::Port sensorPort;
    finder::physical::Port motorPort;

    sensorPort.setBasePath("/sys/class/lego-sensor/sensor0");
    motorPort.setBasePath("/sys/class/lego-motor/motor0");
    
    ASSERT_EQ(sensorPort.getDeviceType(), finder::physical::DeviceType::SENSOR);
    ASSERT_EQ(motorPort.getDeviceType(), finder::physical::DeviceType::MOTOR);
}

