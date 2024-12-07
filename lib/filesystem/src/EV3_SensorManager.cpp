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

    SensorManager::SensorManager(std::string portBasePath) : DeviceManager(portBasePath)
    {
        spdlog::trace("SensorManager::SensorManager(std::string portBasePath)");

        _dispatcherFuture = std::thread(Dispatcher);
    }

    SensorManager::~SensorManager()
    {
        spdlog::trace("SensorManager::~SensorManager()");

        _stopDispatcher = true;
        _dispatcherFuture.join();
    }

    void SensorManager::readAllSensors()
    {
        spdlog::trace("SensorManager::readAllSensors()");

        absl::StatusOr<int> gyroValue = _gyroSensor->getValue(0);
        if (gyroValue.ok())
        {
            _gyroValue = gyroValue.value();
        } else {
            spdlog::error("Error reading gyro sensor");
        }

        absl::StatusOr<int> colorLeftValue = _colorSensorLeft->getValue(0);
        if (colorLeftValue.ok())
        {
            _colorLeftValue = colorLeftValue.value();
        } else {
            spdlog::error("Error reading left color sensor");
        }

        absl::StatusOr<int> colorRightValue = _colorSensorRight->getValue(0);
        if (colorRightValue.ok())
        {
            _colorRightValue = colorRightValue.value();
        } else {
            spdlog::error("Error reading right color sensor");
        }

        absl::StatusOr<int> colorFrontValue = _colorSensorFront->getValue(0);
        if (colorFrontValue.ok())
        {
            _colorFrontValue = colorFrontValue.value();
        } else {
            spdlog::error("Error reading front color sensor");
        }
    }

    absl::StatusOr<int> SensorManager::readGyro()
    {
        spdlog::trace("SensorManager::readGyro()");
        
        absl::StatusOr<int> gyroValue = _gyroSensor->getValue(0);
        if (!gyroValue.ok())
        {
            spdlog::error("Error reading gyro sensor");
            return absl::InternalError("Error reading gyro sensor");
        }
        _gyroValue = gyroValue.value();
        return _gyroValue;
    }

    absl::StatusOr<int> SensorManager::readColorLeft()
    {
        spdlog::trace("SensorManager::readColorLeft()");

        absl::StatusOr<int> colorLeftValue = _colorSensorLeft->getValue(0);
        if (!colorLeftValue.ok())
        {
            spdlog::error("Error reading left color sensor");
            return absl::InternalError("Error reading left color sensor");
        }
        _colorLeftValue = colorLeftValue.value();
        return _colorLeftValue;
    }

    absl::StatusOr<int> SensorManager::readColorRight()
    {
        spdlog::trace("SensorManager::readColorRight()");
        
        absl::StatusOr<int> colorRightValue = _colorSensorRight->getValue(0);
        if (!colorRightValue.ok())
        {
            spdlog::error("Error reading right color sensor");
            return absl::InternalError("Error reading right color sensor");
        }
        _colorRightValue = colorRightValue.value();
        return _colorRightValue;
    }

    absl::StatusOr<int> SensorManager::readColorFront()
    {
        spdlog::trace("SensorManager::readColorFront()");

        absl::StatusOr<int> colorFrontValue = _colorSensorFront->getValue(0);
        if (!colorFrontValue.ok())
        {
            spdlog::error("Error reading front color sensor");
            return absl::InternalError("Error reading front color sensor");
        }
        _colorFrontValue = colorFrontValue.value();
        return _colorFrontValue;
    }
    
    void SensorManager::addEventListeners(DeviceID port, std::function<void(DeviceID, int)> callback)
    {
        spdlog::trace("SensorManager::addEventListeners())");

        _eventListeners[port] = callback;
    }

    void SensorManager::Dispatcher()
    {
        spdlog::trace("SensorManager::Dispatcher()");

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