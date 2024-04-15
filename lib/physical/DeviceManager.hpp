#ifndef __DEVICE_MANAGER_HPP__
#define __DEVICE_MANAGER_HPP__

#include <physical/portManager/PortManager.hpp>
#include <physical/portManager/port/MotorPort.hpp>
#include <physical/portManager/port/SensorPort.hpp>

namespace finder
{
    namespace physical
    {
        enum struct DeviceID
        {
            GYRO = 1,
            COLOR_LEFT = 2,
            COLOR_RIGHT = 3,
            COLOR_FRONT = 4,
            MOTOR_LEFT = 5,
            MOTOR_RIGHT = 6,
            MOTOR_SHIFT = 7,
            MOTOR_TOOL  = 8,
        };

        class DeviceManager
        {
            public:
                DeviceManager();
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

                static void init();
        };
    } // namespace physical
} // namespace finder


#endif // __DEVICE_MANAGER_HPP__