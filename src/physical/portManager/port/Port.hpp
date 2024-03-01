#ifndef PORT_HPP
#define PORT_HPP
#include <string>
#include <memory>
#include <fstream>
#include <console/Logger.hpp>
#include <filesystem>
namespace finder
{
    namespace physical
    {
        typedef std::string path_port_t;
        typedef std::string path_address_t;
        typedef std::string path_value_t;
        typedef std::string path_mode_t;
        typedef std::string path_modes_t;
        typedef std::string path_command_t;
        typedef std::string path_commands_t;
        typedef std::string path_position_sp_t;
        typedef std::string path_speed_t;
        typedef std::string path_count_per_rotation_t;
        typedef std::string path_duty_cycle_t;
        typedef std::string path_stop_action_t;
        typedef std::string path_polarity_t;
        typedef std::string path_state_t;
        typedef std::string path_num_values_t;
        typedef std::string path_poll_ms_t;

        struct Port
        {
            public:
                Port();
                Port(const path_port_t& port);
                Port(std::shared_ptr<Port> port);
                Port(Port&) = delete;
                ~Port() = default;

                void setBasePath(const path_port_t& path);
                
                char getPortKey();
                path_port_t getBasePath();
                path_address_t getAddressPath();
                path_command_t getCommandPath();
                path_commands_t getCommandsPath();
                bool initFiles();
            
                bool isEnabled();

            protected:
                std::shared_ptr<std::ifstream> _file_address_path;
                std::shared_ptr<std::ofstream> _file_command_path;
                std::shared_ptr<std::ifstream> _file_commands_path;
                path_port_t _path;
            private:
                bool _f_enabled;
                // bool _enabled;
                static ::finder::console::Logger _logger;

        };

    } // namespace physical
    
} // namespace finder

#endif // PORT_HPP