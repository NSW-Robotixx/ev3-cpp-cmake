#include "MotorPosition.hpp"
#include <EV3_SensorManager.hpp>

namespace finder::position
{
    math::Vector2 MotorPosition::_prev_motor_position = math::Vector2(0, 0);
    math::Vector2 MotorPosition::_position = math::Vector2(EV3_ROBOT_POSITION_X, EV3_ROBOT_POSITION_Y);
    float MotorPosition::_angle;
    math::Vector2 MotorPosition::_movement_start_position = math::Vector2(0, 0);
    math::Vector2 MotorPosition::_movement_end_position = math::Vector2(0, 0);
    math::Vector2 MotorPosition::_movement_start_robot_position = math::Vector2(0, 0);

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
        
        // Update angle (gyro sensor)
        _angle = fmod(_gyroSensor->getValue(0).value() + 360.0, 360.0);

        // Get motor positions
        int motor_position_left = _motorLeft->getPosition() / EV3_MOTOR_DISTANCE_PER_DEGREE;
        int motor_position_right = _motorRight->getPosition() / EV3_MOTOR_DISTANCE_PER_DEGREE;

        // Calculate percentage of movement completed for both motors
        double movement_range_right = abs(_movement_end_position.x - _movement_start_position.x);
        double movement_range_left = abs(_movement_end_position.y - _movement_start_position.y);

        double percent_arrived_right = abs(motor_position_right - _movement_start_position.x) / movement_range_right;
        double percent_arrived_left = abs(motor_position_left - _movement_start_position.y) / movement_range_left;

        // Logging for debugging
        spdlog::debug("MotorPosition::updatePosition() - Percent arrived: right: {}, left: {}", percent_arrived_right, percent_arrived_left);
        spdlog::debug("MotorPosition::updatePosition() - Movement start: {}, {}, Movement end: {}, {}", _movement_start_position.x, _movement_start_position.y, _movement_end_position.x, _movement_end_position.y);
        spdlog::debug("MotorPosition::updatePosition() - Motor position: right: {}, left: {}", motor_position_right, motor_position_left);
        spdlog::debug("MotorPosition::updatePosition() - Distance to move: right: {}, left: {}", movement_range_right, movement_range_left);

        // Calculate the average percentage arrived
        double average_percent_arrived = abs((percent_arrived_right + percent_arrived_left) / 2);

        // Calculate the new position based on average percent arrived
        // This assumes that _movement_start_position is a Vector (x, y)
        math::Vector2 travelled_position = math::Vector2(
            movement_range_right * average_percent_arrived,
            movement_range_left * average_percent_arrived
        );
        
        // Update the robot's position
        _position.x = _movement_start_robot_position.x + cos(_angle) * travelled_position.x;
        _position.y = _movement_start_robot_position.y + sin(_angle) * travelled_position.y;
        

        // int motor_position_left = _motorLeft->getPosition();
        // int motor_position_right = _motorRight->getPosition();

        // math::Vector2 moved_distance = math::Vector2(0, 0);

        // // calculate the distance the robot has moved as Vector2
        // moved_distance.x = (motor_position_right - _prev_motor_position.x) / EV3_MOTOR_DISTANCE_PER_DEGREE;
        // moved_distance.y = (motor_position_left - _prev_motor_position.y) / EV3_MOTOR_DISTANCE_PER_DEGREE;

        // float abs_moved_distance_x = abs(moved_distance.x);
        // float abs_moved_distance_y = abs(moved_distance.y);
        // if (abs_moved_distance_x > EV3_POSITION_JUMP_TOLERANCE || abs_moved_distance_y > EV3_POSITION_JUMP_TOLERANCE)
        // {
        //     spdlog::warn("MotorPosition::updatePosition() - Jump detected: x: {}, y: {}, ignoring step. Previous positions: left: {}, right: {}", moved_distance.x, moved_distance.y, _prev_motor_position.x, _prev_motor_position.y);
        //     _prev_motor_position = math::Vector2(motor_position_right, motor_position_left);
        //     return;
        // }

        // // calculate the angle the robot has turned
        // float motor_position_difference = moved_distance.x - moved_distance.y; // kreisbogenlaenge
        // float calculated_turn_angle = motor_position_difference / EV3_MOTOR_TURN_CIRCLE; // kreisbogenlaenge / kreisumfang = winkel
        
        // // update the robot's angle
        // _angle += calculated_turn_angle * 360.0; // convert turn angle to degrees
        // _angle = fmod(_angle + 360.0, 360.0); // normalize the angle to be within 0-360 degrees


        // // update the position estimate
        // double length = sqrt(moved_distance.x * moved_distance.x + moved_distance.y * moved_distance.y);
        // float angle_radians = _gyroSensor->getValue(0).value() * M_PI / 180.0;
        
        // _position.x += cos(angle_radians) * length;
        // _position.y += sin(angle_radians) * length;
        
        // // _angle = fmod((atan2(moved_distance.y, moved_distance.x) * 180 / M_PI) + 360, 360);

        // // update the previous motor position
        // _prev_motor_position = math::Vector2(motor_position_right, motor_position_left);

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
        // _position = position;
    }

    void MotorPosition::notifyMovementStart(int destination)
    {
        spdlog::trace("MotorPosition::notifyMovementStart()");

        _movement_start_position = math::Vector2(
            _motorRight->getPosition() / EV3_MOTOR_DISTANCE_PER_DEGREE, 
            _motorLeft->getPosition() / EV3_MOTOR_DISTANCE_PER_DEGREE
        );
        _movement_end_position = _movement_start_position + math::Vector2(destination, destination);

        _movement_start_robot_position = _position;

        spdlog::info("Movement started from position: {}, {} to position: {}, {}", 
                     _movement_start_position.x, _movement_start_position.y, 
                     _movement_end_position.x, _movement_end_position.y);
    }