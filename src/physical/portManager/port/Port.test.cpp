#include <gtest/gtest.h>

#include <physical/portManager/port/Port.hpp>

TEST(PortTest, BasicAssertions) {
    using namespace finder::physical;

    Port port = Port();

    EXPECT_EQ(port.isEnabled(), false);
    EXPECT_EQ(port.getBasePath(), "");
    port.setEnabled();
    EXPECT_EQ(port.isEnabled(), true);
    EXPECT_EQ(port.getBasePath(), "");
}

TEST(PortTest, PathAssertions) {
    using namespace finder::physical;

    Port port = Port();

    port.setBasePath("/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getBasePath(), "/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getAddressPath(), "/sys/class/lego-sensor/sensor0/address");
    EXPECT_EQ(port.getValuePath(), "/sys/class/lego-sensor/sensor0/value0");
    EXPECT_EQ(port.getModePath(), "/sys/class/lego-sensor/sensor0/mode");
    EXPECT_EQ(port.getCommandPath(), "/sys/class/lego-sensor/sensor0/command");
    EXPECT_EQ(port.getPositionSpPath(), "/sys/class/lego-sensor/sensor0/position_sp");
    EXPECT_EQ(port.getSpeedPath(), "/sys/class/lego-sensor/sensor0/speed_sp");
    EXPECT_EQ(port.getCountPerRotationPath(), "/sys/class/lego-sensor/sensor0/count_per_rot");
    EXPECT_EQ(port.getDutyCyclePath(), "/sys/class/lego-sensor/sensor0/duty_cycle_sp");
    EXPECT_EQ(port.getStopActionPath(), "/sys/class/lego-sensor/sensor0/stop_action");
    EXPECT_EQ(port.getPolarityPath(), "/sys/class/lego-sensor/sensor0/polarity");
    EXPECT_EQ(port.getStatePath(), "/sys/class/lego-sensor/sensor0/state");
}

TEST(PortTest, SetPathAssertions) {
    using namespace finder::physical;

    Port port = Port();

    port.setBasePath("/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getBasePath(), "/sys/class/lego-sensor/sensor0");
    port.setBasePath("/sys/class/lego-sensor/sensor1");
    EXPECT_EQ(port.getBasePath(), "/sys/class/lego-sensor/sensor1");
}

TEST(PortTest, EmptyPathAssertions) {
    using namespace finder::physical;

    Port port = Port();

    EXPECT_EQ(port.getBasePath(), "");

    port.setBasePath("/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getBasePath(), "/sys/class/lego-sensor/sensor0");

    port.setBasePath("");
    EXPECT_EQ(port.getBasePath(), "");
    EXPECT_EQ(port.getAddressPath(), "");

    EXPECT_EQ(port.isEnabled(), false);
}