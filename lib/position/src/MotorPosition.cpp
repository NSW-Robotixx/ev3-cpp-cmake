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
        
        int position_left = _motorLeft->getPosition();
        int position_right = _motorRight->getPosition();

        math::Vector2 moved_distance = math::Vector2(0, 0);

        // calculate the distance the robot has moved as Vector2
        moved_distance.x = (position_right - _prev_motor_position.x) * EV3_MOTOR_DISTANCE_PER_DEGREE;
        moved_distance.y = (position_left - _prev_motor_position.y) * EV3_MOTOR_DISTANCE_PER_DEGREE;

        if (moved_distance.x >= EV3_POSITION_JUMP_TOLERANCE || moved_distance.y >= EV3_POSITION_JUMP_TOLERANCE)
        {
            spdlog::warn("MotorPosition::updatePosition() - Jump detected: x: {}, y: {}, ignoring step", moved_distance.x, moved_distance.y);
            return;
        }

        // calculate the angle the robot has turned
        float motor_pos_dif = position_right - position_left; // kreisbogenlaenge
        float turned_angle = motor_pos_dif / EV3_MOTOR_TURN_CIRCLE; // kreisbogenlaenge / kreisumfang = winkel
        

        // update the position estimate
        _position += moved_distance;
        _angle += turned_angle;

        // update the previous motor position
        _prev_motor_position = math::Vector2(position_left, position_right);
    }

    void MotorPosition::init()
    {
        
    }

} // namespace finder::position
