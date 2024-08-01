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
    class SensorManager : public DeviceManager
    {
        public:
            SensorManager(std::string portBasePath);
            ~SensorManager();

            static void readAllSensors();
            static int readGyro();
            static int readColorLeft();
            static int readColorRight();
            static int readColorFront();
            static int readMotorLeft();
            static int readMotorRight();
            static int readMotorShift();
            static int readMotorTool();

            static void addEventListeners(DeviceID port, std::function<void(DeviceID, int)> callback);

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