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
            _path = path;
            _f_enabled = initFiles();
        }

        char Port::getPortKey()
        {
            if (isEnabled())
            {
                return _path.back();
            } else {
                return '-';
            }
        }
        
        path_port_t Port::getBasePath()
        {
            if (isEnabled()) {
                return _path;
            } else {
                return "";
            }
        }

        path_address_t Port::getAddressPath()
        {
            if (isEnabled()) {
                return _path + "/address";
            } else {
                return "";
            }
        }

        path_command_t Port::getCommandPath()
        {
            if (isEnabled()) {
                return _path + "/command";
            } else {
                return "";
            }
        }

        path_commands_t Port::getCommandsPath()
        {
            if (isEnabled()) {
                return _path + "/commands";
            } else {
                return "";
            }
        }

        DeviceType Port::getDeviceType()
        {
            if (isEnabled()) {
                if (_path.find("sensor") != std::string::npos) {
                    return DeviceType::SENSOR;
                } else if (_path.find("motor") != std::string::npos) {
                    return DeviceType::MOTOR;
                }
            }
            return DeviceType::SENSOR;
        }

        bool Port::initFiles()
        {
            using namespace ::finder::console;

            if (
                std::filesystem::exists(getAddressPath()) == false ||
                std::filesystem::exists(getCommandPath()) == false ||
                std::filesystem::exists(getCommandsPath()) == false
            ) {
                _logger.log(
                    Logger::LogLevel::DEBUG, 
                    "Port files not found at: " + getAddressPath()
                );
            } else {
                _file_address_path = std::make_shared<std::ifstream>();
                _file_command_path = std::make_shared<std::ofstream>();
                _file_commands_path = std::make_shared<std::ifstream>();

                _file_address_path->open(getAddressPath());
                _file_command_path->open(getCommandPath());
                _file_commands_path->open(getCommandsPath());
                if (
                    _file_address_path->is_open() == false ||
                    _file_command_path->is_open() == false ||
                    _file_commands_path->is_open() == false
                ) {
                _logger.log(
                        Logger::LogLevel::WARN, 
                        "Failed to open port files at: " + getAddressPath()
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
