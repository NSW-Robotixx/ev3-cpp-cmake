#ifndef __MOTOR_MANAGER_HPP__
#define __MOTOR_MANAGER_HPP__

#include <DeviceManager.hpp>
#include <EV3_SensorManager.hpp>
#include "../../EV3_conf.hpp"
#include "../../EV3_macros.hpp"
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>

#include <boost/exception/diagnostic_information.hpp>

namespace finder::physical
{
    /// @brief Enum for turn directions
    enum struct TurnDirection
    {
        LEFT = 0,
        RIGHT = 1,
        FORWARD = 2,
        BACKWARD = 3,
    };

    /// @brief Manage the connected motors
    class MotorManager : public DeviceManager
    {
        public:
            /// @brief Constructor for MotorManager
            /// @param portBasePath Path to the base path of the motors
            MotorManager(std::string portBasePath);
            ~MotorManager();

            /// @brief Set the speed of the drive motors
            /// @param speed Speed of the motors
            static void setSpeed(int speed);

            /// @brief Set the duty cycle of the drive motors
            /// @param dutyCycle Duty cycle of the motors
            static void setDutyCycle(int dutyCycle);

            /// @brief Set the duty cycle of the drive motors
            /// @param dutyCycle Duty cycle of the motors
            static void setDutyCycle(int dutyCycleLeft, int dutyCycleRight);

            /// @brief Move the robot forward
            /// @param distance Distance to move
            /// @param speed Speed of the motors
            static void moveForward(int distance, int speed);

            /// @brief Move the robot direct forward
            /// @param speed Speed of the motors
            static void moveForwardDirect(int speed);

            /// @brief Move the robot direct forward
            /// @param speed Speed of the motors
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

            };
}


#endif//__MOTOR_MANAGER_HPP__