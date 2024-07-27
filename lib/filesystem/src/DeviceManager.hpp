#ifndef __DEVICE_MANAGER_HPP__
#define __DEVICE_MANAGER_HPP__

#include <portManager/PortManager.hpp>
#include <portManager/port/MotorPort.hpp>
#include <portManager/port/SensorPort.hpp>

namespace finder
{
    namespace physical
    {
        class DeviceManager
        {
            public:
                DeviceManager(std::string portBasePath);
                ~DeviceManager();

            protected:
                static std::shared_ptr<PortManager> _portManager;

                static std::shared_ptr<SensorPort> _gyroSensor;
                static std::shared_ptr<SensorPort> _colorSensorLeft;
                static std::shared_ptr<SensorPort> _colorSensorRight;
                static std::shared_ptr<SensorPort> _colorSensorFront;

                static std::shared_ptr<MotorPort> _motorLeft;
                static std::shared_ptr<MotorPort> _motorRight;
                static std::shared_ptr<MotorPort> _motorShift;
                static std::shared_ptr<MotorPort> _motorTool;

            private:
                static bool _initialized;

                static void init(std::string portBasePath);
        };
    } // namespace physical
} // namespace finder


#endif // __DEVICE_MANAGER_HPP__