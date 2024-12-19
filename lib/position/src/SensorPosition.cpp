#include "SensorPosition.hpp"


namespace finder::position {
    std::deque<math::Vector3> SensorPosition::_sensorLineOrder;
    float SensorPosition::_angle;
    TurnDirection SensorPosition::_lastDirection;

    SensorPosition::SensorPosition(std::string portBasePath) {
        spdlog::trace("Initializing SensorPosition");
    }

    void SensorPosition::update(DeviceID port, int value) {
        if (port == DeviceID::GYRO)
        {
            updateGyro(value);
            return;
        }

        if (value <= EV3_COLOR_SENSOR_TRIGGER) 
        {
            return;
        }
        
        switch (port)
        {
        case DeviceID::COLOR_LEFT:
            updateColorLeft(value);
            break;

        case DeviceID::COLOR_RIGHT:
            updateColorRight(value);
            break;

        case DeviceID::COLOR_FRONT:
            updateColorFront(value);
            break;

        default:
            throw std::invalid_argument("Port is probably not a sensor port");
            break;
        }
    }

    void SensorPosition::init() {
        SensorManager::addEventListeners(DeviceID::ANY_SENSOR, &update);
    }
    
    void SensorPosition::movementDirectionChange(TurnDirection direction)
    {
        if (direction == _lastDirection)
        {
            return;
        }

        // not needed yet, because no line recognition is implemented for movement direction changes

        // if (direction == TurnDirection::FORWARD && _lastDirection == TurnDirection::BACKWARD) {
        //     _sensorLineOrder.clear();
        // } 
        // else if (direction == TurnDirection::BACKWARD && _lastDirection == TurnDirection::FORWARD)
        // {
        //     _sensorLineOrder.clear();
        // }

        // past line recognitions can not be used
        _sensorLineOrder.clear();


        _lastDirection = direction;
    }
    
    void SensorPosition::updateColorLeft(int value)
    {
        _sensorLineOrder.push_back({MotorPosition::getPosition(), _angle});
    }
    
    void SensorPosition::updateColorRight(int value)
    {
        _sensorLineOrder.push_back({MotorPosition::getPosition(), _angle});
    }
    
    void SensorPosition::updateColorFront(int value)
    {
        _sensorLineOrder.push_back({MotorPosition::getPosition(), _angle});
    }
    
    void SensorPosition::updateGyro(int value)
    {
        // sensor value range is too big
        _angle = value % 360;
    }
    
    void SensorPosition::updatePosition()
    {
        if (_sensorLineOrder.size() >= 2) 
        {

        }
    }
}