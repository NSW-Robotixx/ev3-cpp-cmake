#include "Port.hpp"

namespace finder
{
    namespace physical
    {
#ifdef ENABLE_LOGGING
        ::finder::log::Logger Port::_logger = ::finder::log::Logger{};
#endif
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
                // _logger.log(
                //     ::finder::console::Logger::LogLevel::WARN, 
                //     "Port path is empty"
                // );
                throw std::invalid_argument("Port path is empty");
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

        path_address_t Port::getAddressPath(const path_port_t &path)
        {
            return path_address_t(path + "/address");
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
#ifdef ENABLE_LOGGING
            FileLoggerLock lock = FileLoggerLock();
            logToFile("ADDRESS.GET: " + _path);
#endif            
            if (isEnabled()) {
                std::string address;
                *_file_address_path >> address;
#ifdef ENABLE_LOGGING
                logToFile(" WITH RESULT: " + address);
#endif
                return address;
            }
            return "";
        }

        bool Port::setCommand(std::string command)
        {
#ifdef ENABLE_LOGGING
            FileLoggerLock lock = FileLoggerLock();
            logToFile("COMMAND.SET: " + command + " TO: " + _path);
#endif            

            if (isEnabled()) {
                *_file_command_path << command;
                return true;
            }
            return false;
        }

        std::vector<std::string> Port::getCommands()
        {
#ifdef ENABLE_LOGGING
            FileLoggerLock lock = FileLoggerLock();
            logToFile("COMMANDS.GET: " + _path);
#endif            
            if (isEnabled()) {
                std::vector<std::string> commands;
                std::string command_total;
                // split by space and store in vector
                *_file_commands_path >> command_total;
                std::istringstream iss(command_total);
                std::string command;
                while (iss >> command) {
                    commands.push_back(command);
#ifdef ENABLE_LOGGING
                    logToFile(" WITH_RESULT: " + command);
#endif
                }
                return commands;
            }
            return {};
        }

        DeviceType Port::getDeviceType()
        {
#ifdef ENABLE_LOGGING
            _logger.debug(
                "Checking device type for port: " + _path
            );
#endif
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
            bool full_success = true;

            std::string address_path = _path + "/address";
            std::string command_path = _path + "/command";
            std::string commands_path = _path + "/commands";

            _file_address_path = std::make_shared<std::ifstream>(address_path);
            _file_command_path = std::make_shared<std::ofstream>(command_path);
            _file_commands_path = std::make_shared<std::ifstream>(commands_path);

            // check if address file is opened
            if (!_file_address_path->fail()) {
                if (!_file_address_path->is_open()) {
#ifdef ENABLE_LOGGING                    
                    _logger.warn("Failed to open address file at: " + address_path);
#endif                    
                    _file_address_path.reset();
                    full_success = false;
                } else {
#ifdef ENABLE_LOGGING                    
                    _logger.success("Opened address file at: " + address_path);
#endif                    
                }
            } else {
#ifdef ENABLE_LOGGING                
                _logger.error("File does not exist at: " + address_path);
#endif                
                full_success = false;
            }

            // check if command file is opened
            if (!_file_command_path->fail()) {
                if (!_file_command_path->is_open()) {
#ifdef ENABLE_LOGGING                    
                    _logger.warn("Failed to open command file at: " + command_path);
#endif                    
                    _file_command_path.reset();
                    full_success = false;
                } else {
#ifdef ENABLE_LOGGING                    
                    _logger.success("Opened command file at: " + command_path);
#endif                    
                }
            } else {
#ifdef ENABLE_LOGGING                
                _logger.error("File does not exist at: " + command_path);
#endif                
                full_success = false;
            }

            // check if commands file is opened
            if (!_file_commands_path->fail()) {
                if (!_file_commands_path->is_open()) {
#ifdef ENABLE_LOGGING                    
                    _logger.warn("Failed to open commands file at: " + commands_path);
#endif                    
                    _file_commands_path.reset();
                    full_success = false;
                } else {
#ifdef ENABLE_LOGGING                    
                    _logger.success("Opened commands file at: " + commands_path);
#endif                    
                }
            } else {
#ifdef ENABLE_LOGGING                
                _logger.error("File does not exist at: " + commands_path);
#endif                
                full_success = false;
            }

            return full_success;
        }

        bool Port::isEnabled()
        {
            if (this == nullptr) {
                throw std::invalid_argument("Port is nullptr");
            }
            return _f_enabled;
        }
    } // namespace physical
} // namespace finder
