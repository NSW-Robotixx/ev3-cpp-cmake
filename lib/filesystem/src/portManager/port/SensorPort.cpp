// #include <physical/portManager/port/SensorPort.hpp>
#include "./SensorPort.hpp"

namespace finder
{
    namespace physical
    {
#ifdef ENABLE_LOGGING
        ::finder::log::Logger SensorPort::_logger;
#endif
        std::vector<sensor_mode_t> SensorPort::_modes{};

        /*
        SensorPort::SensorPort(): Port()
        {
            _is_initialized = false;
        }
        */

        SensorPort::SensorPort(std::string port_name): Port(port_name)
        {
            if (port_name.length() <= 0) {
                throw new std::invalid_argument("SensorPort created without port path");
            }
            _is_initialized = false;
            _is_initialized = initFiles();
        }

        SensorPort::SensorPort(std::shared_ptr<Port> port): Port(port->getBasePath())
        {
            if (port->getBasePath().length() <= 0) {
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
            if (isEnabled())
            {
                return getBasePath() + "/value" + std::to_string(index);
            }
            else
            {
                return "";
            }
        }

        path_mode_t SensorPort::getModePath()
        {
            if (isEnabled())
            {
                return getBasePath() + "/mode";
            }
            else
            {
                return "";
            }
        }

        path_modes_t SensorPort::getModesPath()
        {
            if (isEnabled())
            {
                return getBasePath() + "/modes";
            }
            else
            {
                return "";
            }
        }

        path_num_values_t SensorPort::getNumValuesPath()
        {
            if (isEnabled())
            {
                return getBasePath() + "/num_values";
            }
            else
            {
                return "";
            }
        }

        path_poll_ms_t SensorPort::getPollMsPath()
        {
            if (isEnabled())
            {
                return getBasePath() + "/poll_ms";
            }
            else
            {
                return "";
            }
        }

        int SensorPort::getValue(int index)
        {
#ifdef ENABLE_LOGGING            
            FileLoggerLock lock = FileLoggerLock();
            logToFile("VALUE.GET: " + std::to_string(index) + " FROM: " + getBasePath());
#endif            

            if (isEnabled())
            {
                if (index < 0 || index >= _file_value_path.size())
                {
#ifdef ENABLE_LOGGING
                    _logger.error("Index out of range for value file");
#endif
                    return -1;
                }
                
                if (_file_value_path[index]->is_open())
                {
                    int value;
                    *_file_value_path[index] >> value;
#ifdef ENABLE_LOGGING                    
                    logToFile(" WITH_RESULT: " + std::to_string(value));
#endif                    
                    return value;
                }
            }
            return -1;
        }

        void SensorPort::setMode(sensor_mode_t mode)
        {
#ifdef ENABLE_LOGGING            
            FileLoggerLock lock = FileLoggerLock();
            logToFile("MODE.SET: " + mode + " FOR: " + getBasePath());
#endif            

            if (isEnabled())
            {
                if (_file_mode_path->is_open())
                {
                    *_file_mode_path << mode;
                    _file_mode_path->flush();
                }
            }
        }

        std::vector<sensor_mode_t> SensorPort::getModes()
        {
#ifdef ENABLE_LOGGING            
            FileLoggerLock lock = FileLoggerLock();
            logToFile("MODES.GET: " + getBasePath());
#endif            

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
#ifdef ENABLE_LOGGING                        
                        logToFile(" WITH_RESULT: " + m);
#endif                        
                    }
                }
                return _modes;
            }
            return std::vector<sensor_mode_t>{};
        }

        int SensorPort::getNumValues()
        {
#ifdef ENABLE_LOGGING            
            FileLoggerLock lock = FileLoggerLock();
            logToFile("NUM_VALUES.GET: " + getBasePath());
#endif            

            if (isEnabled())
            {
                if (_file_num_values_path->is_open())
                {
                    int num_values;
                    *_file_num_values_path >> num_values;
#ifdef ENABLE_LOGGING                    
                    logToFile(" WITH_RESULT: " + std::to_string(num_values));
#endif                    
                    return num_values;
                }
            }
            return -1;
        }

        int SensorPort::getPollMs()
        {
#ifdef ENABLE_LOGGING            
            FileLoggerLock lock = FileLoggerLock();
            logToFile("POLL_MS.GET: " + getBasePath());
#endif            

            if (isEnabled())
            {
                if (_file_poll_ms_path->is_open())
                {
                    int poll_ms;
                    *_file_poll_ms_path >> poll_ms;
#ifdef ENABLE_LOGGING                    
                    logToFile(" WITH_RESULT: " + std::to_string(poll_ms));
#endif                    
                    return poll_ms;
                }
            }
            return -1;
        }

        DeviceType SensorPort::getDeviceType()
        {
            if (Port::getDeviceType() != DeviceType::SENSOR) {
                // _logger.warn(
                    // "SensorPort::getDeviceType() called on non-sensor port"
                // );
                throw new std::runtime_error(
                    "SensorPort::getDeviceType() called on non-sensor port"
                );
            }
            return DeviceType::SENSOR;
        }
        bool SensorPort::initFiles()
        {
            bool full_success = true;

            // open files
            _file_value_path.push_back(std::make_shared<std::ifstream>(getValuePath(0)));
            _file_mode_path = std::make_shared<std::ofstream>(getModePath());
            _file_modes_path = std::make_shared<std::ifstream>(getModesPath());
            _file_num_values_path = std::make_shared<std::ifstream>(getNumValuesPath());
            _file_poll_ms_path = std::make_shared<std::ifstream>(getPollMsPath());

            // check if value[0] path is opened
            if (!_file_value_path[0]->fail()) {
                if (!_file_value_path[0]->is_open()) {
#ifdef ENABLE_LOGGING                    
                    _logger.warn("Failed to open value0 file at: " + getValuePath(0));
#endif                    
                    _file_value_path[0].reset();
                    full_success = false;
                } else {
#ifdef ENABLE_LOGGING                    
                    _logger.success("Opened value file at: " + getValuePath(0));
#endif                    
                }
            } else {
#ifdef ENABLE_LOGGING                
                _logger.error("File does not exist at: " + getValuePath(0));
#endif                
            }

            // check if mode path is opened
            if (!_file_mode_path->fail()) {
                if (!_file_mode_path->is_open()) {
#ifdef ENABLE_LOGGING                    
                    _logger.warn("Failed to open value0 file at: " + getModePath());
#endif                    
                    _file_mode_path.reset();
                    full_success = false;
                } else {
#ifdef ENABLE_LOGGING                    
                    _logger.success("Opened mode file at: " + getModePath());
#endif                    
                }
            } else {
#ifdef ENABLE_LOGGING                
                _logger.error("File does not exist at: " + getModePath());
#endif                
            }

            // check if modes path is opened
            if (!_file_modes_path->fail()) {
                if (!_file_modes_path->is_open()) {
#ifdef ENABLE_LOGGING                    
                    _logger.warn("Failed to open value0 file at: " + getModesPath());
#endif                    
                    _file_modes_path.reset();
                    full_success = false;
                } else {
#ifdef ENABLE_LOGGING                    
                    _logger.success("Opened modes file at: " + getModesPath());
#endif                    
                }
            } else {
#ifdef ENABLE_LOGGING                
                _logger.error("File does not exist at: " + getModesPath());
#endif                
            }

            // check if num_values path is opened
            if (!_file_num_values_path->fail()) {
                if (!_file_num_values_path->is_open()) {
#ifdef ENABLE_LOGGING                    
                    _logger.warn("Failed to open value0 file at: " + getNumValuesPath());
#endif                    
                    _file_num_values_path.reset();
                    full_success = false;
                } else {
#ifdef ENABLE_LOGGING                    
                    _logger.success("Opened num_values file at: " + getNumValuesPath());
#endif                    
                }
            } else {
#ifdef ENABLE_LOGGING                
                _logger.error("File does not exist at: " + getNumValuesPath());
#endif                
            }

            // check if poll_ms path is opened
            if (!_file_poll_ms_path->fail()) {
                if (!_file_poll_ms_path->is_open()) {
#ifdef ENABLE_LOGGING                    
                    _logger.warn("Failed to open value0 file at: " + getPollMsPath());
#endif                    
                    _file_poll_ms_path.reset();
                    full_success = false;
                } else {
#ifdef ENABLE_LOGGING                    
                    _logger.success("Opened poll_ms file at: " + getPollMsPath());
#endif                    
                }
            } else {
#ifdef ENABLE_LOGGING                
                _logger.error("File does not exist at: " + getPollMsPath());
#endif                
            }

            return full_success;
        }

    } // namespace physical
    
} // namespace finder
