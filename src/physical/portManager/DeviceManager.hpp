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
#include <physical/portManager/port/Port.hpp>


namespace finder
{
    namespace physical
    {
        #define MAX_DEVICES 8

        typedef struct {
            Port input_1;
            Port input_2;
            Port input_3;
            Port input_4;
            Port output_A;
            Port output_B;
            Port output_C;
            Port output_D;
        } Ports;

        typedef struct {
            std::string input_1;
            std::string input_2;
            std::string input_3;
            std::string input_4;
            std::string output_A;
            std::string output_B;
            std::string output_C;
            std::string output_D;
        } Adresses;



        class DeviceManager {
            
            public:
                enum struct DeviceType {
                    SENSOR,
                    MOTOR
                };

                enum struct DevicePort {
                    INPUT_1,
                    INPUT_2,
                    INPUT_3,
                    INPUT_4,
                    OUTPUT_A,
                    OUTPUT_B,
                    OUTPUT_C,
                    OUTPUT_D
                };
                
                DeviceManager();
                DeviceManager(path_port_t dir);
                
                static int readPorts();
                static Ports getPorts() {return _ports;}

                static path_port_t getSensorDir() {return _sensor_dir;}
                static path_port_t getMotorDir() {return _motor_dir;}

                static Port getSensor(Port port);
                static Port getMotor(Port port);

            private:
                static Ports _ports;  
                static Adresses _adresses;

                static path_port_t _sensor_dir;
                static path_port_t _motor_dir;

                static void init();
        };

    } // namespace physical
} // namespace finder

#endif // DEVICE_MANAGER_HPP