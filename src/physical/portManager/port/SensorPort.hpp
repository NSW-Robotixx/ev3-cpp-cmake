#include <physical/portManager/port/Port.hpp>
#include <filesystem>
#include <vector>

namespace finder
{
    namespace physical
    {
        typedef std::string sensor_mode_t;

        class SensorPort : Port {
            public:
                SensorPort();
                SensorPort(std::string port_name);
                SensorPort(std::shared_ptr<Port> port);
                ~SensorPort();

                inline path_value_t getValuePath(int index);
                inline path_mode_t getModePath();
                inline path_modes_t getModesPath();
                inline path_num_values_t getNumValuesPath();
                inline path_poll_ms_t getPollMsPath();

                int getValue(int index);
                void setMode(sensor_mode_t mode);
                std::vector<sensor_mode_t> getModes();
                int getNumValues();
                int getPollMs();
                
            private:
                static ::finder::console::Logger _logger;

                static std::vector<sensor_mode_t> _modes;

                std::shared_ptr<std::ifstream> _file_value_path;
                std::shared_ptr<std::ofstream> _file_mode_path;
                std::shared_ptr<std::ifstream> _file_modes_path;
                std::shared_ptr<std::ifstream> _file_num_values_path;
                std::shared_ptr<std::ifstream> _file_poll_ms_path;

                bool _is_initialized;

                void initFiles();
        };
    } // namespace physical
    
} // namespace finder
