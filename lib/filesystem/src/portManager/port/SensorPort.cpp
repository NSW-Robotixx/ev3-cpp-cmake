// #include <physical/portManager/port/SensorPort.hpp>
#include "./SensorPort.hpp"

namespace finder
{
    namespace physical
    {
        log4cplus::Logger SensorPort::_logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main.SensorPort"));
        
        std::vector<sensor_mode_t> SensorPort::_modes{};

        /*
        SensorPort::SensorPort(): Port()
        {
            _is_initialized = false;
        }
        */

        SensorPort::SensorPort(std::string port_name): Port(port_name)
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::SensorPort(std::string port_name)");

            if (port_name.length() <= 0) {
                LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("SensorPort created without port path"));
                throw new std::invalid_argument("SensorPort created without port path");
            }
            _is_initialized = false;
            _path = port_name;

            absl::Status success = initFiles();
            if (!success.ok())
            {
                LOG4CPLUS_ERROR(_logger, "Failed to initialize files");
                _path = "";
                throw new std::invalid_argument(std::string(success.message()));
            }
            _is_initialized = success.ok();
        }

        SensorPort::SensorPort(std::shared_ptr<Port> port): Port(port)
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::SensorPort(std::shared_ptr<Port> port)");
            absl::StatusOr<std::string> path = port->getBasePath();

            if (path.ok()) {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("Unable to get path from port: %s"), std::string(path.status().message()).c_str());
                throw new std::invalid_argument(std::string(path.status().message()));
            } else if (path.value().length() <= 0) {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("SensorPort created without port path : %s"), std::string(path.status().message()).c_str());
                throw new std::invalid_argument("SensorPort created without port path");
            }
            _is_initialized = false;
            
            absl::StatusOr<bool> success = initFiles();
            if (!success.ok())
            {
                LOG4CPLUS_ERROR(_logger, "Failed to initialize files");
                throw new std::invalid_argument(std::string(success.status().message()));
            }
            _is_initialized = success.value();
        }

        absl::Status SensorPort::setBasePath(const path_port_t& path)
        {
            absl::Status status = Port::setBasePath(path);
            if (!status.ok())
            {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("Failed to set path for port: %s"), path.c_str());
                return absl::InvalidArgumentError("Failed to set path for port: " + path);
            }
            absl::StatusOr<bool> success = initFiles();
            if (!success.ok())
            {
                LOG4CPLUS_ERROR(_logger, "Failed to initialize files");
                return success.status();
            }
            return status;
        }

        absl::StatusOr<path_value_t> SensorPort::getValuePath(int index)
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getValuePath()");

            if (isEnabled().value_or(false))
            {
                absl::StatusOr<std::string> path = getBasePath();
                if (!path.ok())
                {
                    LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Failed to get path"));
                    return path;
                }
                return path.value() + "/value" + std::to_string(index);
            }
            else
            {
                LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().value_or("").c_str());
                return absl::InvalidArgumentError("Port is not enabled: " + getBasePath().value_or(""));
            }
        }

        absl::StatusOr<path_mode_t> SensorPort::getModePath()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getModePath()");

            if (isEnabled().value_or(false))
            {
                absl::StatusOr<std::string> path = getBasePath();
                if (!path.ok())
                {
                    LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Failed to get path"));
                    return path;
                }
                return path.value() + "/mode";
            }
            else
            {
                LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().value_or("").c_str());
                return absl::InvalidArgumentError("Port is not enabled: " + getBasePath().value_or(""));
            }
        }

        absl::StatusOr<path_modes_t> SensorPort::getModesPath()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getModesPath()");
        
            if (isEnabled().value_or(false))
            {
                absl::StatusOr<std::string> path = getBasePath();
                if (!path.ok())
                {
                    LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Failed to get path"));
                    return path;
                }
                return path.value() + "/modes";
            }
            else
            {
                LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().value_or("").c_str());
                return absl::InvalidArgumentError("Port is not enabled: " + getBasePath().value_or(""));
            }
        }

        absl::StatusOr<path_num_values_t> SensorPort::getNumValuesPath()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getNumValuesPath()");

            if (isEnabled().value_or(false))
            {
                absl::StatusOr<std::string> path = getBasePath();
                if (!path.ok())
                {
                    LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Failed to get path"));
                    return path.status();
                }
                return path.value() + "/num_values";
            }
            else
            {
                LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().value_or("").c_str());
                return absl::InvalidArgumentError("Port is not enabled: " + getBasePath().value_or(""));
            }
        }

        absl::StatusOr<path_poll_ms_t> SensorPort::getPollMsPath()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getPollMsPath()");

            if (isEnabled().value_or(false))
            {
                absl::StatusOr<std::string> path = getBasePath();
                if (!path.ok())
                {
                    LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("Failed to get path"));
                    return "";
                }
                return path.value() + "/poll_ms";
            }
            else
            {
                LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().value_or("").c_str());
                return absl::InvalidArgumentError("Port is not enabled: " + getBasePath().value_or(""));
            }
        }

        absl::StatusOr<int> SensorPort::getValue(int index)
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getValue()");

            if (isEnabled().value_or(false))
            {
                if (index < 0 || index >= _file_value_path.size())
                {
                    LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Index out of range for %s"), getBasePath().value_or("").c_str());
                    return absl::OutOfRangeError("Index out of range");
                }
                
                if (_file_value_path[index]->is_open())
                {
                    int value;
                    *_file_value_path[index] >> value;
                    LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("VALUE.GET: %s WITH_RESULT: %d"), getBasePath().value_or("").c_str(), value);
                    return value;
                } 
            } 
            LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().value_or("").c_str());
            return absl::InvalidArgumentError("Port is not enabled: " + getBasePath().value_or(""));
        }

        absl::Status SensorPort::setMode(sensor_mode_t mode)
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::setMode()");

            if (isEnabled().value_or(false))
            {
                if (_file_mode_path->is_open())
                {
                    *_file_mode_path << mode;
                    _file_mode_path->flush();
                }
                LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("MODE.SET: %s WITH_VALUE: %s"), getBasePath().value_or("").c_str(), mode.c_str());
                return absl::OkStatus();
            }
            LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().value_or("").c_str());
            return absl::InvalidArgumentError("Port is not enabled: " + getBasePath().value_or(""));
        }

        std::vector<sensor_mode_t> SensorPort::getModes()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getModes()");

            // read modes from file into vector
            if (isEnabled().value_or(false))
            {
                if (_file_modes_path->is_open())
                {
                    std::string mode;
                    _modes.clear();
                    while (*_file_modes_path >> mode)
                    {
                        _modes.push_back(mode);
                    }
                    _modes = _modes;
                    for (auto m : _modes)
                    {
                        LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("MODES.GET: %s WITH_RESULT: %s"), getBasePath().value_or("").c_str(), m.c_str());
                    }
                }
                return _modes;
            }
            LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().value_or("").c_str());
            return std::vector<sensor_mode_t>{};
        }

        absl::StatusOr<int> SensorPort::getNumValues()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getNumValues()");

            if (isEnabled().value_or(false))
            {
                if (_file_num_values_path->is_open())
                {
                    int num_values;
                    *_file_num_values_path >> num_values;
                    LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("NUM_VALUES.GET: %s WITH_RESULT: %d"), getBasePath().value_or("").c_str(), num_values);
                    return num_values;
                }
            }
            LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().value_or("").c_str());
            return absl::InvalidArgumentError("Port is not enabled: " + getBasePath().value_or(""));
        }

        int SensorPort::getPollMs()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getPollMs()");

            if (isEnabled().value_or(false))
            {
                if (_file_poll_ms_path->is_open())
                {
                    int poll_ms;
                    *_file_poll_ms_path >> poll_ms;
                    LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("POLL_MS.GET: %s WITH_RESULT: %d"), getBasePath().value_or("").c_str(), poll_ms);
                    return poll_ms;
                }
            }
            LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().value_or("").c_str());
            return -1;
        }

        absl::StatusOr<DeviceType> SensorPort::getDeviceType()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getDeviceType()");

            absl::StatusOr<DeviceType> device_type = Port::getDeviceType();
            if (device_type.ok() && device_type.value() != DeviceType::SENSOR) {
                LOG4CPLUS_ERROR(_logger, "SensorPort::getDeviceType() called on non-sensor port");
                return absl::InvalidArgumentError("SensorPort::getDeviceType() called on non-sensor port");
            } else {
                LOG4CPLUS_DEBUG(_logger, "Device type is SENSOR");
            }
            return DeviceType::SENSOR;
        }
        absl::Status SensorPort::initFiles()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::initFiles()");

            absl::Status full_success;

            // open files
            for (int i = 0; i < 10; i++)
            {
                absl::StatusOr<std::string> value_path = getValuePath(i);
                if (!value_path.ok())
                {
                    LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("Failed to get value path for %d"), i);
                    full_success.Update(value_path.status());
                    continue;
                }
                _file_value_path.push_back(std::make_shared<std::ifstream>(value_path.value()));
                if (!_file_value_path[i]->fail())
                {
                    if (!_file_value_path[i]->is_open())
                    {
                        LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Failed to open value0 file at: %s"), value_path.value().c_str());
                        _file_value_path[i].reset();
                        full_success.Update(absl::InvalidArgumentError("Failed to open value0 file: " + value_path.value()));
                    }
                    else
                    {
                        LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened value0 file at: %s"), value_path.value().c_str());
                    }
                }
                else
                {
                    LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), value_path.value().c_str());
                    full_success.Update(absl::InvalidArgumentError("File does not exist: " + value_path.value()));
                }
            }  

            absl::StatusOr<std::string> mode_path = getModePath();
            if (!mode_path.ok())
            {
                LOG4CPLUS_ERROR(_logger, "Failed to get mode path");
                full_success.Update(mode_path.status());
            }
            _file_mode_path = std::make_shared<std::ofstream>(mode_path.value());
            absl::StatusOr<std::string> modes_path = getModesPath();
            if (!modes_path.ok())
            {
                LOG4CPLUS_ERROR(_logger, "Failed to get modes path");
                full_success.Update(modes_path.status());
            }
            _file_modes_path = std::make_shared<std::ifstream>(modes_path.value());
            absl::StatusOr<std::string> num_values_path = getNumValuesPath();
            if (!num_values_path.ok())
            {
                LOG4CPLUS_ERROR(_logger, "Failed to get num values path");
                full_success.Update(num_values_path.status());
            }
            _file_num_values_path = std::make_shared<std::ifstream>(num_values_path.value());
            absl::StatusOr<std::string> poll_ms_path = getPollMsPath();
            if (!poll_ms_path.ok())
            {
                LOG4CPLUS_ERROR(_logger, "Failed to get poll ms path");
                full_success.Update(poll_ms_path.status());
            }
            _file_poll_ms_path = std::make_shared<std::ifstream>(poll_ms_path.value());

            // check if mode path is opened
            if (!_file_mode_path->fail()) {
                if (!_file_mode_path->is_open()) {
                    LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Failed to open value0 file at: %s"), mode_path.value().c_str());
                    _file_mode_path.reset();
                    full_success.Update(absl::InvalidArgumentError("Failed to open value0 file: " + mode_path.value()));
                } else {
                    LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened mode file at: %s"), mode_path.value().c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), mode_path.value().c_str());
                full_success.Update(absl::InvalidArgumentError("File does not exist: " + mode_path.value()));
            }

            // check if modes path is opened
            if (!_file_modes_path->fail()) {
                if (!_file_modes_path->is_open()) {
                    LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Failed to open value0 file at: %s"), modes_path.value().c_str());
                    _file_modes_path.reset();
                    full_success.Update(absl::InvalidArgumentError("Failed to open value0 file: " + modes_path.value()));
                } else {
                    LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened modes file at: %s"), modes_path.value().c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), modes_path.value().c_str());
                full_success.Update(absl::InvalidArgumentError("File does not exist: " + modes_path.value()));
            }

            // check if num_values path is opened
            if (!_file_num_values_path->fail()) {
                if (!_file_num_values_path->is_open()) {
                    LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Failed to open value0 file at: %s"), num_values_path.value().c_str());
                    _file_num_values_path.reset();
                    full_success.Update(absl::InvalidArgumentError("Failed to open value0 file: " + num_values_path.value()));
                } else {
                    LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened num_values file at: %s"), num_values_path.value().c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), num_values_path.value().c_str());
                full_success.Update(absl::InvalidArgumentError("File does not exist: " + num_values_path.value()));
            }

            // check if poll_ms path is opened
            if (!_file_poll_ms_path->fail()) {
                if (!_file_poll_ms_path->is_open()) {
                    LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Failed to open value0 file at: %s"), poll_ms_path.value().c_str());
                    _file_poll_ms_path.reset();
                    full_success.Update(absl::InvalidArgumentError("Failed to open value0 file: " + poll_ms_path.value()));
                } else {
                    LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened poll_ms file at: %s"), poll_ms_path.value().c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), poll_ms_path.value().c_str());
                full_success.Update(absl::InvalidArgumentError("File does not exist: " + poll_ms_path.value()));
            }

            return full_success;
        }

    } // namespace physical
    
} // namespace finder
