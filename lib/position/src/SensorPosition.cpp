#include "SensorPosition.hpp"


namespace finder::position {
    std::deque<Eigen::Vector3d> SensorPosition::_sensorLineOrder;
    float SensorPosition::_angle;
    TurnDirection SensorPosition::_lastDirection;

    std::deque<Eigen::Vector3i> SensorPosition::_prev_color_values_front;
    std::deque<Eigen::Vector3i> SensorPosition::_prev_color_values_left;
    std::deque<Eigen::Vector3i> SensorPosition::_prev_color_values_right;
    std::deque<int> SensorPosition::_prev_gyro_values;

    Eigen::Vector2d SensorPosition::_sensorPosition;

    const Eigen::Vector2d SensorPosition::EV3_SENSOR_COLOR_RIGHT_OFFSET_VECTOR{
        EV3_SENSOR_COLOR_RIGHT_OFFSET_X,
        EV3_SENSOR_COLOR_RIGHT_OFFSET_Y
    };
    const Eigen::Vector2d SensorPosition::EV3_SENSOR_COLOR_LEFT_OFFSET_VECTOR{
        EV3_SENSOR_COLOR_LEFT_OFFSET_X,
        EV3_SENSOR_COLOR_LEFT_OFFSET_Y
    };
    const Eigen::Vector2d SensorPosition::EV3_SENSOR_COLOR_FRONT_OFFSET_VECTOR{
        EV3_SENSOR_COLOR_FRONT_OFFSET_X,
        EV3_SENSOR_COLOR_FRONT_OFFSET_Y
    };

    SensorPosition::SensorPosition(std::string portBasePath) : DeviceManager(portBasePath){
        spdlog::trace("Initializing SensorPosition");

        #if EV3_COLOR_SENSOR_USE_RGB_MODE
            _colorSensorFront->setMode("RGB-RAW");
            _colorSensorLeft->setMode("RGB-RAW");
            _colorSensorRight->setMode("RGB-RAW");
            _gyroSensor->setMode("GYRO-ANG");
        #else
            _colorSensorFront->setMode("COL-REFLECT");
            _colorSensorLeft->setMode("COL-REFLECT");
            _colorSensorRight->setMode("COL-REFLECT");
            _gyroSensor->setMode("GYRO-ANG");
        #endif
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
    }
    
    void SensorPosition::updateColorRight(int value)
    {
    }
    
    void SensorPosition::updateColorFront(int value)
    {
    }
    
    void SensorPosition::updateGyro(int value)
    {
        // sensor value range is too big
        _angle = value % 360;
    }
    
    void SensorPosition::updatePosition()
    {
        #if EV3_COLOR_SENSOR_USE_RGB_MODE
            Eigen::Vector3i color_values_front(
                _colorSensorFront->getValue(0).value(),
                _colorSensorFront->getValue(1).value(),
                _colorSensorFront->getValue(2).value()
            );

            Eigen::Vector3i color_values_left(
                _colorSensorLeft->getValue(0).value(),
                _colorSensorLeft->getValue(1).value(),
                _colorSensorLeft->getValue(2).value()
            );

            Eigen::Vector3i color_values_right(
                _colorSensorRight->getValue(0).value(),
                _colorSensorRight->getValue(1).value(),
                _colorSensorRight->getValue(2).value()
            );


            _prev_color_values_front.push_back(color_values_front);
            _prev_color_values_left.push_back(color_values_left);
            _prev_color_values_right.push_back(color_values_right);

            for (size_t i = 0; i < _prev_color_values_front.size(); i++)
            {
                if (color_values_front[i] >= EV3_COLOR_SENSOR_TRIGGER && _prev_color_values_front.size() - 1 < color_values_front[i])
                {
                    Eigen::Vector2d sensorPosition = _sensorPosition + EV3_SENSOR_COLOR_FRONT_OFFSET_VECTOR;
                    _sensorLineOrder.push_back(Eigen::Vector3d{sensorPosition.x(), sensorPosition.y(), _angle});
                }

                if (color_values_left[i] >= EV3_COLOR_SENSOR_TRIGGER && _prev_color_values_left.size() - 1 < color_values_left[i])
                {
                    Eigen::Vector2d sensorPosition = _sensorPosition + EV3_SENSOR_COLOR_LEFT_OFFSET_VECTOR;
                    _sensorLineOrder.push_back(Eigen::Vector3d{
                        sensorPosition.x(),
                        sensorPosition.y(),
                        _angle
                    });;
                }

                if (color_values_right[i] >= EV3_COLOR_SENSOR_TRIGGER && _prev_color_values_right.size() - 1 < color_values_right[i])
                {
                    Eigen::Vector2d sensorPosition = _sensorPosition + EV3_SENSOR_COLOR_RIGHT_OFFSET_VECTOR;
                    _sensorLineOrder.push_back(Eigen::Vector3d{
                        sensorPosition.x(),
                        sensorPosition.y(),
                        _angle
                    });
                }
            }

            _prev_gyro_values.push_back(_gyroSensor->getValue(0).value());

            _angle = _prev_gyro_values.back();
            
                        
            if (_prev_color_values_front.size() >= EV3_COLOR_SENSOR_BACKLOG)
            {
                _prev_color_values_front.pop_front();
            }

            if (_prev_color_values_left.size() >= EV3_COLOR_SENSOR_BACKLOG)
            {
                _prev_color_values_left.pop_front();
            }

            if (_prev_color_values_right.size() >= EV3_COLOR_SENSOR_BACKLOG)
            {
                _prev_color_values_right.pop_front();
            }

            if (_prev_gyro_values.size() >= EV3_GYRO_SENSOR_BACKLOG)
            {
                _prev_gyro_values.pop_front();
            }

        #else

        #endif
    }
}