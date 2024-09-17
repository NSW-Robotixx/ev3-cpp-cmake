#ifndef __MOTOR_MANAGER_HPP__
#define __MOTOR_MANAGER_HPP__

#include <DeviceManager.hpp>
#include <EV3_SensorManager.hpp>
#include "../../EV3_conf.hpp"
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>

namespace finder::physical
{

    /// @brief Enum for launch types
    enum struct LaunchType
    {
        IMMEDIATE = 0,
        DEFFERED = 1,
    };

    /// @brief Enum for turn directions
    enum struct TurnDirection
    {
        LEFT = 0,
        RIGHT = 1,
        FORWARD = 2,
        BACKWARD = 3,
    };

    class MotorManager : public DeviceManager
    {
        public:
            /// @brief Constructor for MotorManager
            MotorManager(std::string portBasePath);
            ~MotorManager();

            /// @brief Set the speed of a motor
            /// @param motor Which motor to set the speed for
            /// @param speed Speed to set the motor to. Positive for forward, negative for backward. Has to be less than or equal to max speed. See getMaxSpeed().
            static void setMotorSpeed(DeviceID motor, int speed);

            /// @brief Move the robot forward.
            /// @param launch Async or not.
            /// @param speed Max speed to move the motor at
            /// @param distance Distance to move.
            /// @param stopCallback Function to call when the movement has finished.
            static void moveForward(LaunchType launch, int speed, int distance, std::function<void()> stopCallback);

            /// @brief Move the robot backward.
            /// @param launch Async or not.
            /// @param speed Max speed to move at
            /// @param distance 
            /// @param stopCallback 
            static void moveBackward(LaunchType launch, int speed, int distance, std::function<void()> stopCallback);

            static void turnLeft(LaunchType launch, int speed, int distance, std::function<void()> stopCallback);

            static void turnRight(LaunchType launch, int speed, int distance, std::function<void()> stopCallback);

            static void onDirectionChange(std::function<void(TurnDirection)> callback);

            static int getMaxSpeed();

        private:
            static void move(LaunchType launch, int speed, int distance, std::function<void()> stopCallback);
            static void turn(LaunchType launch, int speed, int distance, std::function<void()> stopCallback, TurnDirection direction);

            static void moveNow(int speed, int distance, std::function<void()> stopCallback);
            // static void moveAsync(int speed, int distance, std::function<void()> stopCallback, DeviceID motor);

            static TurnDirection _prevTurnDirection;

            static std::vector<std::function<void(TurnDirection)>> _directionChangeListeners;
    };
}


#endif//__MOTOR_MANAGER_HPP__