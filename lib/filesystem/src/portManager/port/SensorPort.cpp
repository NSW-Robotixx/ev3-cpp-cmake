// #include <physical/portManager/port/SensorPort.hpp>
#include "./SensorPort.hpp"
#include "SensorPort.hpp"

namespace finder
{
    namespace physical
    {
        std::vector<sensor_mode_t> SensorPort::_modes{};

        /*
        SensorPort::SensorPort(): Port()
        {
            _is_initialized = false;
        }
        */

        SensorPort::SensorPort(std::string port_name): Port(port_name)
        {
            spdlog::trace("SensorPort::SensorPort(std::string port_name)");

            if (port_name.length() <= 0) {
                spdlog::error("SensorPort created without port path");
                throw new std::invalid_argument("SensorPort created without port path");
            }
            _is_initialized = false;
            _path = port_name;

            boost::leaf::result<void> success = initFiles();
            if (!success)
            {
                spdlog::error("Failed to initialize files");
                _path = "";
                // throw success.error();
            } else
            {
                _is_initialized = true;
            }
        }

        SensorPort::SensorPort(std::shared_ptr<Port> port): Port(port)
        {
            spdlog::trace("SensorPort::SensorPort(std::shared_ptr<Port> port)");
            boost::leaf::result<std::string> path = port->getBasePath();

            if (!path) {
                spdlog::error("Unable to get path from port");
                throw path.error();
            } else if (path.value().length() <= 0) {
                spdlog::error("SensorPort created without port path");
                throw new std::invalid_argument("SensorPort created without port path");
            }
            _is_initialized = false;
            
            boost::leaf::result<void> success = initFiles();
            if (!success)
            {
                spdlog::error("Failed to initialize files");
                // throw success.error();
            } else {
                _is_initialized = true;
            }
        }

        boost::leaf::result<void> SensorPort::setBasePath(const path_port_t& path)
        {
            boost::leaf::result<void> status = Port::setBasePath(path);
            if (!status)
            {
                spdlog::error("Failed to set path for port: %s", path.c_str());
                return boost::leaf::new_error(std::invalid_argument("Failed to set path for port: " + path));
            }
            boost::leaf::result<void> success = initFiles();
            if (!success)
            {
                spdlog::error("Failed to initialize files");
                return success.error();
            }
            return status;
        }

        boost::leaf::result<void> SensorPort::reinit()
        {
            _file_address_path.reset();
            _file_command_path.reset();
            _file_commands_path.reset();
            _file_mode_path.reset();
            _file_modes_path.reset();
            _file_num_values_path.reset();
            _file_poll_ms_path.reset();
            
            for (auto& file : _file_value_path)
            {
                file.reset();
            }

            _file_value_path.clear();

            return initFiles();
        }

        boost::leaf::result<path_value_t> SensorPort::getValuePath(int index)
        {
            spdlog::trace("SensorPort::getValuePath()");

            if (isEnabled() && isEnabled().value())
            {
                boost::leaf::result<std::string> path = getBasePath();
                if (!path)
                {
                    spdlog::error("Failed to get path");
                    return path;
                }
                return path.value() + "/value" + std::to_string(index);
            }
            else
            {
                spdlog::warn(("Port is not enabled for %s"), _path);
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
            }
        }

        boost::leaf::result<path_mode_t> SensorPort::getModePath()
        {
            spdlog::trace("SensorPort::getModePath()");

            if (isEnabled() && isEnabled().value())
            {
                boost::leaf::result<std::string> path = getBasePath();
                if (!path)
                {
                    spdlog::error("Failed to get path");
                    return path;
                }
                return path.value() + "/mode";
            }
            else
            {
                spdlog::warn(("Port is not enabled for %s"), _path);
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled"));
            }
        }

        boost::leaf::result<path_modes_t> SensorPort::getModesPath()
        {
            spdlog::trace("SensorPort::getModesPath()");
        
            if (isEnabled() && isEnabled().value())
            {
                boost::leaf::result<std::string> path = getBasePath();
                if (!path)
                {
                    spdlog::error("Failed to get path");
                    return path;
                }
                return path.value() + "/modes";
            }
            else
            {
                spdlog::warn(("Port is not enabled for %s"), _path);
                boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
            }

            return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
        }

        boost::leaf::result<path_num_values_t> SensorPort::getNumValuesPath()
        {
            spdlog::trace("SensorPort::getNumValuesPath()");

            if (isEnabled() && isEnabled().value())
            {
                boost::leaf::result<std::string> path = getBasePath();
                if (!path)
                {
                    spdlog::error("Failed to get path");
                    return path.error();
                }
                return path.value() + "/num_values";
            }
            else
            {
                spdlog::warn(("Port is not enabled for %s"), _path);
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
            }
        }

        boost::leaf::result<path_poll_ms_t> SensorPort::getPollMsPath()
        {
            spdlog::trace("SensorPort::getPollMsPath()");

            if (isEnabled() && isEnabled().value())
            {
                boost::leaf::result<std::string> path = getBasePath();
                if (!path)
                {
                    spdlog::error("Failed to get path");
                    return "";
                }
                return path.value() + "/poll_ms";
            }
            else
            {
                spdlog::warn(("Port is not enabled for %s"), _path);
                return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
            }
        }

        boost::leaf::result<int> SensorPort::getValue(int index)
        {
            spdlog::trace("SensorPort::getValue()");

            

            if (isEnabled() && isEnabled().value())
            {
                if (index < 0 || index >= _file_value_path.size())
                {
                    spdlog::warn(("Index out of range for %s"), getBasePath().value().c_str());
                    return boost::leaf::new_error(std::invalid_argument("Index out of range"));
                }
                
                if (_file_value_path[index]->bad())
                {
                    spdlog::error(("Failed to get value for %s"), getBasePath().value().c_str());
                    return boost::leaf::new_error(std::invalid_argument("Failed to get value"));
                }

                if (_file_value_path[index]->fail())
                {
                    spdlog::error(("Failed to get value for %s"), getBasePath().value().c_str());
                    return boost::leaf::new_error(std::invalid_argument("Failed to get value"));
                }

                if (_file_value_path[index]->is_open())
                {
                    int value = 0;
                    _file_value_path[index]->seekg(0);
                    *_file_value_path[index] >> value;
                    spdlog::debug("VALUE.GET: " + std::string(getBasePath().value().c_str()) + " WITH VALUE: " + std::to_string(value));
                    return value;
                } 
            } 
            spdlog::warn(("Port is not enabled for %s"), _path);
            return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
        }

        boost::leaf::result<void> SensorPort::setMode(sensor_mode_t mode)
        {
            spdlog::trace("SensorPort::setMode()");

            if (isEnabled() && isEnabled().value())
            {
                spdlog::trace("Port is enabled");
                if (_file_mode_path->good())
                {
                    spdlog::trace("Mode file is good");
                } else {
                    spdlog::error("Mode file is not good");
                    return boost::leaf::new_error(std::invalid_argument("Mode file is not good"));
                }
                if (_file_mode_path->is_open())
                {
                    _file_mode_path->seekp(0);
                    *_file_mode_path << mode;
                    _file_mode_path->flush();
                }
                spdlog::info(("MODE.SET: %s WITH_VALUE: %s"), getBasePath().value().c_str(), mode.c_str());
                return boost::leaf::result<void>();
            }
            spdlog::warn(("Port is not enabled for %s"), getBasePath().value().c_str());
            return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + getBasePath().value()));
        }

        std::vector<sensor_mode_t> SensorPort::getModes()
        {
            spdlog::trace("SensorPort::getModes()");

            // read modes from file into vector
            if (isEnabled())
            {
                if (_file_modes_path->is_open())
                {
                    std::string mode;
                    _file_modes_path->seekg(0);
                    _modes.clear();
                    while (*_file_modes_path >> mode)
                    {
                        _modes.push_back(mode);
                    }
                    _modes = _modes;
                    for (auto m : _modes)
                    {
                        spdlog::info(("MODES.GET: %s WITH_RESULT: %s"), getBasePath().value().c_str(), m.c_str());
                    }
                }
                return _modes;
            }
            spdlog::warn(("Port is not enabled for %s"), getBasePath().value().c_str());
            return std::vector<sensor_mode_t>{};
        }

        boost::leaf::result<int> SensorPort::getNumValues()
        {
            spdlog::trace("SensorPort::getNumValues()");

            if (isEnabled() && isEnabled().value())
            {
                if (_file_num_values_path->is_open())
                {
                    int num_values;
                    _file_num_values_path->seekg(0);
                    *_file_num_values_path >> num_values;
                    spdlog::info("NUM_VALUES.GET: %s WITH_RESULT: %d", getBasePath().value().c_str(), num_values);
                    return num_values;
                }
            }
            spdlog::warn("Port is not enabled for {}", _path);
            return boost::leaf::new_error(std::invalid_argument("Port is not enabled: " + _path));
        }

        int SensorPort::getPollMs()
        {
            spdlog::trace("SensorPort::getPollMs()");

            if (isEnabled() && isEnabled().value())
            {
                if (_file_poll_ms_path->is_open())
                {
                    int poll_ms;
                    _file_poll_ms_path->seekg(0);
                    *_file_poll_ms_path >> poll_ms;
                    spdlog::info(("POLL_MS.GET: %s WITH_RESULT: %d"), getBasePath().value().c_str(), poll_ms);
                    return poll_ms;
                }
            }
            spdlog::warn("Port is not enabled for: " + _path);
            return -1;
        }

        boost::leaf::result<DeviceType> SensorPort::getDeviceType()
        {
            spdlog::trace("SensorPort::getDeviceType()");

            boost::leaf::result<DeviceType> device_type = Port::getDeviceType();
            if (device_type && device_type.value() != DeviceType::SENSOR) {
                spdlog::error("SensorPort::getDeviceType() called on non-sensor port");
                return boost::leaf::new_error(std::invalid_argument("SensorPort::getDeviceType() called on non-sensor port"));
            } else {
                spdlog::debug("Device type is SENSOR");
            }
            return DeviceType::SENSOR;
        }
        
        void SensorPort::calibrateGyro()
        {
            if (isEnabled() && isEnabled().value())
            {
                if (getDriverName().value() == DriverName::SENSOR_GYRO) {
                    spdlog::info("###### CALIBRATING ######");
                    spdlog::info("Calibrating gyro sensor, please do not move the robot");

                    setMode("GYRO-CAL");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    setMode("GYRO-ANG");
                    spdlog::info("### END OF CALIBRATION ###");
                }
                else
                {
                    spdlog::error("Calibrate gyro called on non-gyro sensor");
                }
            }
            else
            {
                spdlog::warn("Port is not enabled for: " + _path);
            }
        }
        
        boost::leaf::result<void> SensorPort::initFiles()
        {
            spdlog::trace("SensorPort::initFiles()");

            // open files
            for (int i = 0; i < 10; i++)
            {
                boost::leaf::result<std::string> value_path = getValuePath(i);
                if (!value_path)
                {
                    spdlog::error("Failed to get value path for %d", i);
                    return value_path.error();
                    continue;
                }
                _file_value_path.push_back(std::make_shared<std::ifstream>(value_path.value()));
                if (!_file_value_path[i]->fail())
                {
                    if (!_file_value_path[i]->is_open())
                    {
                        spdlog::error(("Failed to open value0 file at: %s"), value_path.value().c_str());
                        _file_value_path[i].reset();
                        return boost::leaf::new_error(std::invalid_argument("Failed to open value0 file: " + value_path.value()));
                    }
                    else
                    {
                        spdlog::info(("Opened value0 file at: %s"), value_path.value().c_str());
                    }
                }
                else
                {
                    spdlog::error(("File does not exist at: %s"), value_path.value().c_str());
                    return boost::leaf::new_error(std::invalid_argument("File does not exist: " + value_path.value()));
                }
            }  

            boost::leaf::result<std::string> mode_path = getModePath();
            if (!mode_path)
            {
                spdlog::error("Failed to get mode path");
                return mode_path.error();
            }
            _file_mode_path = std::make_shared<std::ofstream>(mode_path.value());
            boost::leaf::result<std::string> modes_path = getModesPath();
            if (!modes_path)
            {
                spdlog::error("Failed to get modes path");
                return modes_path.error();
            }
            _file_modes_path = std::make_shared<std::ifstream>(modes_path.value());
            boost::leaf::result<std::string> num_values_path = getNumValuesPath();
            if (!num_values_path)
            {
                spdlog::error("Failed to get num values path");
                return num_values_path.error();
            }
            _file_num_values_path = std::make_shared<std::ifstream>(num_values_path.value());
            boost::leaf::result<std::string> poll_ms_path = getPollMsPath();
            if (!poll_ms_path)
            {
                spdlog::error("Failed to get poll ms path");
                return poll_ms_path.error();
            }
            _file_poll_ms_path = std::make_shared<std::ifstream>(poll_ms_path.value());

            // check if mode path is opened
            if (!_file_mode_path->fail()) {
                if (!_file_mode_path->is_open()) {
                    spdlog::warn(("Failed to open value0 file at: %s"), mode_path.value().c_str());
                    _file_mode_path.reset();
                    return boost::leaf::new_error(std::invalid_argument("Failed to open value0 file: " + mode_path.value()));
                } else {
                    spdlog::debug(("Opened mode file at: %s"), mode_path.value().c_str());
                }
            } else {
                spdlog::error(("File does not exist at: %s"), mode_path.value().c_str());
                return boost::leaf::new_error(std::invalid_argument("File does not exist: " + mode_path.value()));
            }

            // check if modes path is opened
            if (!_file_modes_path->fail()) {
                if (!_file_modes_path->is_open()) {
                    spdlog::warn(("Failed to open value0 file at: %s"), modes_path.value().c_str());
                    _file_modes_path.reset();
                    return boost::leaf::new_error(std::invalid_argument("Failed to open value0 file: " + modes_path.value()));
                } else {
                    spdlog::debug(("Opened modes file at: %s"), modes_path.value().c_str());
                }
            } else {
                spdlog::error(("File does not exist at: %s"), modes_path.value().c_str());
                return boost::leaf::new_error(std::invalid_argument("File does not exist: " + modes_path.value()));                
            }

            // check if num_values path is opened
            if (!_file_num_values_path->fail()) {
                if (!_file_num_values_path->is_open()) {
                    spdlog::warn(("Failed to open value0 file at: %s"), num_values_path.value().c_str());
                    _file_num_values_path.reset();
                    return boost::leaf::new_error(std::invalid_argument("Failed to open value0 file: " + num_values_path.value()));
                } else {
                    spdlog::debug(("Opened num_values file at: %s"), num_values_path.value().c_str());
                }
            } else {
                spdlog::error(("File does not exist at: %s"), num_values_path.value().c_str());
                return boost::leaf::new_error(std::invalid_argument("File does not exist: " + num_values_path.value()));
            }

            // check if poll_ms path is opened
            if (!_file_poll_ms_path->fail()) {
                if (!_file_poll_ms_path->is_open()) {
                    spdlog::warn(("Failed to open value0 file at: %s"), poll_ms_path.value().c_str());
                    _file_poll_ms_path.reset();
                    return boost::leaf::new_error(std::invalid_argument("Failed to open value0 file: " + poll_ms_path.value()));
                } else {
                    spdlog::info(("Opened poll_ms file at: %s"), poll_ms_path.value().c_str());
                }
            } else {
                spdlog::error(("File does not exist at: %s"), poll_ms_path.value().c_str());
                return boost::leaf::new_error(std::invalid_argument("File does not exist: " + poll_ms_path.value()));
            }

            return boost::leaf::result<void>();
        }
    } // namespace physical
    
} // namespace finder
