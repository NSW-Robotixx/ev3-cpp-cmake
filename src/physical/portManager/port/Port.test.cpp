#include <gtest/gtest.h>

#include <physical/portManager/port/Port.hpp>

TEST(PortTest, BasicAssertions) {
    using namespace finder::physical;

    Port port = Port("./test");

    EXPECT_EQ(port.isEnabled(), true);
    EXPECT_EQ(port.getBasePath(), "./test");
}

TEST(PortTest, PathAssertions) {
    using namespace finder::physical;

    Port port = Port("./test");

    port.setBasePath("/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getBasePath(), "/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getAddressPath(), "/sys/class/lego-sensor/sensor0/address");
    EXPECT_EQ(port.getValuePath(), "/sys/class/lego-sensor/sensor0/value0");
    EXPECT_EQ(port.getModePath(), "/sys/class/lego-sensor/sensor0/mode");
}

TEST(PortTest, SetPathAssertions) {
    using namespace finder::physical;

    Port port = Port("./test");

    port.setBasePath("/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getBasePath(), "/sys/class/lego-sensor/sensor0");
    port.setBasePath("/sys/class/lego-sensor/sensor1");
    EXPECT_EQ(port.getBasePath(), "/sys/class/lego-sensor/sensor1");
}

TEST(PortTest, EmptyPathAssertions) {
    using namespace finder::physical;

    Port port = Port("./test");

    EXPECT_EQ(port.getBasePath(), "./test");

    port.setBasePath("/sys/class/lego-sensor/sensor0");
    EXPECT_EQ(port.getBasePath(), "/sys/class/lego-sensor/sensor0");

    port.setBasePath("");
    EXPECT_EQ(port.getBasePath(), "");
    EXPECT_EQ(port.getAddressPath(), "");

    EXPECT_EQ(port.isEnabled(), false);
}