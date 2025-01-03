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

        boost::leaf::result<int> gyroValue = _gyroSensor->getValue(0);
        if (gyroValue)
        {
            _gyroValue = gyroValue.value();
        } else {
            spdlog::error("Error reading gyro sensor");
        }

        boost::leaf::result<int> colorLeftValue = _colorSensorLeft->getValue(0);
        if (colorLeftValue)
        {
            _colorLeftValue = colorLeftValue.value();
        } else {
            spdlog::error("Error reading left color sensor");
        }

        boost::leaf::result<int> colorRightValue = _colorSensorRight->getValue(0);
        if (colorRightValue)
        {
            _colorRightValue = colorRightValue.value();
        } else {
            spdlog::error("Error reading right color sensor");
        }

        boost::leaf::result<int> colorFrontValue = _colorSensorFront->getValue(0);
        if (colorFrontValue)
        {
            _colorFrontValue = colorFrontValue.value();
        } else {
            spdlog::error("Error reading front color sensor");
        }
    }

    boost::leaf::result<int> SensorManager::readGyro()
    {
        spdlog::trace("SensorManager::readGyro()");
        
        boost::leaf::result<int> gyroValue = _gyroSensor->getValue(0);
        if (!gyroValue)
        {
            spdlog::error("Error reading gyro sensor");
            return boost::leaf::new_error(std::runtime_error("Failed to read gyro sensor value"));
        }
        _gyroValue = gyroValue.value();
        return _gyroValue;
    }

    boost::leaf::result<int> SensorManager::readColorLeft()
    {
        spdlog::trace("SensorManager::readColorLeft()");

        boost::leaf::result<int> colorLeftValue = _colorSensorLeft->getValue(0);
        if (!colorLeftValue)
        {
            spdlog::error("Error reading left color sensor");
            return boost::leaf::new_error(std::runtime_error("Failed to read color sensor left value"));
        }
        _colorLeftValue = colorLeftValue.value();
        return _colorLeftValue;
    }

    boost::leaf::result<int> SensorManager::readColorRight()
    {
        spdlog::trace("SensorManager::readColorRight()");
        
        boost::leaf::result<int> colorRightValue = _colorSensorRight->getValue(0);
        if (!colorRightValue)
        {
            spdlog::error("Error reading right color sensor");
            return boost::leaf::new_error(std::runtime_error("Failed to read color sensor right value"));
        }
        _colorRightValue = colorRightValue.value();
        return _colorRightValue;
    }

    boost::leaf::result<int> SensorManager::readColorFront()
    {
        spdlog::trace("SensorManager::readColorFront()");

        boost::leaf::result<int> colorFrontValue = _colorSensorFront->getValue(0);
        if (!colorFrontValue)
        {
            spdlog::error("Error reading front color sensor");
            return boost::leaf::new_error(std::runtime_error("Failed to read color sensor front value"));
        }
        _colorFrontValue = colorFrontValue.value();
        return _colorFrontValue;
    }
    
    void SensorManager::addEventListeners(DeviceID port, std::function<void(DeviceID, int)> callback)
    {
        spdlog::trace("SensorManager::addEventListeners())");

        _eventListeners[port] = callback;
    }

    void SensorManager::calibrateGyroSensor()
    {
        spdlog::trace("SensorManager::calibrateGyroSensor()");

        boost::leaf::result<int> old_gyro_value = _gyroSensor->getValue(0);

        if (!old_gyro_value)
        {
            spdlog::error("Error reading first gyro sensor value");
            return;
        }


        spdlog::info("Calibrating gyro sensor, please do not move the robot");
        std::this_thread::sleep_for(std::chrono::milliseconds(EV3_GYRO_CALIBRATION_TIMEOUT_MS));

        boost::leaf::result<int> new_gyro_value = _gyroSensor->getValue(0);

        if (!new_gyro_value)
        {
            spdlog::error("Error reading second gyro sensor value");
            return;
        }

        if (std::abs(old_gyro_value.value() - new_gyro_value.value()) > 0)
        {
            spdlog::info("Gyro sensor drift detected, recalibrating...");

            _gyroSensor->calibrateGyro();

            spdlog::info("Gyro sensor recalibrated, rechecking values");

            calibrateGyroSensor();
        } else {
            spdlog::info("No drift detected, gyro sensor calibrated");
        }
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

                boost::leaf::result<int> gyroValue = _gyroSensor->getValue(0);
                if (gyroValue && gyroValue.value() != _gyroValue)
                {
                    _gyroValue = gyroValue.value();
                    for (auto const& [port, callback] : _eventListeners)
                    {
                        if (port == DeviceID::GYRO || port == DeviceID::ANY) {
                            callback(DeviceID::GYRO, _gyroValue);
                        }
                    }
                }

                boost::leaf::result<int> colorLeftValue = _colorSensorLeft->getValue(0);
                if (colorLeftValue && colorLeftValue.value() != _colorLeftValue)
                {
                    _colorFrontValue = colorLeftValue.value();
                    for (auto const& [port, callback] : _eventListeners)
                    {
                        if (port == DeviceID::COLOR_LEFT || port == DeviceID::ANY) {
                            callback(DeviceID::COLOR_LEFT, _colorFrontValue);
                        }
                    }
                }

                boost::leaf::result<int> colorRightValue = _colorSensorRight->getValue(0);
                if (colorRightValue && colorRightValue.value() != _colorRightValue)
                {
                    _colorRightValue = colorRightValue.value();
                    for (auto const& [port, callback] : _eventListeners)
                    {
                        if (port == DeviceID::COLOR_RIGHT || port == DeviceID::ANY) {
                            callback(DeviceID::COLOR_RIGHT, _colorRightValue);
                        }
                    }
                }

                boost::leaf::result<int> colorFrontValue = _colorSensorFront->getValue(0);
                if (colorFrontValue && colorFrontValue.value() != _colorFrontValue)
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