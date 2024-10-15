#include "Port.hpp"

namespace finder
{
    namespace physical
    {
        log4cplus::Logger Port::_logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main.Port"));

        Port::Port(const path_port_t &port)
        {
            LOG4CPLUS_TRACE(_logger, "Port::Port(const path_port_t &port)");
            absl::Status status = setBasePath(port);
            if (!status.ok()) {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("Failed to set path for port: %s"), port.c_str());
                throw status;
            }
        }

        Port::Port(std::shared_ptr<Port> port)
        {
            LOG4CPLUS_TRACE(_logger, "Port::Port(std::shared_ptr<Port> port)");
            absl::StatusOr<std::string> path = port->getBasePath();

            if (path.ok()) {
                absl::Status status = setBasePath(path.value());
                if (!status.ok()) {
                    LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("Failed to set path for port: %s"), path.value().c_str());
                    throw status;
                }
            } else {
                LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Failed to get path from port"));
                throw std::invalid_argument("Invalid port path");
            }
        }

        Port::~Port()
        {
        }

        absl::Status Port::setBasePath(const path_port_t &path)
        {
            LOG4CPLUS_TRACE(_logger, "Port::setBasePath()");

            if (path.empty()) {
                LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Port path is empty"));
                return absl::InvalidArgumentError("Port path is empty");
            }

            _path = path;
            if (initFiles().ok()) {
                _f_enabled = true;
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("Failed to initialize files for port: %s"), _path.c_str());
                _f_enabled = false;
                _path.clear();
                return absl::InvalidArgumentError("Failed to initialize files for port: " + _path);
            }
            return absl::OkStatus();
        }
        
        absl::StatusOr<path_port_t> Port::getBasePath()
        {
            // LOG4CPLUS_TRACE(_logger, "Port::getBasePath()");

            if (isEnabled().value_or(false)) {
                return _path;
            }
            LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled: %s"), _path.c_str());
            return absl::InvalidArgumentError("Port is not enabled: " + _path);
        }

        absl::StatusOr<path_address_t> Port::getAddressPath()
        {
            LOG4CPLUS_TRACE(_logger, "Port::getAddressPath()");

            if (isEnabled().value_or(false)) {
                return _path + "/address";
            }
            LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
            return absl::InvalidArgumentError("Port is not enabled: " + _path);
        }

        absl::StatusOr<path_address_t> Port::getAddressPath(const path_port_t &path)
        {
            LOG4CPLUS_TRACE(_logger, "Port::getAddressPath()");

            if (path.empty()) {
                LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Port path is empty"));
                return absl::InvalidArgumentError("Port path is empty");
            }

            return path_address_t(path + "/address");
        }

        absl::StatusOr<path_command_t> Port::getCommandPath()
        {
            LOG4CPLUS_TRACE(_logger, "Port::getCommandPath()");

            if (isEnabled().value_or(false)) {
                return _path + "/command";
            }
            LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
            return absl::InvalidArgumentError("Port is not enabled: " + _path);
        }

        absl::StatusOr<path_commands_t> Port::getCommandsPath()
        {
            LOG4CPLUS_TRACE(_logger, "Port::getCommandsPath()");

            if (isEnabled().value_or(false)) {
                return _path + "/commands";
            }
            LOG4CPLUS_WARN(_logger, LOG4CPLUS_TEXT("Port is not enabled"));
            return absl::InvalidArgumentError("Port is not enabled: " + _path);
        }

        absl::StatusOr<std::string> Port::getAddress()
        {   
            LOG4CPLUS_TRACE(_logger, "Port::getAddress()");
            LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("Getting address for port: %s"), _path.c_str());

            if (isEnabled().value_or(false)) {
                std::string address;
                *_file_address_path >> address;
                LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("Address: %s"), address.c_str());
                return address;
            }
            LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Failed to get address, port is not enabled"));
            return absl::InvalidArgumentError("Failed to get address, port is not enabled");
        }

        absl::Status Port::setCommand(std::string command)
        {
            LOG4CPLUS_TRACE(_logger, "Port::setCommand()");
            LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("Setting command for port: %s"), _path.c_str());

            if (isEnabled().value_or(false)) {
                *_file_command_path << command;
                LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("Command set: %s"), command.c_str());
                return absl::OkStatus();
            }
            LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Failed to set command, port is not enabled"));
            return absl::InvalidArgumentError("Failed to set command, port is not enabled");
        }

        absl::StatusOr<std::vector<std::string>> Port::getCommands()
        {
            LOG4CPLUS_TRACE(_logger, "Port::getCommands()");
            LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("Getting commands for port: %s"), _path.c_str());

            if (isEnabled().value_or(false)) {
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
            LOG4CPLUS_ERROR(_logger, ("Failed to get commands, port is not enabled"));
            return absl::InvalidArgumentError("Failed to get commands, port is not enabled");
        }

        absl::StatusOr<DeviceType> Port::getDeviceType()
        {
            LOG4CPLUS_TRACE(_logger, "Port::getDeviceType()");

            if (isEnabled().value_or(false)) {
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

        absl::Status Port::initFiles()
        {
            LOG4CPLUS_TRACE(_logger, "Port::initFiles()");

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
                    return absl::InvalidArgumentError("Failed to open address file: " + address_path);
                } else {
                    LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened address file at: %s"), address_path.c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), address_path.c_str());
                return absl::InvalidArgumentError("File does not exist: " + address_path);
            }

            // check if command file is opened
            if (!_file_command_path->fail()) {
                if (!_file_command_path->is_open()) {
                    LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Failed to open command file at: %s"), command_path.c_str());
                    _file_command_path.reset();
                    return absl::InvalidArgumentError("Failed to open command file: " + command_path);
                } else {
                    LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened command file at: %s"), command_path.c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), command_path.c_str());
                return absl::InvalidArgumentError("File does not exist: " + command_path);
            }

            // check if commands file is opened
            if (!_file_commands_path->fail()) {
                if (!_file_commands_path->is_open()) {
                    LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Failed to open commands file at: %s"), commands_path.c_str());
                    _file_commands_path.reset();
                    return absl::InvalidArgumentError("Failed to open commands file: " + commands_path);
                } else {
                    LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened commands file at: %s"), commands_path.c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), commands_path.c_str());
                return absl::InvalidArgumentError("File does not exist: " + commands_path);
            }
            LOG4CPLUS_INFO(_logger, LOG4CPLUS_TEXT("All files opened successfully"));
            return absl::OkStatus();
        }

        inline absl::StatusOr<bool> Port::isEnabled()
        {
            return _f_enabled;
        }
    } // namespace physical
} // namespace finder
