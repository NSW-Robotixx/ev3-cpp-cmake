// #include <physical/portManager/port/SensorPort.hpp>
#include "./SensorPort.hpp"

namespace finder
{
    namespace physical
    {
        ::finder::console::Logger SensorPort::_logger;
        std::vector<sensor_mode_t> SensorPort::_modes{};

        SensorPort::SensorPort(): Port()
        {
            _is_initialized = false;
        }

        SensorPort::SensorPort(std::string port_name): Port()
        {
            setBasePath(port_name);
            _is_initialized = false;
            initFiles();
        }

        SensorPort::SensorPort(std::shared_ptr<Port> port): Port()
        {
            setBasePath(port->getBasePath());
            _is_initialized = false;
            initFiles();
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
            if (isEnabled())
            {
                if (_file_value_path->is_open())
                {
                    int value;
                    *_file_value_path >> value;
                    return value;
                }
            }
            return -1;
        }

        void SensorPort::setMode(sensor_mode_t mode)
        {
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
                }
                return _modes;
            }
            return std::vector<sensor_mode_t>{};
        }

        int SensorPort::getNumValues()
        {
            if (isEnabled())
            {
                if (_file_num_values_path->is_open())
                {
                    int num_values;
                    *_file_num_values_path >> num_values;
                    return num_values;
                }
            }
            return -1;
        }

        int SensorPort::getPollMs()
        {
            if (isEnabled())
            {
                if (_file_poll_ms_path->is_open())
                {
                    int poll_ms;
                    *_file_poll_ms_path >> poll_ms;
                    return poll_ms;
                }
            }
            return -1;
        }

        DeviceType SensorPort::getDeviceType()
        {
            if (Port::getDeviceType() != DeviceType::SENSOR) {
                _logger.warn(
                    "SensorPort::getDeviceType() called on non-sensor port"
                );
            }
            return DeviceType::SENSOR;
        }
        void SensorPort::initFiles()
        {
            using namespace ::finder::console;

            if (
                std::filesystem::exists(getValuePath(0)) == false ||
                std::filesystem::exists(getModePath()) == false ||
                std::filesystem::exists(getModesPath()) == false ||
                std::filesystem::exists(getNumValuesPath()) == false ||
                std::filesystem::exists(getPollMsPath()) == false
            ) {
                _logger.log(
                    Logger::LogLevel::DEBUG, 
                    "SensorPort files not found at: " + getBasePath()
                );
            } else {
                _file_value_path = std::make_shared<std::ifstream>();
                _file_value_path->open(getValuePath(0));
                _file_mode_path = std::make_shared<std::ofstream>();
                _file_mode_path->open(getModePath());
                _file_modes_path = std::make_shared<std::ifstream>();
                _file_modes_path->open(getModesPath());
                _file_num_values_path = std::make_shared<std::ifstream>();
                _file_num_values_path->open(getNumValuesPath());
                _file_poll_ms_path = std::make_shared<std::ifstream>();
                _file_poll_ms_path->open(getPollMsPath());

                if (
                    _file_value_path->is_open() == false ||
                    _file_mode_path->is_open() == false ||
                    _file_modes_path->is_open() == false ||
                    _file_num_values_path->is_open() == false ||
                    _file_poll_ms_path->is_open() == false
                ) {
                    _logger.log(
                        Logger::LogLevel::ERROR, 
                        "SensorPort files not opened at: " + getBasePath()
                    );
                } else {
                    _is_initialized = true;
                }
            }

        }

    } // namespace physical
    
} // namespace finder
