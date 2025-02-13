#pragma once

#include <Vector2.hpp>
#include <EV3_MotorManager.hpp>
#include <Eigen/Dense>

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
            static inline Eigen::Vector2d getPosition() {
                spdlog::debug("Getting motor position: " + std::to_string(_position.x) + " " + std::to_string(_position.y));
                return Eigen::Vector2d(_position.x, _position.y); 
            }

            /// @brief Get the current angle of the robot
            /// @return The current angle estimate of the robot
            static inline float getAngle() { return _angle; }
            
            /// @brief Set the position of the robot
            /// @param position The new position of the robot
            static void setPosition(math::Vector2 position);

            /// @brief Notify of movement start
            /// @param destination The destination of the movement
            static void notifyMovementStart(int destination);

        private:
            static math::Vector2 _prev_motor_position;
            static math::Vector2 _position;
            static float _angle;
            static math::Vector2 _movement_start_position;
            static math::Vector2 _movement_end_position;
            static math::Vector2 _movement_start_robot_position;
    };
} // namespace finder::position