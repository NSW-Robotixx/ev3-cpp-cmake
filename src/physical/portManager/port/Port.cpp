#include <physical/portManager/port/Port.hpp>

namespace finder
{
    namespace physical
    {
        void Port::setBasePath(const path_port_t& path)
        {
            if (path != "") {
                _path = path;
                _enabled = true;
            } else {
                _enabled = false;
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
    } // namespace physical
} // namespace finder
