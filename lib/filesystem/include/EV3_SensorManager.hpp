#ifndef __SENSOR_MANAGER_HPP__
#define __SENSOR_MANAGER_HPP__

#include <DeviceManager.hpp>
#include <memory>
#include <functional>
#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <map>
#ifdef ENABLE_LOGGING
#include <Logger.hpp>
#endif

namespace finder::physical
{
    /// @brief Manage the connected sensors
    class SensorManager : public DeviceManager
    {
        public:
            /// @brief Constructor
            /// @param portBasePath Path to the base directory of the ports 
            SensorManager(std::string portBasePath);
            ~SensorManager();

            /// @brief Read all sensors
            static void readAllSensors();

            /// @brief Read the gyro sensor
            /// @return The value of the gyro sensor
            static int readGyro();

            /// @brief Read the left color sensor
            /// @return The value of the left color sensor
            static int readColorLeft();

            /// @brief Read the right color sensor
            /// @return The value of the right color sensor
            static int readColorRight();

            /// @brief Read the front color sensor
            /// @return The value of the front color sensor
            static int readColorFront();

            /// @brief Read the left motor
            /// @return The value of the left motor
            static int readMotorLeft();

            /// @brief Read the right motor
            /// @return The value of the right motor
            static int readMotorRight();

            /// @brief Read the shift motor
            /// @return The value of the shift motor
            static int readMotorShift();

            /// @brief Read the tool motor
            /// @return The value of the tool motor
            static int readMotorTool();

            /// @brief Add an event listener
            /// @param port Port to listen to
            /// @param callback Callback to call when the event occurs
            static void addEventListeners(DeviceID port, std::function<void(DeviceID, int)> callback);

            /// @brief Dispatcher for the event listeners
            static void Dispatcher();

        private:
            static std::atomic<int> _gyroValue;
            static std::atomic<int> _colorLeftValue;
            static std::atomic<int> _colorRightValue;
            static std::atomic<int> _colorFrontValue;
            static std::atomic<int> _motorLeftValue;
            static std::atomic<int> _motorRightValue;
            static std::atomic<int> _motorShiftValue;
            static std::atomic<int> _motorToolValue;

            static std::map<DeviceID, std::function<void(DeviceID, int)>> _eventListeners;

            static std::atomic<bool> _stopDispatcher;
            static std::thread _dispatcherFuture;

#ifdef ENABLE_LOGGING
            static log::Logger _logger; 
#endif
    };
} // namespace finder::physical

#endif // __SENSOR_MANAGER_HPP__