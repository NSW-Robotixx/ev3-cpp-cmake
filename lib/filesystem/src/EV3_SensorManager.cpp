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

    log4cplus::Logger SensorManager::_logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("main.SensorManager"));

    SensorManager::SensorManager(std::string portBasePath) : DeviceManager(portBasePath)
    {
        LOG4CPLUS_TRACE(_logger, "SensorManager::SensorManager(std::string portBasePath)");

        _dispatcherFuture = std::thread(Dispatcher);
    }

    SensorManager::~SensorManager()
    {
        LOG4CPLUS_TRACE(_logger, "SensorManager::~SensorManager()");

        _stopDispatcher = true;
        _dispatcherFuture.join();
    }

    void SensorManager::readAllSensors()
    {
        LOG4CPLUS_TRACE(_logger, "SensorManager::readAllSensors()");

        readGyro();
        readColorLeft();
        readColorRight();
        readColorFront();
    }

    int SensorManager::readGyro()
    {
        LOG4CPLUS_TRACE(_logger, "SensorManager::readGyro()");
        
        _gyroValue = _gyroSensor->getValue(0);
        return _gyroValue;
    }

    int SensorManager::readColorLeft()
    {
        LOG4CPLUS_TRACE(_logger, "SensorManager::readColorLeft()");

        _colorLeftValue = _colorSensorLeft->getValue(0);
        return _colorLeftValue;
    }

    int SensorManager::readColorRight()
    {
        LOG4CPLUS_TRACE(_logger, "SensorManager::readColorRight()");
        
        _colorRightValue = _colorSensorRight->getValue(0);
        return _colorRightValue;
    }

    int SensorManager::readColorFront()
    {
        LOG4CPLUS_TRACE(_logger, "SensorManager::readColorFront()");

        _colorFrontValue = _colorSensorFront->getValue(0);
        return _colorFrontValue;
    }
    
    void SensorManager::addEventListeners(DeviceID port, std::function<void(DeviceID, int)> callback)
    {
        LOG4CPLUS_TRACE(_logger, "SensorManager::addEventListeners())");

        _eventListeners[port] = callback;
    }

    void SensorManager::Dispatcher()
    {
        LOG4CPLUS_TRACE(_logger, "SensorManager::Dispatcher()");

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