#include <EV3_SensorManager.hpp>

namespace finder::physical
{
    std::atomic<int> SensorManager::_gyroValue = 0;
    std::atomic<int> SensorManager::_colorLeftValue = 0;
    std::atomic<int> SensorManager::_colorRightValue = 0;
    std::atomic<int> SensorManager::_colorFrontValue = 0;
    std::atomic<int> SensorManager::_motorLeftValue = 0;
    std::atomic<int> SensorManager::_motorRightValue = 0;
    std::atomic<int> SensorManager::_motorShiftValue = 0;
    std::atomic<int> SensorManager::_motorToolValue = 0;

    std::map<DeviceID, std::function<void(DeviceID, int)>> SensorManager::_eventListeners;

    std::atomic<bool> SensorManager::_stopDispatcher = false;
    std::thread SensorManager::_dispatcherFuture;

#ifdef ENABLE_LOGGING
    log::Logger SensorManager::_logger;
#endif

    SensorManager::SensorManager(std::string portBasePath) : DeviceManager(portBasePath)
    {
        _dispatcherFuture = std::thread(Dispatcher);
    }

    SensorManager::~SensorManager()
    {
        _stopDispatcher = true;
        _dispatcherFuture.join();
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
        _gyroValue = _gyroSensor->getValue(0);
        return _gyroValue;
    }

    int SensorManager::readColorLeft()
    {
        _colorLeftValue = _colorSensorLeft->getValue(0);
        return _colorLeftValue;
    }

    int SensorManager::readColorRight()
    {
        _colorRightValue = _colorSensorRight->getValue(0);
        return _colorRightValue;
    }

    int SensorManager::readColorFront()
    {
        _colorFrontValue = _colorSensorFront->getValue(0);
        return _colorFrontValue;
    }
    
    void SensorManager::addEventListeners(DeviceID port, std::function<void(DeviceID, int)> callback)
    {
        _eventListeners[port] = callback;
    }

    void SensorManager::Dispatcher()
    {
        while (true)
        {
            {
                if (_stopDispatcher)
                {
                    break;
                } 

                if (_gyroSensor->getValue(0) != _gyroValue)
                {
                    _gyroValue = _gyroSensor->getValue(0);
                    for (auto const& [port, callback] : _eventListeners)
                    {
                        if (port == DeviceID::GYRO || port == DeviceID::ANY) {
                            callback(DeviceID::GYRO, _gyroValue);
                        }
                    }
                }

                if (_colorSensorFront->getValue(0) != _colorFrontValue)
                {
                    _colorFrontValue = _colorSensorFront->getValue(0);
                    for (auto const& [port, callback] : _eventListeners)
                    {
                        if (port == DeviceID::COLOR_LEFT || port == DeviceID::ANY) {
                            callback(DeviceID::COLOR_LEFT, _colorFrontValue);
                        }
                    }
                }

                if (_colorSensorLeft->getValue(0) != _colorFrontValue)
                {
                    _colorLeftValue = _colorSensorLeft->getValue(0);
                    for (auto const& [port, callback] : _eventListeners)
                    {
                        if (port == DeviceID::COLOR_RIGHT || port == DeviceID::ANY) {
                            callback(DeviceID::COLOR_FRONT, _colorFrontValue);
                        }
                    }
                }

                if (_colorSensorRight->getValue(0) != _colorRightValue)
                {
                    _colorRightValue = _colorSensorLeft->getValue(0);
                    for (auto const& [port, callback] : _eventListeners)
                    {
                        if (port == DeviceID::COLOR_RIGHT || port == DeviceID::ANY) {
                            callback(DeviceID::COLOR_RIGHT, _colorRightValue);
                        }
                    }
                }

                if (_motorLeft->getPosition() != _motorLeftValue)
                {
                    _motorLeftValue = _motorLeft->getPosition();
                    for (auto const& [port, callback] : _eventListeners)
                    {
                        if (port == DeviceID::MOTOR_LEFT || port == DeviceID::ANY) {
                            callback(DeviceID::MOTOR_LEFT, _motorLeftValue);
                        }
                    }
                }


            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
} // namespace finder::physical