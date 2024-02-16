#include <gtest/gtest.h>

#include <physical/portManager/port/Port.hpp>

TEST(Port, constructor) {
    using namespace finder::physical;

        Port port("/test/path/to/port");

    ASSERT_EQ(port.getBasePath(), "/test/path/to/port");
    ASSERT_EQ(port.getAddressPath(), "/test/path/to/port/address");
    ASSERT_EQ(port.getModePath(), "/test/path/to/port/mode");
    ASSERT_EQ(port.getValuePath(), "/test/path/to/port/value0");
    ASSERT_EQ(port.getCommandPath(), "/test/path/to/port/command");
    ASSERT_EQ(port.getPositionPath(), "/test/path/to/port/position_sp");
    ASSERT_EQ(port.getSpeedPath(), "/test/path/to/port/speed_sp");
    ASSERT_EQ(port.getCountPerRotationPath(), "/test/path/to/port/count_per_rot");
    ASSERT_EQ(port.getDutyCyclePath(), "/test/path/to/port/duty_cycle_sp");
    ASSERT_EQ(port.getStopActionPath(), "/test/path/to/port/stop_action");
    ASSERT_EQ(port.getPolarityPath(), "/test/path/to/port/polarity");
    ASSERT_EQ(port.getStatePath(), "/test/path/to/port/state");
};

TEST(Port, functionsetPath) {
    using namespace finder::physical;

    Port port("/test/path/to/port");
    port.setBasePath("/new/path/to/port");

    ASSERT_EQ(port.getBasePath(), "/new/path/to/port");
    ASSERT_EQ(port.getAddressPath(), "/new/path/to/port/address");
    ASSERT_EQ(port.getModePath(), "/new/path/to/port/mode");
    ASSERT_EQ(port.getValuePath(), "/new/path/to/port/value0");
    ASSERT_EQ(port.getCommandPath(), "/new/path/to/port/command");
    ASSERT_EQ(port.getPositionPath(), "/new/path/to/port/position_sp");
    ASSERT_EQ(port.getSpeedPath(), "/new/path/to/port/speed_sp");
    ASSERT_EQ(port.getCountPerRotationPath(), "/new/path/to/port/count_per_rot");
    ASSERT_EQ(port.getDutyCyclePath(), "/new/path/to/port/duty_cycle_sp");
    ASSERT_EQ(port.getStopActionPath(), "/new/path/to/port/stop_action");
    ASSERT_EQ(port.getPolarityPath(), "/new/path/to/port/polarity");
    ASSERT_EQ(port.getStatePath(), "/new/path/to/port/state");
}

TEST(Port, functionsetEnabled) {
    using namespace finder::physical;

    Port port("/test/path/to/port");
    port.setEnabled();

    ASSERT_EQ(port.isEnabled(), 1);
}

TEST(Port, functionsetDisabled) {
    using namespace finder::physical;

    Port port("/test/path/to/port");
    port.setDisabled();

    ASSERT_EQ(port.isEnabled(), 0);
}