#ifndef __ROBOTMOVEMENT_HPP__
#define __ROBOTMOVEMENT_HPP__

#include <vector>
#include <string>
#include <memory>
#include <future>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <physical/DeviceManager.hpp>
#include <physical/portManager/port/MotorPort.hpp>
#include <physical/portManager/port/SensorPort.hpp>
#include <console/Logger.hpp>
#include "MovementAction.hpp"

#define LEFT_RIGHT_SWITCH -1

namespace finder::robot
{
    class RobotMovement
    {
        public:
            RobotMovement();
            ~RobotMovement();

            static void move(MovementType type, int distance, int speed, float arcRatio);

            static void stop();


            static void setSpeed(int speed);
            static void setDutyCycle(int dutyCycle);

            static void awaitMotorReady();

        
        private:
            static std::shared_ptr<physical::MotorPort> _motorLeft;
            static std::shared_ptr<physical::MotorPort> _motorRight;
            static std::shared_ptr<physical::MotorPort> _motorShift;
            static std::shared_ptr<physical::MotorPort> _motorTool;

            static int _speed;
            static int _dutyCycle;

            static finder::console::Logger _logger;

            static unsigned long int _movementID;
            static unsigned long int _movementIDAhead;
            static std::mutex _movementIDMutex;

            static std::queue<std::future<void>> _movementFuture;
            static std::mutex _movementFutureMutex;

            static std::queue<std::shared_ptr<std::condition_variable>> _movementQueueCV;
            static std::queue<std::shared_ptr<std::mutex>> _movementQueueCVMutex;
            
            static void processQueueChanges();
    };
} // namespace finder::robot

#endif // __ROBOTMOVEMENT_HPP__ 