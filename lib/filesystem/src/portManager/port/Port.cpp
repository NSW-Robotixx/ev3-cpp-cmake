#include "Port.hpp"

namespace finder
{
    namespace physical
    {
        log4cplus::Logger Port::_logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main.Port"));

        Port::Port(const path_port_t &port)
        {
            log4cplus::SharedAppenderPtr _appender(new log4cplus::ConsoleAppender());
            _appender->setName(LOG4CPLUS_TEXT("console"));
            _logger.addAppender(_appender);

            LOG4CPLUS_TRACE(_logger, "Port::Port(const path_port_t &port)");
            setBasePath(port);
        }

        Port::Port(std::shared_ptr<Port> port)
        {
            log4cplus::SharedAppenderPtr _appender(new log4cplus::ConsoleAppender());
            _appender->setName(LOG4CPLUS_TEXT("console"));
            _logger.addAppender(_appender);

            LOG4CPLUS_TRACE(_logger, "Port::Port(std::shared_ptr<Port> port)");
            setBasePath(port->getBasePath());
        }

        Port::~Port()
        {
        }

        void Port::setBasePath(const path_port_t &path)
        {
            LOG4CPLUS_TRACE(_logger, "Port::setBasePath()");

            if (path.empty()) {
                LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Port path is empty"));
                    
                throw std::invalid_argument("Port path is empty");
                return;
            }
            _path = path;
            _f_enabled = initFiles();
        }
        
        path_port_t Port::getBasePath()
        {
            // LOG4CPLUS_TRACE(_logger, "Port::getBasePath()");

            if (isEnabled()) {
                return _path;
            }
            LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled: %s"), _path.c_str());
            return "";
        }

        path_address_t Port::getAddressPath()
        {
            LOG4CPLUS_TRACE(_logger, "Port::getAddressPath()");

            if (isEnabled()) {
                return _path + "/address";
            }
            LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
            return "";
        }

        path_address_t Port::getAddressPath(const path_port_t &path)
        {
            LOG4CPLUS_TRACE(_logger, "Port::getAddressPath()");

            return path_address_t(path + "/address");
        }

        path_command_t Port::getCommandPath()
        {
            LOG4CPLUS_TRACE(_logger, "Port::getCommandPath()");

            if (isEnabled()) {
                return _path + "/command";
            }
            LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
            return "";
        }

        path_commands_t Port::getCommandsPath()
        {
            LOG4CPLUS_TRACE(_logger, "Port::getCommandsPath()");

            if (isEnabled()) {
                return _path + "/commands";
            }
            LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
            return "";
        }

        std::string Port::getAddress()
        {   
            LOG4CPLUS_TRACE(_logger, "Port::getAddress()");
            LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("Getting address for port: %s"), _path.c_str());

            if (isEnabled()) {
                std::string address;
                *_file_address_path >> address;
                LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("Address: %s"), address.c_str());
                return address;
            }
            LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Failed to get address, port is not enabled"));
            return "";
        }

        bool Port::setCommand(std::string command)
        {
            LOG4CPLUS_TRACE(_logger, "Port::setCommand()");
            LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("Setting command for port: %s"), _path.c_str());

            if (isEnabled()) {
                *_file_command_path << command;
                LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("Command set: %s"), command.c_str());
                return true;
            }
            LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Failed to set command, port is not enabled"));
            return false;
        }

        std::vector<std::string> Port::getCommands()
        {
            LOG4CPLUS_TRACE(_logger, "Port::getCommands()");
            LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("Getting commands for port: %s"), _path.c_str());

            if (isEnabled()) {
                std::vector<std::string> commands;
                std::string command_total;
                // split by space and store in vector
                *_file_commands_path >> command_total;
                std::istringstream iss(command_total);
                std::string command;
                while (iss >> command) {
                    LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("Command: %s"), command.c_str());
                    commands.push_back(command);
                }
                return commands;
            }
            LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Failed to get commands, port is not enabled"));
            return {};
        }

        DeviceType Port::getDeviceType()
        {
            LOG4CPLUS_TRACE(_logger, "Port::getDeviceType()");

            if (isEnabled()) {
                if (_path.find("sensor") != std::string::npos) {
                    LOG4CPLUS_DEBUG(_logger, LOG4CPLUS_TEXT("Device type is SENSOR"));
                    return DeviceType::SENSOR;
                } else if (_path.find("motor") != std::string::npos) {
                    LOG4CPLUS_DEBUG(_logger, LOG4CPLUS_TEXT("Device type is MOTOR"));
                    return DeviceType::MOTOR;
                } else {
                    LOG4CPLUS_DEBUG(_logger, LOG4CPLUS_TEXT("Device type is UNKNOWN"));
                    return DeviceType::UNKNOWN;
                }
            }
            LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Failed to get device type, port is not enabled"));
            return DeviceType::DISABLED;
        }

        bool Port::initFiles()
        {
            LOG4CPLUS_TRACE(_logger, "Port::initFiles()");
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
                    LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Failed to open address file at: %s"), address_path.c_str());
                    _file_address_path.reset();
                    full_success = false;
                } else {
                    LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened address file at: %s"), address_path.c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), address_path.c_str());
                full_success = false;
            }

            // check if command file is opened
            if (!_file_command_path->fail()) {
                if (!_file_command_path->is_open()) {
                    LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Failed to open command file at: %s"), command_path.c_str());
                    _file_command_path.reset();
                    full_success = false;
                } else {
                    LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened command file at: %s"), command_path.c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), command_path.c_str());
                full_success = false;
            }

            // check if commands file is opened
            if (!_file_commands_path->fail()) {
                if (!_file_commands_path->is_open()) {
                    LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Failed to open commands file at: %s"), commands_path.c_str());
                    _file_commands_path.reset();
                    full_success = false;
                } else {
                    LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened commands file at: %s"), commands_path.c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), commands_path.c_str());
                full_success = false;
            }
            if (!full_success) {
                LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Failed to initialize files"));
            }
            return full_success;
        }

        inline bool Port::isEnabled()
        {
            // LOG4CPLUS_TRACE(_logger, "Port::isEnabled()");

            if (this == nullptr) {
                LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Port is nullptr"));
                throw std::invalid_argument("Port is nullptr");
            }
            // LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Port is enabled: %s"), _f_enabled ? "true" : "false");
            return _f_enabled;
        }
    } // namespace physical
} // namespace finder
