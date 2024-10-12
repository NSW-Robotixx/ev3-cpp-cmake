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
            _is_initialized = initFiles();
        }

        SensorPort::SensorPort(std::shared_ptr<Port> port): Port(port->getBasePath())
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::SensorPort(std::shared_ptr<Port> port)");

            if (port->getBasePath().length() <= 0) {
                LOG4CPLUS_ERROR(_logger, LOG4CPLUS_TEXT("SensorPort created without port path"));
                throw new std::invalid_argument("SensorPort created without port path");
            }
            _is_initialized = false;
            _is_initialized = initFiles();
        }

        void SensorPort::setBasePath(const path_port_t& path)
        {
            Port::setBasePath(path);
            initFiles();
        }

        path_value_t SensorPort::getValuePath(int index)
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getValuePath()");

            if (isEnabled())
            {
                return getBasePath() + "/value" + std::to_string(index);
            }
            else
            {
                LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
                return "";
            }
        }

        path_mode_t SensorPort::getModePath()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getModePath()");

            if (isEnabled())
            {
                return getBasePath() + "/mode";
            }
            else
            {
                LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
                return "";
            }
        }

        path_modes_t SensorPort::getModesPath()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getModesPath()");
        
            if (isEnabled())
            {
                return getBasePath() + "/modes";
            }
            else
            {
                LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
                return "";
            }
        }

        path_num_values_t SensorPort::getNumValuesPath()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getNumValuesPath()");

            if (isEnabled())
            {
                return getBasePath() + "/num_values";
            }
            else
            {
                LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
                return "";
            }
        }

        path_poll_ms_t SensorPort::getPollMsPath()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getPollMsPath()");

            if (isEnabled())
            {
                return getBasePath() + "/poll_ms";
            }
            else
            {
                LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
                return "";
            }
        }

        int SensorPort::getValue(int index)
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getValue()");

            if (isEnabled())
            {
                if (index < 0 || index >= _file_value_path.size())
                {
                    LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Index out of range for %s"), getBasePath().c_str());
                    return -1;
                }
                
                if (_file_value_path[index]->is_open())
                {
                    int value;
                    *_file_value_path[index] >> value;
                    LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("VALUE.GET: %s WITH_RESULT: %d"), getBasePath().c_str(), value);
                    return value;
                } 
            } 
            LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
            throw new std::runtime_error("SensorPort is not enabled");
        }

        void SensorPort::setMode(sensor_mode_t mode)
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::setMode()");

            if (isEnabled())
            {
                if (_file_mode_path->is_open())
                {
                    *_file_mode_path << mode;
                    _file_mode_path->flush();
                }
            }
            LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
        }

        std::vector<sensor_mode_t> SensorPort::getModes()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getModes()");

            // read modes from file into vector
            if (isEnabled())
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
                        LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("MODES.GET: %s WITH_RESULT: %s"), getBasePath().c_str(), m.c_str());
                    }
                }
                return _modes;
            }
            LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
            return std::vector<sensor_mode_t>{};
        }

        int SensorPort::getNumValues()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getNumValues()");

            if (isEnabled())
            {
                if (_file_num_values_path->is_open())
                {
                    int num_values;
                    *_file_num_values_path >> num_values;
                    LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("NUM_VALUES.GET: %s WITH_RESULT: %d"), getBasePath().c_str(), num_values);
                    return num_values;
                }
            }
            LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
            return -1;
        }

        int SensorPort::getPollMs()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getPollMs()");

            if (isEnabled())
            {
                if (_file_poll_ms_path->is_open())
                {
                    int poll_ms;
                    *_file_poll_ms_path >> poll_ms;
                    LOG4CPLUS_INFO_FMT(_logger, LOG4CPLUS_TEXT("POLL_MS.GET: %s WITH_RESULT: %d"), getBasePath().c_str(), poll_ms);
                    return poll_ms;
                }
            }
            LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Port is not enabled for %s"), getBasePath().c_str());
            return -1;
        }

        DeviceType SensorPort::getDeviceType()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::getDeviceType()");

            if (Port::getDeviceType() != DeviceType::SENSOR) {
                LOG4CPLUS_ERROR(_logger, "SensorPort::getDeviceType() called on non-sensor port");
                throw new std::runtime_error(
                    "SensorPort::getDeviceType() called on non-sensor port"
                );
            }
            return DeviceType::SENSOR;
        }
        bool SensorPort::initFiles()
        {
            LOG4CPLUS_TRACE(_logger, "SensorPort::initFiles()");

            bool full_success = true;

            // open files
            for (int i = 0; i < 10; i++)
            {
                _file_value_path.push_back(std::make_shared<std::ifstream>(getValuePath(i)));
                if (!_file_value_path[i]->fail())
                {
                    if (!_file_value_path[i]->is_open())
                    {
                        LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Failed to open value0 file at: %s"), getValuePath(i).c_str());
                        _file_value_path[i].reset();
                        full_success = false;
                    }
                    else
                    {
                        LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened value0 file at: %s"), getValuePath(i).c_str());
                    }
                }
                else
                {
                    LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), getValuePath(i).c_str());
                }
            }  

            _file_mode_path = std::make_shared<std::ofstream>(getModePath());
            _file_modes_path = std::make_shared<std::ifstream>(getModesPath());
            _file_num_values_path = std::make_shared<std::ifstream>(getNumValuesPath());
            _file_poll_ms_path = std::make_shared<std::ifstream>(getPollMsPath());


            // check if mode path is opened
            if (!_file_mode_path->fail()) {
                if (!_file_mode_path->is_open()) {
                    LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Failed to open value0 file at: %s"), getModePath().c_str());
                    _file_mode_path.reset();
                    full_success = false;
                } else {
                    LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened mode file at: %s"), getModePath().c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), getModePath().c_str());
            }

            // check if modes path is opened
            if (!_file_modes_path->fail()) {
                if (!_file_modes_path->is_open()) {
                    LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Failed to open value0 file at: %s"), getModesPath().c_str());
                    _file_modes_path.reset();
                    full_success = false;
                } else {
                    LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened modes file at: %s"), getModesPath().c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), getModesPath().c_str());
            }

            // check if num_values path is opened
            if (!_file_num_values_path->fail()) {
                if (!_file_num_values_path->is_open()) {
                    LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Failed to open value0 file at: %s"), getNumValuesPath().c_str());
                    _file_num_values_path.reset();
                    full_success = false;
                } else {
                    LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened num_values file at: %s"), getNumValuesPath().c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), getNumValuesPath().c_str());
            }

            // check if poll_ms path is opened
            if (!_file_poll_ms_path->fail()) {
                if (!_file_poll_ms_path->is_open()) {
                    LOG4CPLUS_WARN_FMT(_logger, LOG4CPLUS_TEXT("Failed to open value0 file at: %s"), getPollMsPath().c_str());
                    _file_poll_ms_path.reset();
                    full_success = false;
                } else {
                    LOG4CPLUS_DEBUG_FMT(_logger, LOG4CPLUS_TEXT("Opened poll_ms file at: %s"), getPollMsPath().c_str());
                }
            } else {
                LOG4CPLUS_ERROR_FMT(_logger, LOG4CPLUS_TEXT("File does not exist at: %s"), getPollMsPath().c_str());
            }

            return full_success;
        }

    } // namespace physical
    
} // namespace finder
