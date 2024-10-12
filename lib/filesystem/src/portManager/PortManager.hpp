// this file is to manage all devices in the system
#ifndef DEVICE_MANAGER_HPP
#define DEVICE_MANAGER_HPP

#define ENABLE_LOGGING

#include "../../../EV3_conf.hpp"
#include <string>
#include <array>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <portManager/port/SensorPort.hpp>
#include <portManager/port/MotorPort.hpp>

namespace finder
{
    namespace physical
    {
        #define MAX_DEVICES 8
        #define MAX_SENSORS 4
        #define MAX_MOTORS 4

        
        
        enum struct DeviceID
        {
            GYRO          = EV3_PORT_INPUT_1,
            COLOR_LEFT    = EV3_PORT_INPUT_2,
            COLOR_RIGHT   = EV3_PORT_INPUT_3,
            COLOR_FRONT   = EV3_PORT_INPUT_4,
            MOTOR_LEFT    = EV3_PORT_OUTPUT_A,
            MOTOR_RIGHT   = EV3_PORT_OUTPUT_B,
            MOTOR_SHIFT   = EV3_PORT_OUTPUT_C,
            MOTOR_TOOL    = EV3_PORT_OUTPUT_D,
            ANY           = 0,
            ANY_MOTOR     = 254,
            ANY_SENSOR    = 253,
        };
        
        /// @brief Class to manage the ports
        class PortManager {
            
            public:
                /// @brief List of all the ports
                static std::vector<std::string> adresses;
                
                PortManager();

                /// @brief Constructor
                /// @param dir The path to the directory of the ports
                PortManager(path_port_t dir);
                ~PortManager();
                
                /// @brief Read all the ports
                static void readPorts();

                /// @warning DO NOT USE THIS FUNCTION : DEPRECATED
                /// @param port_address 
                /// @return shared pointer to a port object
                static std::shared_ptr<Port> borrowDevice(DevicePort port_address);
                
                /// @brief Borrow a port from the port manager
                /// @param port_address The address of the port
                /// @return The port
                static std::shared_ptr<SensorPort> borrowSensor(DevicePort port_address);

                /// @brief Borrow a port from the port manager
                /// @param port The address of the port
                /// @return The port
                static std::shared_ptr<SensorPort> borrowSensor(DeviceID port);

                /// @brief Borrow a port from the port manager
                /// @param port The address of the port
                /// @return The port
                static std::shared_ptr<MotorPort> borrowMotor(DevicePort port);

                /// @brief Borrow a port from the port manager
                /// @param port_address The address of the port
                /// @return The port
                static std::shared_ptr<MotorPort> borrowMotor(DeviceID port_address);

                /// @brief Get the number of devices
                /// @return The number of devices
                static int getNumberOfDevices() {return _motor_ports.size() + _sensor_ports.size();}

            private:
                static std::vector<std::shared_ptr<Port>> _borrowed_ports;
                static int _read_ports_future;

                static bool _ports_read;

                static path_port_t _sensor_dir;
                static path_port_t _motor_dir;

                static std::array<std::shared_ptr<SensorPort>, MAX_SENSORS> _sensor_ports;
                static std::array<std::shared_ptr<MotorPort>, MAX_MOTORS> _motor_ports;

                static void init();

                static log4cplus::Logger _logger;
        };

    } // namespace physical
} // namespace finder

#endif // DEVICE_MANAGER_HPP