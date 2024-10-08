#ifndef __DEVICE_MANAGER_HPP__
#define __DEVICE_MANAGER_HPP__

#include <portManager/PortManager.hpp>
#include <portManager/port/MotorPort.hpp>
#include <portManager/port/SensorPort.hpp>

namespace finder
{
    namespace physical
    {
        /// @brief Manage the connected devices
        class DeviceManager
        {
            public:
                /// @brief Constructor
                /// @param portBasePath Path to the base directory of the ports 
                DeviceManager(std::string portBasePath);
                ~DeviceManager();

            protected:
                /// @brief Port manager to manage the ports
                static std::shared_ptr<PortManager> _portManager;

                /// @brief Gyro sensor port
                static std::shared_ptr<SensorPort> _gyroSensor;

                /// @brief Color sensor left port
                static std::shared_ptr<SensorPort> _colorSensorLeft;

                /// @brief Color sensor right port
                static std::shared_ptr<SensorPort> _colorSensorRight;

                /// @brief Color sensor front port
                static std::shared_ptr<SensorPort> _colorSensorFront;

                /// @brief Motor left port
                static std::shared_ptr<MotorPort> _motorLeft;

                /// @brief Motor right port
                static std::shared_ptr<MotorPort> _motorRight;

                /// @brief Motor shift port
                static std::shared_ptr<MotorPort> _motorShift;

                /// @brief Motor tool port
                static std::shared_ptr<MotorPort> _motorTool;

            private:
                static bool _initialized;

                static void init(std::string portBasePath);
        };
    } // namespace physical
} // namespace finder


#endif // __DEVICE_MANAGER_HPP__