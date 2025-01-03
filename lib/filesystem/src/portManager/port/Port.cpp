#include "Port.hpp"

#include "../../EV3_conf.hpp"

namespace finder
{
    namespace physical
    {
        Port::Port(const path_port_t &port)
        {
            spdlog::trace("Port::Port(const path_port_t &port)");
            boost::leaf::result<void> status = setBasePath(port);
            if (!status) {
                spdlog::error(fmt::format("Failed to set path for port: %s", port.c_str()));
                // if constexpr (EV3_THROW_ON_ERROR) { throw status.error(); }
            }
        }

        Port::Port(std::shared_ptr<Port> port)
        {
            spdlog::trace("Port::Port(std::shared_ptr<Port> port)");
            boost::leaf::result<std::string> path = port->getBasePath();

            if (path) {
                boost::leaf::result<void> status = setBasePath(path.value());
                if (!status) {
                    spdlog::error(fmt::format("Failed to set path for port: %s", path.value().c_str()));
                    throw status;
                }
            } else {
                spdlog::error("Failed to get path from port");
                throw std::invalid_argument("Invalid port path");
            }
        }

        Port::~Port()
        {
        }

        boost::leaf::result<void> Port::setBasePath(const path_port_t &path)
        {
            spdlog::trace("Port::setBasePath()");

            if (path.empty()) {
                spdlog::error("Port path is empty");
                return boost::leaf::new_error(std::invalid_argument("Port path is empty"));
            }

            _path = path;
            if (initFiles()) {
                _f_enabled = true;
            } else {
                spdlog::error(fmt::format("Failed to initialize files for port: %s", _path.c_str()));
                _f_enabled = false;
                _path.clear();
                return boost::leaf::new_error(std::invalid_argument("Failed to initialize files for port: " + _path));
            }
            return boost::leaf::result<void>();
        }

        boost::leaf::result<void> Port::reinit()
        {
            _file_address_path.reset();
            _file_command_path.reset();
            _file_commands_path.reset();

            return initFiles();
        }

        boost::leaf::result<path_port_t> Port::getBasePath()
        {
            // spdlog::trace("Port::getBasePath()");

            if (isEnabled() && isEnabled().value()) {
                return _path;
            }
            spdlog::warn(("Port is not enabled: %s"), _path.c_str());
            return boost::leaf::new_error(std::runtime_error(""));

        }

        boost::leaf::result<path_address_t> Port::getAddressPath()
        {
            spdlog::trace("Port::getAddressPath()");

            if (isEnabled() && isEnabled().value()) {
                return _path + "/address";
            }
            spdlog::warn("Port is not enabled");
            return boost::leaf::new_error(std::invalid_argument("Failed to get Address, port ist not enabled"));
        }

        boost::leaf::result<path_address_t> Port::getAddressPath(const path_port_t &path)
        {
            spdlog::trace("Port::getAddressPath()");

            if (path.empty()) {
                spdlog::error("Port path is empty");
                return boost::leaf::new_error(std::invalid_argument("Port path is empty"));
            }

            return path_address_t(path + "/address");
        }

        boost::leaf::result<path_command_t> Port::getCommandPath()
        {
            spdlog::trace("Port::getCommandPath()");

            if (isEnabled() && isEnabled().value()) {
                return _path + "/command";
            }
            spdlog::warn("Port is not enabled");
            return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
        }

        boost::leaf::result<path_commands_t> Port::getCommandsPath()
        {
            spdlog::trace("Port::getCommandsPath()");

            if (isEnabled() && isEnabled().value()) {
                return _path + "/commands";
            }
            spdlog::warn("Port is not enabled");
            return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
        }

        boost::leaf::result<std::string> Port::getAddress()
        {   
            spdlog::trace("Port::getAddress()");
            spdlog::debug(fmt::format("Getting address for port: {}", _path));

            if (isEnabled() && isEnabled().value()) {
                std::string address;
                *_file_address_path >> address;
                spdlog::debug(fmt::format("Address: {}", address));
                return address;
            }
            spdlog::error("Failed to get address, port is not enabled");
            return boost::leaf::new_error(std::invalid_argument("Failed to get address, port is not enabled"));
        }

        boost::leaf::result<void> Port::setCommand(std::string command)
        {
            spdlog::trace("Port::setCommand()");
            spdlog::debug(fmt::format("Setting command: {}", command));

            if (isEnabled() && isEnabled().value()) {
                *_file_command_path << command;
                spdlog::debug(fmt::format("Command set: {}", command));
                return boost::leaf::result<void>();
            }
            spdlog::error("Failed to set command, port is not enabled");
            return boost::leaf::new_error(std::invalid_argument("Failed to set command, port is not enabled"));
        }

        boost::leaf::result<std::vector<std::string>> Port::getCommands()
        {
            spdlog::trace("Port::getCommands()");
            spdlog::info(("Getting commands for port: %s"), _path.c_str());

            if (isEnabled() && isEnabled().value()) {
                std::vector<std::string> commands;
                std::string command_total;
                // split by space and store in vector
                *_file_commands_path >> command_total;
                std::istringstream iss(command_total);
                std::string command;
                while (iss >> command) {
                    spdlog::info(("Command: %s"), command.c_str());
                    commands.push_back(command);
                }
                return commands;
            }
            spdlog::error("Failed to get commands, port is not enabled");
            return boost::leaf::new_error(std::invalid_argument("Failed to get commands, port is not enabled"));
        }

        boost::leaf::result<DeviceType> Port::getDeviceType()
        {
            spdlog::trace("Port::getDeviceType()");

            if (isEnabled() && isEnabled().value()) {
                if (_path.find("sensor") != std::string::npos) {
                    spdlog::debug("Device type is SENSOR");
                    return DeviceType::SENSOR;
                } else if (_path.find("motor") != std::string::npos) {
                    spdlog::debug("Device type is MOTOR");
                    return DeviceType::MOTOR;
                } else {
                    spdlog::debug("Device type is UNKNOWN");
                    return DeviceType::UNKNOWN;
                }
            }
            spdlog::error("Failed to get device type, port is not enabled");
            return DeviceType::DISABLED;
        }

        boost::leaf::result<DriverName> Port::getDriverName()
        {
            spdlog::trace("Port::getDriverName()");

            if (isEnabled() && isEnabled().value()) {
                if (_file_driver_name_path->good()) {
                    std::string driver_name;

                    _file_driver_name_path->seekg(0);
                    *_file_driver_name_path >> driver_name;
                    
                    spdlog::info(fmt::format("Driver name: {}", driver_name));
                    
                    if (driver_name == "lego-ev3-gyro") {
                        return DriverName::SENSOR_GYRO;
                    } else if (driver_name == "lego-ev3-color") {
                        return DriverName::SENSOR_COLOR;
                    } else if (driver_name == "lego-ev3-us") {
                        return DriverName::SENSOR_ULTRASONIC;
                    } else if (driver_name == "lego-ev3-l-motor") {
                        return DriverName::MOTOR_LARGE;
                    } else if (driver_name == "lego-ev3-m-motor") {
                        return DriverName::MOTOR_MEDIUM;
                    } else {
                        spdlog::error(fmt::format("Unknown driver name: {}", driver_name));
                        return boost::leaf::new_error(std::invalid_argument("Unknown driver name: " + driver_name));
                    }
                }
            }
            spdlog::error("Failed to get driver name, port is not enabled");
            return boost::leaf::new_error(std::invalid_argument("Failed to get driver name, port is not enabled"));
        }

        boost::leaf::result<void> Port::initFiles()
        {
            spdlog::trace("Port::initFiles()");

            std::string address_path = _path + "/address";
            std::string command_path = _path + "/command";
            std::string commands_path = _path + "/commands";
            std::string driver_name_path = _path + "/driver_name";

            _file_address_path = std::make_shared<std::ifstream>(address_path);
            _file_command_path = std::make_shared<std::ofstream>(command_path);
            _file_commands_path = std::make_shared<std::ifstream>(commands_path);
            _file_driver_name_path = std::make_shared<std::ifstream>(driver_name_path);

            // check if address file is opened
            if (!_file_address_path->fail()) {
                if (!_file_address_path->is_open()) {
                    spdlog::warn("Failed to open address file at: {}", address_path);
                    _file_address_path.reset();
                    return boost::leaf::new_error(std::invalid_argument("Failed to open address file: " + address_path));
                } else {
                     spdlog::debug("Opened address file at: {}", address_path);
                }
            } else {
                spdlog::error(fmt::format("File does not exist at: {}", address_path));
                return boost::leaf::new_error(std::invalid_argument("File does not exist: " + address_path));
            }

            // check if command file is opened
            if (!_file_command_path->fail()) {
                if (!_file_command_path->is_open()) {
                    spdlog::error("Failed to open command file at: {}", command_path.c_str());
                    _file_command_path.reset();
                    return boost::leaf::new_error(std::invalid_argument("Failed to open command file: " + command_path));
                } else {
                    spdlog::debug("Opened command file at: {}", command_path.c_str());
                }
            } else {
                spdlog::error(fmt::format("File does not exist at: {}", command_path.c_str()));
                return boost::leaf::new_error(std::invalid_argument("File does not exist: " + command_path));
            }

            // check if commands file is opened
            if (!_file_commands_path->fail()) {
                if (!_file_commands_path->is_open()) {
                    spdlog::warn("Failed to open commands file at: {}", commands_path.c_str());
                    _file_commands_path.reset();
                    return boost::leaf::new_error(std::invalid_argument("Failed to open commands file: " + commands_path));
                } else {
                    spdlog::debug("Opened commands file at: {}", commands_path.c_str());
                }
            } else {
                spdlog::error(fmt::format("File does not exist at: {}", commands_path.c_str()));
                return boost::leaf::new_error(std::invalid_argument("File does not exist: " + commands_path));
            }

            // check if driver name file is opened
            if (!_file_driver_name_path->fail()) {
                if (!_file_driver_name_path->is_open()) {
                    spdlog::warn("Failed to open driver name file at: {}", driver_name_path.c_str());
                    _file_driver_name_path.reset();
                    return boost::leaf::new_error(std::invalid_argument("Failed to open driver name file: " + driver_name_path));
                } else {
                    spdlog::debug("Opened driver name file at: {}", driver_name_path.c_str());
                }
            } else {
                spdlog::error(fmt::format("File does not exist at: {}", driver_name_path.c_str()));
                return boost::leaf::new_error(std::invalid_argument("File does not exist: " + driver_name_path));
            }

            spdlog::info("All files opened successfully");

            return boost::leaf::result<void>();
        }

        boost::leaf::result<bool> Port::isEnabled()
        {
            boost::call_once(_init_flag, &Port::initFiles, this);

            return _f_enabled;
        }
    } // namespace physical
} // namespace finder
