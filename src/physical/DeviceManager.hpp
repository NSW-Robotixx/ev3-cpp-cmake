#ifndef __DEVICE_MANAGER_HPP__
#define __DEVICE_MANAGER_HPP__

#include <physical/portManager/PortManager.hpp>
#include <physical/Motor.hpp>
#include <physical/Sensor.hpp>

namespace finder
{
    namespace physical
    {
        class DeviceManager
        {
            public:
                DeviceManager();
                ~DeviceManager();
        };        
    } // namespace physical
} // namespace finder


#endif // __DEVICE_MANAGER_HPP__