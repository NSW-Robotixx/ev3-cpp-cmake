#include <string>
namespace finder
{
    namespace physical
    {
        #ifndef PORT_HPP
        #define PORT_HPP

        
        typedef std::string path_port_t;
        typedef std::string path_address_t;
        typedef std::string path_value_t;
        typedef std::string path_mode_t;
        typedef std::string path_command_t;
        typedef std::string path_position_sp_t;
        typedef std::string path_speed_t;
        typedef std::string path_count_per_rotation_t;
        typedef std::string path_duty_cycle_t;
        typedef std::string path_stop_action_t;
        typedef std::string path_polarity_t;
        typedef std::string path_state_t;

        struct Port
        {
            public:
                Port(): _enabled{false} {};
                Port(const path_port_t& port) : _path{port}, _enabled{true} {}
                ~Port() = default;

                void setBasePath(const path_port_t& path);

                path_port_t getBasePath() const;
                path_address_t getAddressPath() const;
                path_value_t getValuePath() const;
                path_mode_t getModePath() const;
                path_command_t getCommandPath() const;
                path_position_sp_t getPositionSpPath() const;
                path_speed_t getSpeedPath() const;
                path_count_per_rotation_t getCountPerRotationPath() const;
                path_duty_cycle_t getDutyCyclePath() const;
                path_stop_action_t getStopActionPath() const;
                path_polarity_t getPolarityPath() const;
                path_state_t getStatePath() const;
            
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
