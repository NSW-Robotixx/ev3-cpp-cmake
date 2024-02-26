// this file is to manage all devices in the system
#ifndef DEVICE_MANAGER_HPP
#define DEVICE_MANAGER_HPP

#include <string>
#include <array>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <atomic>
#include <unistd.h>
#include <filesystem>
#include <console/Logger.hpp>
#include <physical/portManager/port/Port.hpp>


namespace finder
{
    namespace physical
    {
        #define MAX_DEVICES 8
        class PortManager {
            
            public:
                enum struct DeviceType {
                    SENSOR,
                    MOTOR
                };

                enum struct DevicePort {
                    INPUT_1 = '1',
                    INPUT_2 = '2',
                    INPUT_3 = '3',
                    INPUT_4 = '4',
                    OUTPUT_A = 'A',
                    OUTPUT_B = 'B',
                    OUTPUT_C = 'C',
                    OUTPUT_D = 'D'
                };
                static std::vector<std::string> adresses;
                
                PortManager();
                PortManager(path_port_t dir);
                
                static void readPorts();

                static std::shared_ptr<Port> borrowDevice(PortManager::DeviceType type, std::string port_address);
                static void returnDevice(std::shared_ptr<Port> port);

                static int getNumberOfDevices() {return _ports.size();}

            private:
                static std::vector<std::shared_ptr<Port>> _borrowed_ports;
                static std::future<int> _read_ports_future;

                static std::atomic<bool> _ports_read;

                static std::vector<std::shared_ptr<Port>> _ports;

                static path_port_t _sensor_dir;
                static path_port_t _motor_dir;

                static void init();

                static ::finder::console::Logger _logger;
        };

    } // namespace physical
} // namespace finder

#endif // DEVICE_MANAGER_HPP