#ifndef __ROBOTMOVEMENT_HPP__
#define __ROBOTMOVEMENT_HPP__

#include <vector>
#include <string>
#include <memory>
#include <future>
#include <mutex>
#include <physical/DeviceManager.hpp>
#include <physical/portManager/port/MotorPort.hpp>
#include <physical/portManager/port/SensorPort.hpp>
#include <console/Logger.hpp>

#define LEFT_RIGHT_SWITCH -1

namespace finder::robot
{
    class RobotMovement
    {
        public:
            RobotMovement();
            ~RobotMovement();

            static void moveForward();
            static void moveForward(int distance);
            static void moveForward(int distance, int speed);

            static void moveBackward();
            static void moveBackward(int distance);
            static void moveBackward(int distance, int speed);

            static void turnLeft();
            static void turnLeft(int angle);
            static void turnLeft(int angle, int speed);

            static void turnRight();
            static void turnRight(int angle);
            static void turnRight(int angle, int speed);

            static void turnArcLeft(int angle);
            static void turnArcLeft(int angle, int speed);

            static void turnArcRight(int angle);
            static void turnArcRight(int angle, int speed);

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
            static std::mutex _movementIDMutex;

            static std::future<void> _movementFuture;
    };
} // namespace finder::robot

#endif // __ROBOTMOVEMENT_HPP__ 