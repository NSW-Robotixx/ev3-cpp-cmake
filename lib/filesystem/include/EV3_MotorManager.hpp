#ifndef __MOTOR_MANAGER_HPP__
#define __MOTOR_MANAGER_HPP__

#include <DeviceManager.hpp>
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>

namespace finder::physical
{
    enum struct LaunchType
    {
        IMMEDIATE = 0,
        DEFFERED = 1,
    };

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
            MotorManager(std::string portBasePath);
            ~MotorManager();

            static void setMotorSpeed(DeviceID motor, int speed);
            static void moveForward(LaunchType launch, int speed, int distance, std::function<void()> stopCallback);

            static void moveBackward(LaunchType launch, int speed, int distance, std::function<void()> stopCallback);

            static void turnLeft(LaunchType launch, int speed, int distance, std::function<void()> stopCallback);

            static void turnRight(LaunchType launch, int speed, int distance, std::function<void()> stopCallback);

            static void stopAllMotors();
            static void stopMotor(DeviceID motor);

            static void onDirectionChange(std::function<void(TurnDirection)> callback);

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