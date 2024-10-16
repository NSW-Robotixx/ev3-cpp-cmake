#ifndef PORT_HPP
#define PORT_HPP

#define ENABLE_LOGGING

#include <string>
#include <memory>
#include <fstream>
#include <filesystem>
#include <vector>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <absl/status/status.h>
#include <absl/status/statusor.h>

namespace finder
{
    namespace physical
    {
        typedef std::string path_port_t;
        typedef std::string path_address_t;
        typedef std::string path_value_t;
        typedef std::string path_mode_t;
        typedef std::string path_modes_t;
        typedef std::string path_command_t;
        typedef std::string path_commands_t;
        typedef std::string path_position_t;
        typedef std::string path_position_sp_t;
        typedef std::string path_speed_t;
        typedef std::string path_speed_sp_t;
        typedef std::string path_count_per_rotation_t;
        typedef std::string path_duty_cycle_t;
        typedef std::string path_stop_action_t;
        typedef std::string path_polarity_t;
        typedef std::string path_state_t;
        typedef std::string path_num_values_t;
        typedef std::string path_poll_ms_t;
        typedef std::string path_max_speed_t;

        enum struct DeviceType {
            SENSOR = 0,
            MOTOR = 1,
            UNKNOWN = 2,
            DISABLED = 3,
            ANY = 4
        };
#ifdef ENABLE_LOGGING
        /// @brief Port for the physical ports on the EV3
        struct Port
#else
        struct Port
#endif
        {
            public:
                Port() = delete;

                /// @brief Constructor
                /// @param port The path to the port
                Port(const path_port_t& port);

                /// @brief Constructor
                /// @param port The path to the port
                Port(std::shared_ptr<Port> port);

                /// @brief Copy constructor
                Port(Port&) = delete;
                ~Port();

                /// @brief Set the base path of the port
                /// @return absl::Status
                /// @param path The path to set
                virtual absl::Status setBasePath(const path_port_t& path);
                
                /// @brief Get the key of the port
                /// @details The key is the last character of the port path.
                /// @return The key of the port
                inline absl::StatusOr<char> getPortKey() {
                    if (isEnabled().value_or(false)) {
                        return _path.back();
                    }
                    return absl::InvalidArgumentError("Port is not enabled: " + _path);
                };

                /// @brief Get the path of the port
                /// @return The path of the port
                absl::StatusOr<path_port_t> getBasePath();

                /// @brief Get the address of the port
                /// @return The address of the port
                absl::StatusOr<path_address_t> getAddressPath();

                /// @brief Get the address of the port
                /// @param path The path to get the address from
                /// @return The address of the port
                static absl::StatusOr<path_address_t> getAddressPath(const path_port_t& path);

                /// @brief Get the command path of the port
                /// @return The command path of the port
                absl::StatusOr<path_command_t> getCommandPath();

                /// @brief Get the commands path of the port
                /// @return The commands path of the port
                absl::StatusOr<path_commands_t> getCommandsPath();

                /**
                 * @brief Get the address of the port.
                 * 
                 * @return The address of the port as a string.
                 */
                absl::StatusOr<std::string> getAddress();
                
                /**
                 * Sets the command for the port.
                 *
                 * @param command The command to set.
                 * @return True if the command was set successfully, false otherwise.
                 */
                absl::Status setCommand(std::string command);

                /// @brief get the commands that the port can execute from file 
                /// @return vector of strings of the commands that the port can execute
                absl::StatusOr<std::vector<std::string>> getCommands();

                /// @brief gets the device type of the port
                /// @return the device type of the port, SENSOR, MOTOR, UNKNOWN, or DISABLED
                virtual absl::StatusOr<DeviceType> getDeviceType();

            
                /// @brief return the enabled status of the port
                /// @return true if the port is enabled, false otherwise
                absl::StatusOr<bool> isEnabled();

                /// @brief This is a testing function to override the enabled status of the port
                /// @warning NOT TO BE USED IN PRODUCTION! ONLY FOR TESTING PURPOSES!
                /// @param enabled the new enabled status
                void overrideEnabled(bool enabled) { _f_enabled = enabled; };

            protected:  
                /// @brief Initializes the files for the port.
                /// @return true if the files were successfully initialized, false otherwise.
                absl::Status initFiles();

                /// @brief File stream for the address file
                std::shared_ptr<std::ifstream> _file_address_path;

                /// @brief File stream for the address file
                std::shared_ptr<std::ofstream> _file_command_path;

                /// @brief File stream for the commands file
                std::shared_ptr<std::ifstream> _file_commands_path;

                /// @brief Directory path of the port
                path_port_t _path;
            private:
                bool _f_enabled;
                // bool _enabled;
                /// @brief Logger for the port
                static ::log4cplus::Logger _logger;
        };

    } // namespace physical
    
} // namespace finder

#endif // PORT_HPP