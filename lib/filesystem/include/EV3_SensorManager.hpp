#ifndef __SENSOR_MANAGER_HPP__
#define __SENSOR_MANAGER_HPP__

#include <DeviceManager.hpp>
#include <memory>
#include <functional>
#include <vector>
#include <mutex>
#include <future>
#include <map>
#ifdef ENABLE_LOGGING
#include <log/Logger.hpp>
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

            static void addEventListeners(DeviceType port, std::function<void(int)> callback, int value);

            static void Dispatcher();

        private:
            static int _gyroValue;
            static int _colorLeftValue;
            static int _colorRightValue;
            static int _colorFrontValue;

            static std::mutex _gyroValueMutex;
            static std::mutex _colorLeftValueMutex;
            static std::mutex _colorRightValueMutex;
            static std::mutex _colorFrontValueMutex;

            static std::vector<std::map<DeviceType, std::function<void(int)>>> _eventListeners;

            static std::mutex _stopDispatcherMutex;
            static bool _stopDispatcher;
            static std::future<void> _dispatcherFuture;

#ifdef ENABLE_LOGGING
            static log::Logger _logger; 
#endif
    };
} // namespace finder::physical

#endif // __SENSOR_MANAGER_HPP__