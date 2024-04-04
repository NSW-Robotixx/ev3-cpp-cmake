#include "SensorManager.hpp"

namespace finder::physical
{
    SensorManager::SensorManager() : DeviceManager()
    {
    }

    SensorManager::~SensorManager()
    {
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
    
    void SensorManager::Dispatcher()
    {
        
    }
} // namespace finder::physical