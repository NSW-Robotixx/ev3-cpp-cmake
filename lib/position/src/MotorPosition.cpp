#include "MotorPosition.hpp"
#include <EV3_SensorManager.hpp>

namespace finder::position
{
    math::Vector2 MotorPosition::_prev_motor_position = math::Vector2(0, 0);
    math::Vector2 MotorPosition::_position = math::Vector2(EV3_ROBOT_POSITION_X, EV3_ROBOT_POSITION_Y);
    float MotorPosition::_angle;

    MotorPosition::MotorPosition(std::string base_path) : physical::DeviceManager(base_path)
    {
        init();
    }

    MotorPosition::~MotorPosition()
    {
    }

    void MotorPosition::updatePosition()
    {
        spdlog::trace("MotorPosition::updatePosition()");
        
        int motor_position_left = _motorLeft->getPosition();
        int motor_position_right = _motorRight->getPosition();

        math::Vector2 moved_distance = math::Vector2(0, 0);

        // calculate the distance the robot has moved as Vector2
        moved_distance.x = (motor_position_right - _prev_motor_position.x) / EV3_MOTOR_DISTANCE_PER_DEGREE;
        moved_distance.y = (motor_position_left - _prev_motor_position.y) / EV3_MOTOR_DISTANCE_PER_DEGREE;

        float abs_moved_distance_x = abs(moved_distance.x);
        float abs_moved_distance_y = abs(moved_distance.y);
        if (abs_moved_distance_x > EV3_POSITION_JUMP_TOLERANCE || abs_moved_distance_y > EV3_POSITION_JUMP_TOLERANCE)
        {
            spdlog::warn("MotorPosition::updatePosition() - Jump detected: x: {}, y: {}, ignoring step. Previous positions: left: {}, right: {}", moved_distance.x, moved_distance.y, _prev_motor_position.x, _prev_motor_position.y);
            _prev_motor_position = math::Vector2(motor_position_right, motor_position_left);
            return;
        }

        // calculate the angle the robot has turned
        float motor_position_difference = moved_distance.x - moved_distance.y; // kreisbogenlaenge
        float calculated_turn_angle = motor_position_difference / EV3_MOTOR_TURN_CIRCLE; // kreisbogenlaenge / kreisumfang = winkel
        
        // update the robot's angle
        _angle += calculated_turn_angle * 360.0; // convert turn angle to degrees
        _angle = fmod(_angle + 360.0, 360.0); // normalize the angle to be within 0-360 degrees


        // update the position estimate
        double length = sqrt(moved_distance.x * moved_distance.x + moved_distance.y * moved_distance.y);
        float angle_radians = _gyroSensor->getValue(0).value() * M_PI / 180.0;
        
        _position.x += cos(angle_radians) * length;
        _position.y += sin(angle_radians) * length;
        
        // _angle = fmod((atan2(moved_distance.y, moved_distance.x) * 180 / M_PI) + 360, 360);

        // update the previous motor position
        _prev_motor_position = math::Vector2(motor_position_right, motor_position_left);

        spdlog::debug("MotorPosition::updatePosition() - Position: " + std::to_string(_position.x) + "," + std::to_string(_position.y) + " Angle: " + std::to_string(_angle));
    }

    void MotorPosition::init()
    {
        _motorLeft->reset();
        _motorRight->reset();
        _prev_motor_position = math::Vector2(_motorRight->getPosition(), _motorLeft->getPosition());
        // _position = math::Vector2(_motorRight->getPosition(), _motorLeft->getPosition());
        _angle = _gyroSensor->getValue(0).value();
        
    }

    void MotorPosition::setPosition(math::Vector2 position)
    {
        // warn if the delta is too big
        if (abs(_position.x - position.x) > EV3_POSITION_JUMP_TOLERANCE || abs(_position.y - position.y) > EV3_POSITION_JUMP_TOLERANCE)
        {
            spdlog::warn("MotorPosition::setPosition() - Jump detected: x: {}, y: {}", _position.x - position.x, _position.y - position.y);
        }
        _position = position;
    }

} // namespace finder::position
