#include <physical/portManager/port/Port.hpp>
#include "Port.hpp"

namespace finder
{
    namespace physical
    {
        ::finder::console::Logger Port::_logger = ::finder::console::Logger{};

        Port::Port()
        {
            _f_enabled = std::async(std::launch::async, [this]{this->_enabled = false;});
        }

        Port::Port(const path_port_t &port)
        {
            _enabled = false;
            setBasePath(port);

            // _file_address_path.open(getAddressPath());

            // if (!_file_address_path.is_open()) {
            _enabled = true;
            // }
            std::string address;
            // _file_address_path >> address;

        }

        void Port::setBasePath(const path_port_t &path)
        {
            if (path != "") {
                _path = path;
                _f_enabled = std::async(&Port::initFiles, this);
            } else {
                _enabled = false;
            }
        }

        char Port::getPortKey() const
        {
            if (_enabled)
            {
                return _path.back();
            } else {
                return '-';
            }
        }
        
        path_port_t Port::getBasePath() const
        {
            if (_enabled) {
                return _path;
            } else {
                return "";
            }
        }

        path_address_t Port::getAddressPath() const
        {
            if (_enabled) {
                return _path + "/address";
            } else {
                return "";
            }
        }

        path_value_t Port::getValuePath() const
        {
            if (_enabled) {
                return _path + "/value0";
            } else {
                return "";
            }
        }

        path_mode_t Port::getModePath() const
        {
            if (_enabled) {
                return _path + "/mode";
            } else {
                return "";
            }
        }

        path_command_t Port::getCommandPath() const
        {
            if (_enabled) {
                return _path + "/command";
            } else {
                return "";
            }
        }

        path_position_sp_t Port::getPositionSpPath() const
        {
            if (_enabled) {
                return _path + "/position_sp";
            } else {
                return "";
            }
        }

        path_speed_t Port::getSpeedPath() const
        {
            if (_enabled) {
                return _path + "/speed_sp";
            } else {
                return "";
            }
        }

        path_count_per_rotation_t Port::getCountPerRotationPath() const
        {
            if (_enabled) {
                return _path + "/count_per_rot";
            } else {
                return "";
            }
        }

        path_duty_cycle_t Port::getDutyCyclePath() const
        {
            if (_enabled) {
                return _path + "/duty_cycle_sp";
            } else {
                return "";
            }
        }

        path_stop_action_t Port::getStopActionPath() const
        {
            if (_enabled) {
                return _path + "/stop_action";
            } else {
                return "";
            }
        }

        path_polarity_t Port::getPolarityPath() const
        {
            if (_enabled) {
                return _path + "/polarity";
            } else {
                return "";
            }
        }

        path_state_t Port::getStatePath() const
        {
            if (_enabled) {
                return _path + "/state";
            } else {
                return "";
            }
        }

        void Port::initFiles()
        {
            using namespace ::finder::console;

            if (
                std::filesystem::exists(getAddressPath()) == false ||
                std::filesystem::exists(getValuePath()) == false ||
                std::filesystem::exists(getModePath()) == false
            ) {
                _logger.log(
                    Logger::LogLevel::DEBUG, 
                    "Port files not found at: " + getAddressPath()
                );
            } else {
                _file_address_path = std::make_shared<std::ifstream>();
                _file_value_path = std::make_shared<std::ifstream>();
                _file_mode_path = std::make_shared<std::ifstream>();

                _file_address_path->open(getAddressPath());
                _file_value_path->open(getValuePath());
                _file_mode_path->open(getModePath());
                if (
                    _file_address_path->is_open() == false ||
                    _file_value_path->is_open() == false ||
                    _file_mode_path->is_open() == false
                ) {
                _logger.log(
                        Logger::LogLevel::WARN, 
                        "Failed to open port files at: " + getAddressPath()
                    ); 
                }
            }
        }
    } // namespace physical
} // namespace finder
