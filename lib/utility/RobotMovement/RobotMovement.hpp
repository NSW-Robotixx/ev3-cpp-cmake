#ifndef __ROBOTMOVEMENT_HPP__
#define __ROBOTMOVEMENT_HPP__

#include <vector>
#include <string>
#include <memory>
#include <future>
#include <mutex>
#include <queue>
#include <functional>
#include <atomic>
#include <condition_variable>
#include <physical/DeviceManager.hpp>
#include <console/Logger.hpp>
#include "MovementAction.hpp"

#define LEFT_RIGHT_SWITCH -1

namespace finder::robot
{
    class RobotMovement : public physical::DeviceManager
    {

        public:
            enum class MovementType {
                FORWARD = 0,
                BACKWARD = 1,
                TURN_LEFT = 2,
                TURN_RIGHT = 3,
                TURN_ARC_LEFT = 4,
                TURN_ARC_RIGHT = 5
            };

            RobotMovement(std::string portBasePath);
            ~RobotMovement();

            void move(MovementType type, int distance, int speed, float arcRatio);

            void stop();


            void setSpeed(int speed);
            void setDutyCycle(int dutyCycle);

            void awaitMotorReady();

            void processMovementQueue();


        
        private:
            int _speed;
            int _dutyCycle;
            double _arcRatio;

            static std::atomic<bool> _isProcessingMovementQueue;

            static finder::console::Logger _logger;

            static unsigned long int _movementID;

            static std::queue<std::function<void(int, int, double)>> _movementQueue;
            static std::mutex _movementQueueMutex;

            static std::future<void> _movementQueueFuture;
            
            static void moveForward(int distance, int speed, float arcRatio);
            static void moveBackward(int distance, int speed, float arcRatio);
            static void turnLeft(int distance, int speed, float arcRatio);
            static void turnRight(int distance, int speed, float arcRatio);
            static void turnArcLeft(int distance, int speed, float arcRatio);
            static void turnArcRight(int distance, int speed, float arcRatio);
    };
} // namespace finder::robot

#endif // __ROBOTMOVEMENT_HPP__ 