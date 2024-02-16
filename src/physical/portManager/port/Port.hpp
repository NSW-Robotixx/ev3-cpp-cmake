namespace finder
{
    namespace physical
    {
        #ifndef PORT_HPP
        #define PORT_HPP

        #include <string>
        
        typedef std::string path_port_t;
        typedef std::string path_address_t;
        typedef std::string path_value_t;
        typedef std::string path_mode_t;
        typedef std::string path_command_t;
        typedef std::string path_position_t;
        typedef std::string path_speed_t;
        typedef std::string path_count_per_rotation_t;
        typedef std::string path_duty_cycle_t;
        typedef std::string path_stop_action_t;
        typedef std::string path_polarity_t;
        typedef std::string path_state_t;

        struct Port
        {
            public:
                Port() = default;
                Port(const path_port_t& port) : _path{port} {}
                ~Port() = default;

                void setBasePath(const path_port_t& path) {_path = path;}

                path_port_t getBasePath() const {return _path;}
                path_address_t getAddressPath() const {return _path + "/address";}
                path_value_t getValuePath() const {return _path + "/value0";}
                path_mode_t getModePath() const {return _path + "/mode";}
                path_command_t getCommandPath() const {return _path + "/command";}
                path_position_t getPositionPath() const {return _path + "/position_sp";}
                path_speed_t getSpeedPath() const {return _path + "/speed_sp";}
                path_count_per_rotation_t getCountPerRotationPath() const {return _path + "/count_per_rot";}
                path_duty_cycle_t getDutyCyclePath() const {return _path + "/duty_cycle_sp";}
                path_stop_action_t getStopActionPath() const {return _path + "/stop_action";}
                path_polarity_t getPolarityPath() const {return _path + "/polarity";}
                path_state_t getStatePath() const {return _path + "/state";}
                
                bool isEnabled() const {return _enabled;}
                void setEnabled() {_enabled = true;}
                void setDisabled() {_enabled = false;}

            private:
                bool _enabled;
                std::string _path;
        };

        #endif // PORT_HPP
    } // namespace physical
    
} // namespace finder
