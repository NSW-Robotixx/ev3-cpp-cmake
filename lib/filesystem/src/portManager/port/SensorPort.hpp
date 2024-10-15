#ifndef __SENSOR_PORT_HPP__
#define __SENSOR_PORT_HPP__

#define ENABLE_LOGGING

#include <portManager/port/Port.hpp>
#include <filesystem>
#include <vector>
namespace finder
{
    namespace physical
    {
        typedef std::string sensor_mode_t;
        
        /// @brief Port for the physical sensors on the EV3
        class SensorPort : public Port {
            public:
                /// @brief Constructor
                /// @param port_name The path to the port
                SensorPort(std::string port_name);

                /// @brief Constructor
                /// @param port The path to the port
                SensorPort(std::shared_ptr<Port> port);

                /// @brief Set the base path of the port
                /// @return absl::Status
                /// @param path The path to set
                absl::Status setBasePath(const path_port_t& path) override;

                /// @brief Get the value path of the port
                /// @param index Index of the value
                /// @return The value path
                absl::StatusOr<path_value_t> getValuePath(int index);

                /// @brief Get the mode path of the port
                /// @return The mode path
                absl::StatusOr<path_mode_t> getModePath();

                /// @brief Get the modes path of the port
                /// @return The modes path
                absl::StatusOr<path_modes_t> getModesPath();

                /// @brief Get the number of values path of the port
                /// @return The number of values path
                absl::StatusOr<path_num_values_t> getNumValuesPath();

                /// @brief Get the poll ms path of the port
                /// @return The poll ms path
                absl::StatusOr<path_poll_ms_t> getPollMsPath();

                /// @brief Get the value of the port
                /// @param index Index of the value
                /// @return The value of the port
                absl::StatusOr<int> getValue(int index);

                /// @brief Set the mode of the sensor
                /// @return absl::Status
                /// @param mode Mode to set
                absl::Status setMode(sensor_mode_t mode);

                /// @brief Get the available modes of the sensor
                /// @return Vector of available modes
                std::vector<sensor_mode_t> getModes();

                /// @brief Get the number of values of the sensor
                /// @return Number of values
                absl::StatusOr<int> getNumValues();

                /// @brief Get the poll ms of the sensor
                /// @return Poll ms
                int getPollMs();

                /// @brief Get the device type of the port
                /// @return The device type of the port
                absl::StatusOr<DeviceType> getDeviceType() override;
                
            private:
                static log4cplus::Logger _logger;

                static std::vector<sensor_mode_t> _modes;

                std::vector<std::shared_ptr<std::ifstream>> _file_value_path;
                std::shared_ptr<std::ofstream> _file_mode_path;
                std::shared_ptr<std::ifstream> _file_modes_path;
                std::shared_ptr<std::ifstream> _file_num_values_path;
                std::shared_ptr<std::ifstream> _file_poll_ms_path;

                bool _is_initialized;

                absl::Status initFiles();
        };
    } // namespace physical
    
} // namespace finder

#endif // __SENSOR_PORT_HPP__