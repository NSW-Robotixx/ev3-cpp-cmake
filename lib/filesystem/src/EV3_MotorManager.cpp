#include "EV3_MotorManager.hpp"

namespace finder::physical
{
    MotorManager::MotorManager(std::string portBasePath) : DeviceManager(portBasePath)
    {
        _motorLeft->setStopAction(MotorStopAction::HOLD);
        _motorRight->setStopAction(MotorStopAction::HOLD);
        _motorShift->setStopAction(MotorStopAction::HOLD);
        _motorTool->setStopAction(MotorStopAction::HOLD);
    }

    MotorManager::~MotorManager()
    {
        stopAllMotors();
    }

    void MotorManager::setMotorSpeed(DeviceID motor, int speed)
    {

        if (motor == DeviceID::MOTOR_LEFT)
        {
            _motorLeft->setSpeed(speed);
        }
        else if (motor == DeviceID::MOTOR_RIGHT)
        {
            _motorRight->setSpeed(speed);
        }
        else if (motor == DeviceID::MOTOR_SHIFT)
        {
            _motorShift->setSpeed(speed);
        }
        else if (motor == DeviceID::MOTOR_TOOL)
        {
            _motorTool->setSpeed(speed);
        }
        else
        {
            // throw error
        }
    }
    void MotorManager::moveForward(LaunchType launch, int speed = 200, int distance = 0, std::function<void()> stopCallback = nullptr)
    {
        move(launch, speed, distance, stopCallback);
    }

    void MotorManager::moveBackward(LaunchType launch, int speed = 200, int distance = 0, std::function<void()> stopCallback = nullptr)
    {
        move(launch, -speed, distance, stopCallback);
    }

    void MotorManager::turnLeft(LaunchType launch, int speed = 200, int distance = 0, std::function<void()> stopCallback = nullptr)
    {
        turn(launch, speed, distance, stopCallback, TurnDirection::LEFT);
    }


    void MotorManager::turnRight(LaunchType launch, int speed = 200, int distance = 0, std::function<void()> stopCallback = nullptr)
    {
        turn(launch, speed, distance, stopCallback, TurnDirection::RIGHT);
    }

    void MotorManager::stopAllMotors()
    {
        stopMotor(DeviceID::MOTOR_LEFT);
        stopMotor(DeviceID::MOTOR_RIGHT);
        stopMotor(DeviceID::MOTOR_SHIFT);
        stopMotor(DeviceID::MOTOR_TOOL);
    }

    void MotorManager::stopMotor(DeviceID motor)
    {
        switch (motor)
        {
        case DeviceID::MOTOR_LEFT:
            _motorLeft->stop();
            break;

        case DeviceID::MOTOR_RIGHT:
            _motorRight->stop();
            break;

        case DeviceID::MOTOR_SHIFT:
            _motorShift->stop();
            break;

        case DeviceID::MOTOR_TOOL:
            _motorTool->stop();
            break;
        
        default:
            break;
        }
    }

    void MotorManager::move(LaunchType launch, int speed, int distance, std::function<void()> stopCallback)
    {
        moveNow(speed, distance, stopCallback);
    }

    void MotorManager::turn(LaunchType launch, int speed, int distance, std::function<void()> stopCallback, TurnDirection direction)
    {
        // not implemented yet
    }

    void MotorManager::moveNow(int speed, int distance, std::function<void()> stopCallback)
    {
        while (!((_motorLeft->getState().front() != MotorState::HOLDING || _motorLeft->getState().front() != MotorState::STOPPED) &&
               (_motorRight->getState().front() != MotorState::HOLDING || _motorRight->getState().front() != MotorState::STOPPED)))
        {
            // wait
        }

        if (speed != 0)
            setMotorSpeed(DeviceID::MOTOR_LEFT, speed);
            setMotorSpeed(DeviceID::MOTOR_RIGHT, speed);

        if (distance != 0)
        {
            stopMotor(DeviceID::MOTOR_LEFT);
            stopMotor(DeviceID::MOTOR_RIGHT);

            _motorLeft->setPositionSp(distance);
            _motorRight->setPositionSp(distance);


            if (stopCallback != nullptr)
            {
                stopCallback();
            }
        }

    }
}