#pragma once

#include "../../EV3_conf.hpp"

#include <MotorPosition.hpp>
#include <SensorPosition.hpp>
#include <Vector2.hpp>

namespace finder::position
{
    /// @brief  Class for getting the position of the EV3 robot using the sensors and motors.
    class Position
    {
        public:
            Position() = default;
            ~Position() = default;

            /// @brief Get the current position of the robot.
            /// @return Current position as a Vector2
            static math::Vector2 getPosition();

            /// @brief Get the current angle of the robot.
            /// @return Current angle in degrees
            static float getAngle();

        private:
            static finder::position::SensorPosition m_sensor_position;
            static finder::position::MotorPosition m_motor_position;
    };
} // namespace finder::position