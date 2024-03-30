#include <physical/portManager/port/Port.hpp>
#include "Port.hpp"

namespace finder
{
    namespace physical
    {
        ::finder::console::Logger Port::_logger = ::finder::console::Logger{};

        Port::Port()
        {
            _f_enabled = initFiles();
        }

        Port::Port(const path_port_t &port)
        {
            setBasePath(port);
        }

        Port::Port(std::shared_ptr<Port> port)
        {
            setBasePath(port->getBasePath());
        }

        void Port::setBasePath(const path_port_t &path)
        {
            if (path.empty()) {
                _logger.log(
                    ::finder::console::Logger::LogLevel::WARN, 
                    "Port path is empty"
                );
                return;
            }
            _path = path;
            _f_enabled = initFiles();
        }
        
        path_port_t Port::getBasePath()
        {
            if (isEnabled()) {
                return _path;
            }
            return "";
        }

        path_address_t Port::getAddressPath()
        {
            if (isEnabled()) {
                return _path + "/address";
            }
            return "";
        }

        path_command_t Port::getCommandPath()
        {
            if (isEnabled()) {
                return _path + "/command";
            }
            return "";
        }

        path_commands_t Port::getCommandsPath()
        {
            if (isEnabled()) {
                return _path + "/commands";
            }
            return "";
        }

        std::string Port::getAddress()
        {
            if (isEnabled()) {
                std::string address;
                *_file_address_path >> address;
                return address;
            }
            return "";
        }

        bool Port::setCommand(std::string command)
        {
            if (isEnabled()) {
                *_file_command_path << command;
                return true;
            }
            return false;
        }

        std::vector<std::string> Port::getCommands()
        {
            if (isEnabled()) {
                std::vector<std::string> commands;
                std::string command_total;
                // split by space and store in vector
                *_file_commands_path >> command_total;
                std::istringstream iss(command_total);
                std::string command;
                while (iss >> command) {
                    commands.push_back(command);
                }
                return commands;
            }
            return {};
        }

        DeviceType Port::getDeviceType()
        {
            _logger.debug(
                "Checking device type for port: " + _path
            );
            if (isEnabled()) {
                if (_path.find("sensor") != std::string::npos) {
                    return DeviceType::SENSOR;
                } else if (_path.find("motor") != std::string::npos) {
                    return DeviceType::MOTOR;
                } else {
                    return DeviceType::UNKNOWN;
                }
            }
            return DeviceType::DISABLED;
        }

        bool Port::initFiles()
        {
            using namespace ::finder::console;
            std::string address_path = _path + "/address";
            std::string command_path = _path + "/command";
            std::string commands_path = _path + "/commands";


            _file_address_path = std::make_shared<std::ifstream>();
            _file_command_path = std::make_shared<std::ofstream>();
            _file_commands_path = std::make_shared<std::ifstream>();

            _file_address_path->open(address_path);
            _file_command_path->open(command_path);
            _file_commands_path->open(commands_path);

            if (
                // ( access( (_path + "/address").c_str(), F_OK ) == -1 ) ||
                // ( access( (_path + "/command").c_str(), F_OK ) == -1 ) ||
                // ( access( (_path + "/commands").c_str(), F_OK ) == -1 )
                false
            ) {
                _logger.log(
                    Logger::LogLevel::DEBUG, 
                    "Port files not found at: " + _path + "/address"
                );
            } else {
                if (
                    _file_address_path->is_open() == false ||
                    _file_command_path->is_open() == false ||
                    _file_commands_path->is_open() == false
                ) {
                _logger.log(
                        Logger::LogLevel::WARN, 
                        "Failed to open port files at: " + _path + "/address"
                    ); 
                } else {
                    return true;
                }
            }
            return false;
        }

        bool Port::isEnabled()
        {
            return _f_enabled;
        }
    } // namespace physical
} // namespace finder
