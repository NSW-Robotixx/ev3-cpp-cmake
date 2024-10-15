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

        absl::StatusOr<int> gyroValue = _gyroSensor->getValue(0);
        if (gyroValue.ok())
        {
            _gyroValue = gyroValue.value();
        } else {
            LOG4CPLUS_ERROR(_logger, "Error reading gyro sensor");
        }

        absl::StatusOr<int> colorLeftValue = _colorSensorLeft->getValue(0);
        if (colorLeftValue.ok())
        {
            _colorLeftValue = colorLeftValue.value();
        } else {
            LOG4CPLUS_ERROR(_logger, "Error reading left color sensor");
        }

        absl::StatusOr<int> colorRightValue = _colorSensorRight->getValue(0);
        if (colorRightValue.ok())
        {
            _colorRightValue = colorRightValue.value();
        } else {
            LOG4CPLUS_ERROR(_logger, "Error reading right color sensor");
        }

        absl::StatusOr<int> colorFrontValue = _colorSensorFront->getValue(0);
        if (colorFrontValue.ok())
        {
            _colorFrontValue = colorFrontValue.value();
        } else {
            LOG4CPLUS_ERROR(_logger, "Error reading front color sensor");
        }
    }

    absl::StatusOr<int> SensorManager::readGyro()
    {
        LOG4CPLUS_TRACE(_logger, "SensorManager::readGyro()");
        
        absl::StatusOr<int> gyroValue = _gyroSensor->getValue(0);
        if (!gyroValue.ok())
        {
            LOG4CPLUS_ERROR(_logger, "Error reading gyro sensor");
            return absl::InternalError("Error reading gyro sensor");
        }
        _gyroValue = gyroValue.value();
        return _gyroValue;
    }

    absl::StatusOr<int> SensorManager::readColorLeft()
    {
        LOG4CPLUS_TRACE(_logger, "SensorManager::readColorLeft()");

        absl::StatusOr<int> colorLeftValue = _colorSensorLeft->getValue(0);
        if (!colorLeftValue.ok())
        {
            LOG4CPLUS_ERROR(_logger, "Error reading left color sensor");
            return absl::InternalError("Error reading left color sensor");
        }
        _colorLeftValue = colorLeftValue.value();
        return _colorLeftValue;
    }

    absl::StatusOr<int> SensorManager::readColorRight()
    {
        LOG4CPLUS_TRACE(_logger, "SensorManager::readColorRight()");
        
        absl::StatusOr<int> colorRightValue = _colorSensorRight->getValue(0);
        if (!colorRightValue.ok())
        {
            LOG4CPLUS_ERROR(_logger, "Error reading right color sensor");
            return absl::InternalError("Error reading right color sensor");
        }
        _colorRightValue = colorRightValue.value();
        return _colorRightValue;
    }

    absl::StatusOr<int> SensorManager::readColorFront()
    {
        LOG4CPLUS_TRACE(_logger, "SensorManager::readColorFront()");

        absl::StatusOr<int> colorFrontValue = _colorSensorFront->getValue(0);
        if (!colorFrontValue.ok())
        {
            LOG4CPLUS_ERROR(_logger, "Error reading front color sensor");
            return absl::InternalError("Error reading front color sensor");
        }
        _colorFrontValue = colorFrontValue.value();
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

                absl::StatusOr<int> gyroValue = _gyroSensor->getValue(0);
                if (gyroValue.ok() && gyroValue.value() != _gyroValue)
                {
                    _gyroValue = gyroValue.value();
                    for (auto const& [port, callback] : _eventListeners)
                    {
                        if (port == DeviceID::GYRO || port == DeviceID::ANY) {
                            callback(DeviceID::GYRO, _gyroValue);
                        }
                    }
                }

                absl::StatusOr<int> colorLeftValue = _colorSensorLeft->getValue(0);
                if (colorLeftValue.ok() && colorLeftValue.value() != _colorLeftValue)
                {
                    _colorFrontValue = colorLeftValue.value();
                    for (auto const& [port, callback] : _eventListeners)
                    {
                        if (port == DeviceID::COLOR_LEFT || port == DeviceID::ANY) {
                            callback(DeviceID::COLOR_LEFT, _colorFrontValue);
                        }
                    }
                }

                absl::StatusOr<int> colorRightValue = _colorSensorRight->getValue(0);
                if (colorRightValue.ok() && colorRightValue.value() != _colorRightValue)
                {
                    _colorRightValue = colorRightValue.value();
                    for (auto const& [port, callback] : _eventListeners)
                    {
                        if (port == DeviceID::COLOR_RIGHT || port == DeviceID::ANY) {
                            callback(DeviceID::COLOR_RIGHT, _colorRightValue);
                        }
                    }
                }

                absl::StatusOr<int> colorFrontValue = _colorSensorFront->getValue(0);
                if (colorFrontValue.ok() && colorFrontValue.value() != _colorFrontValue)
                {
                    _colorFrontValue = colorFrontValue.value();
                    for (auto const& [port, callback] : _eventListeners)
                    {
                        if (port == DeviceID::COLOR_FRONT || port == DeviceID::ANY) {
                            callback(DeviceID::COLOR_FRONT, _colorFrontValue);
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