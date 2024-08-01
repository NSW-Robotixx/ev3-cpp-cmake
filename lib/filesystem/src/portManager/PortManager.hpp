// this file is to manage all devices in the system
#ifndef DEVICE_MANAGER_HPP
#define DEVICE_MANAGER_HPP

#define ENABLE_LOGGING

#include <string>
#include <array>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <portManager/port/SensorPort.hpp>
#include <portManager/port/MotorPort.hpp>
#ifdef ENABLE_LOGGING
#include <Logger.hpp>
#endif

namespace finder
{
    namespace physical
    {
        #define MAX_DEVICES 8
        #define MAX_SENSORS 4
        #define MAX_MOTORS 4

        enum struct DevicePort {
            INPUT_1  = '1',
            INPUT_2  = '2',
            INPUT_3  = '3',
            INPUT_4  = '4',
            OUTPUT_A = 'A',
            OUTPUT_B = 'B',
            OUTPUT_C = 'C',
            OUTPUT_D = 'D'
        };
        enum struct DeviceID
        {
            GYRO          = static_cast<char>(DevicePort::INPUT_1),
            COLOR_LEFT    = static_cast<char>(DevicePort::INPUT_2),
            COLOR_RIGHT   = static_cast<char>(DevicePort::INPUT_3),
            COLOR_FRONT   = static_cast<char>(DevicePort::INPUT_4),
            MOTOR_LEFT    = static_cast<char>(DevicePort::OUTPUT_A),
            MOTOR_RIGHT   = static_cast<char>(DevicePort::OUTPUT_B),
            MOTOR_SHIFT   = static_cast<char>(DevicePort::OUTPUT_C),
            MOTOR_TOOL    = static_cast<char>(DevicePort::OUTPUT_D),
            ANY           = 0,
            ANY_MOTOR     = 254,
            ANY_SENSOR    = 253,
        };
        

        class PortManager {
            
            public:
                static std::vector<std::string> adresses;
                
                PortManager();
                PortManager(path_port_t dir);
                ~PortManager();
                
                static void readPorts();

                static std::shared_ptr<Port> borrowDevice(DevicePort port_address);
                
                static std::shared_ptr<SensorPort> borrowSensor(DevicePort port_address);
                static std::shared_ptr<SensorPort> borrowSensor(DeviceID port);

                static std::shared_ptr<MotorPort> borrowMotor(DevicePort port);
                static std::shared_ptr<MotorPort> borrowMotor(DeviceID port_address);

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

#ifdef ENABLE_LOGGING
                static ::finder::log::Logger _logger;
#endif
        };

    } // namespace physical
} // namespace finder

#endif // DEVICE_MANAGER_HPP