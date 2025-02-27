#ifndef __MOVEMENT_ENGINE_HPP__
#define __MOVEMENT_ENGINE_HPP__

#include <DeviceManager.hpp>
#include <EV3_SensorManager.hpp>
#include <Vector2.hpp>
#include <Line.hpp>
#include <Position.hpp>
#include <EV3_ObstacleManager.hpp>
#include "../../EV3_conf.hpp"
#include "../../EV3_macros.hpp"
#include <queue>
#include <chrono>

namespace finder::engines::movement
{
    using namespace finder::physical;

    /// @brief Manage the connected motors
    class MovementEngine : public finder::physical::DeviceManager
    {
        public:
            /// @brief Constructor for MovementEngine
            /// @param portBasePath Path to the base path of the motors
            MovementEngine(std::string portBasePath);
            ~MovementEngine();

            /// @brief Move the robot to a point
            /// @param destination Point to move to
            static void moveToPoint(math::Vector3 destination);

            /// @brief Set the speed of the drive motors
            /// @param speed Speed of the motors
            static void setSpeed(int speed);

            /// @brief Set the duty cycle of the drive motors
            /// @param dutyCycle Duty cycle of the motors
            static void setDutyCycle(int dutyCycle);

            /// @brief Set the duty cycle of the drive motors
            /// @param dutyCycleLeft Duty cycle of the left motor
            /// @param dutyCycleRight Duty cycle of the right motor
            static void setDutyCycle(int dutyCycleLeft, int dutyCycleRight);

            /// @brief Move the robot forward
            /// @param distance Distance to move
            /// @param speed Speed of the motors
            static void moveForward(int distance, int speed);

            /// @brief Move the robot direct forward
            /// @param speed Speed of the motors
            static void moveForwardDirect(int speed);

            /// @brief Move the robot direct forward
            /// @param speedLeft Speed of the left motor
            /// @param speedRight Speed of the right motor
            static void moveForwardDirect(int speedLeft, int speedRight);

            /// @brief Move the robot backward
            /// @param distance Distance to move
            /// @param speed Speed of the motors
            static void moveBackward(int distance, int speed);

            /// @brief Turn the robot
            /// @param direction Direction to turn
            /// @param distance Distance to turn
            /// @param speed Speed of the motors
            static void turn(TurnDirection direction, int distance, int speed);

            /// @brief Stop the motors
            static void stop();

            /// @brief Get the distance of motor
            /// @param port Port of the motor
            /// @return Distance of the motor
            boost::leaf::result<int> getPosition(DeviceID port);

            /// @brief Get the speed of motor
            /// @param port Port of the motor
            /// @return Speed of the motor
            boost::leaf::result<int> getSpeed(DeviceID port);

            /// @brief Get the state of the motor
            /// @param port Port of the motor
            /// @return State of the motor
            boost::leaf::result<std::vector<MotorState>> getState(DeviceID port);

        private:
            static int _target_angle;
    };
}


#endif//__MOVEMENT_ENGINE_HPP__