#include <gtest/gtest.h>

#include <physical/portManager/DeviceFactory.hpp>


TEST(DeviceFactory, getDevice) {
    using namespace finder::physical;
    
    DeviceManager::DeviceType type = DeviceManager::DeviceType::SENSOR;
    DeviceManager::DevicePort port = DeviceManager::DevicePort::INPUT_1;
    Port p = DeviceFactory::getDevice(type, port);
    ASSERT_EQ(p.isEnabled(), false);
}