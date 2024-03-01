#ifndef __DEVICE_MANAGER_HPP__
#define __DEVICE_MANAGER_HPP__

#include <physical/portManager/PortManager.hpp>
#include <physical/portManager/port/MotorPort.hpp>
#include <physical/portManager/port/SensorPort.hpp>

namespace finder
{
    namespace physical
    {
        class DeviceManager
        {
            public:
                DeviceManager();
                ~DeviceManager();

                // TODO: Change to SensorPorts and MotorPorts
                static std::shared_ptr<SensorPort> getGyroSensor();
                static std::shared_ptr<SensorPort> getColorSensorLeft();
                static std::shared_ptr<SensorPort> getColorSensorRight();
                static std::shared_ptr<SensorPort> getColorSensorFront();

                static std::shared_ptr<MotorPort> getMotorLeft();
                static std::shared_ptr<MotorPort> getMotorRight();
                static std::shared_ptr<MotorPort> getMotorShift();
                static std::shared_ptr<MotorPort> getMotorTool();

            private:
                static std::shared_ptr<PortManager> _portManager;

                static std::shared_ptr<SensorPort> _gyroSensor;
                static std::shared_ptr<SensorPort> _colorSensorLeft;
                static std::shared_ptr<SensorPort> _colorSensorRight;
                static std::shared_ptr<SensorPort> _colorSensorFront;

                static std::shared_ptr<MotorPort> _motorLeft;
                static std::shared_ptr<MotorPort> _motorRight;
                static std::shared_ptr<MotorPort> _motorShift;
                static std::shared_ptr<MotorPort> _motorTool;

                static bool _initialized;

                static void init();
        };
    } // namespace physical
} // namespace finder


#endif // __DEVICE_MANAGER_HPP__