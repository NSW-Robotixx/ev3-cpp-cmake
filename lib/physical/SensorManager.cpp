#include "SensorManager.hpp"

namespace finder::physical
{
    int SensorManager::_gyroValue = 0;
    int SensorManager::_colorLeftValue = 0;
    int SensorManager::_colorRightValue = 0;
    int SensorManager::_colorFrontValue = 0;

    std::mutex SensorManager::_gyroValueMutex;
    std::mutex SensorManager::_colorLeftValueMutex;
    std::mutex SensorManager::_colorRightValueMutex;
    std::mutex SensorManager::_colorFrontValueMutex;

    std::vector<std::map<DeviceType, std::function<void(int)>>> SensorManager::_eventListeners;

    std::mutex SensorManager::_stopDispatcherMutex;
    bool SensorManager::_stopDispatcher = false;
    std::future<void> SensorManager::_dispatcherFuture;

    console::Logger SensorManager::_logger;

    SensorManager::SensorManager(std::string portBasePath) : DeviceManager(portBasePath)
    {
        _dispatcherFuture = std::async(std::launch::async, Dispatcher);
    }

    SensorManager::~SensorManager()
    {
        {
            std::lock_guard<std::mutex> lock(_stopDispatcherMutex);
            _stopDispatcher = true;
        }
        _dispatcherFuture.wait();
    }

    void SensorManager::readAllSensors()
    {
        readGyro();
        readColorLeft();
        readColorRight();
        readColorFront();
    }

    int SensorManager::readGyro()
    {
        std::lock_guard<std::mutex> lock(_gyroValueMutex);
        _gyroValue = _gyroSensor->getValue(0);
        return _gyroValue;
    }

    int SensorManager::readColorLeft()
    {
        std::lock_guard<std::mutex> lock(_colorLeftValueMutex);
        _colorLeftValue = _colorSensorLeft->getValue(0);
        return _colorLeftValue;
    }

    int SensorManager::readColorRight()
    {
        std::lock_guard<std::mutex> lock(_colorRightValueMutex);
        _colorRightValue = _colorSensorRight->getValue(0);
        return _colorRightValue;
    }

    int SensorManager::readColorFront()
    {
        std::lock_guard<std::mutex> lock(_colorFrontValueMutex);
        _colorFrontValue = _colorSensorFront->getValue(0);
        return _colorFrontValue;
    }
    
    void SensorManager::addEventListeners(DeviceType port, std::function<void(int)> callback)
    {
        std::map<DeviceType, std::function<void(int)>> listener;
        listener[port] = callback;
        _eventListeners.push_back(listener);
    }

    void SensorManager::Dispatcher()
    {
        while (_stopDispatcher == false)
        {
            int gyroValue = _gyroValue;
            int colorLeftValue = _colorLeftValue;
            int colorRightValue = _colorRightValue;
            int colorFrontValue = _colorFrontValue;

            std::vector<std::future<void>> callbackFutures;

            readAllSensors();

            for (auto &callback : _eventListeners)
            {
                if (callback.begin()->first == static_cast<DeviceType>(_gyroSensor->getPortKey()))
                    callbackFutures.push_back(std::async(std::launch::async, callback.begin()->second, gyroValue));
                else if (callback.begin()->first == static_cast<DeviceType>(_colorSensorLeft->getPortKey()))
                    callbackFutures.push_back(std::async(std::launch::async, callback.begin()->second, colorLeftValue));
                else if (callback.begin()->first == static_cast<DeviceType>(_colorSensorRight->getPortKey()))
                    callbackFutures.push_back(std::async(std::launch::async, callback.begin()->second, colorRightValue));
                else if (callback.begin()->first == static_cast<DeviceType>(_colorSensorFront->getPortKey()))
                    callbackFutures.push_back(std::async(std::launch::async, callback.begin()->second, colorFrontValue));
                else {
                    _logger.error("SensorManager::Dispatcher, Unknown port key");
                }
            }
        }
    }
} // namespace finder::physical