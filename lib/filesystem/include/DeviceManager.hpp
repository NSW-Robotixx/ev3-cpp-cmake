#ifndef __DEVICE_MANAGER_HPP__
#define __DEVICE_MANAGER_HPP__

#include <portManager/PortManager.hpp>
#include <portManager/port/MotorPort.hpp>
#include <portManager/port/SensorPort.hpp>
#include <boost/thread/once.hpp>

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

                /// @brief Reinitialize the DeviceManager
                void reinit();


            protected:
                DeviceManager();

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

                /// @brief Initialize the Ports in the DeviceManager
                /// @param portBasePath Base path of the ports
                static void init(std::string portBasePath);

                /// @brief Check if the DeviceManager was initialized
                /// @return Initialized?
                bool isInitialized();

                /// @brief Once flag for the DeviceManager
                static boost::once_flag _device_manager_init_once_flag;
                
            private:
                static bool _initialized;
        };
    } // namespace physical
} // namespace finder


#endif // __DEVICE_MANAGER_HPP__