#ifndef __SENSOR_PORT_HPP__
#define __SENSOR_PORT_HPP__

#include <physical/portManager/port/Port.hpp>
#include <filesystem>
#include <vector>
namespace finder
{
    namespace physical
    {
        typedef std::string sensor_mode_t;

        class SensorPort : public Port {
            public:
                // SensorPort();
                SensorPort(std::string port_name);
                SensorPort(std::shared_ptr<Port> port);

                void setBasePath(const path_port_t& path) override;

                path_value_t getValuePath(int index);
                path_mode_t getModePath();
                path_modes_t getModesPath();
                path_num_values_t getNumValuesPath();
                path_poll_ms_t getPollMsPath();

                int getValue(int index);
                void setMode(sensor_mode_t mode);
                std::vector<sensor_mode_t> getModes();
                int getNumValues();
                int getPollMs();

                DeviceType getDeviceType() override;
                
            private:
                static ::finder::console::Logger _logger;

                static std::vector<sensor_mode_t> _modes;

                std::vector<std::shared_ptr<std::ifstream>> _file_value_path;
                std::shared_ptr<std::ofstream> _file_mode_path;
                std::shared_ptr<std::ifstream> _file_modes_path;
                std::shared_ptr<std::ifstream> _file_num_values_path;
                std::shared_ptr<std::ifstream> _file_poll_ms_path;

                bool _is_initialized;

                bool initFiles();
        };
    } // namespace physical
    
} // namespace finder

#endif // __SENSOR_PORT_HPP__