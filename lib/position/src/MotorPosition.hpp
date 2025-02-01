#pragma once

#include <Vector2.hpp>
#include <EV3_MotorManager.hpp> 

namespace finder::position
{
    /// @brief Class that represents the motor position and handles the motor position estimate
    class MotorPosition : public physical::DeviceManager
    {
        public:
            /// @brief Constructor
            /// @param base_path Path to the base directory of the ports
            MotorPosition(std::string base_path);
            ~MotorPosition();

            /// @brief Update the position estimate of the robot
            static void updatePosition();

            /// @brief Initialize the motor position estimate
            static void init();

            /// @brief Get the current position of the robot
            /// @return The current position estimate of the robot
            static inline math::Vector2 getPosition() {
                spdlog::debug("Getting position: " + std::to_string(_position.x) + " " + std::to_string(_position.y));
                return _position; 
            }

            /// @brief Get the current angle of the robot
            /// @return The current angle estimate of the robot
            static inline float getAngle() { return _angle; }

            static inline void setPosition(math::Vector2 position) { _position = position; }

        private:
            static math::Vector2 _prev_motor_position;
            static math::Vector2 _position;
            static float _angle;
    };
}