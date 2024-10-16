#include "EV3_MotorManager.hpp"

namespace finder::physical
{
    TurnDirection MotorManager::_prevTurnDirection = TurnDirection::FORWARD;
    std::vector<std::function<void(TurnDirection)>> MotorManager::_directionChangeListeners;
    
    /// @brief Constructor for MotorManager
    /// @param portBasePath Path to the base path of the motors
    MotorManager::MotorManager(std::string portBasePath) : DeviceManager(portBasePath)
    {
        _motorLeft->setStopAction(MotorStopAction::HOLD);
        _motorRight->setStopAction(MotorStopAction::HOLD);
        _motorShift->setStopAction(MotorStopAction::HOLD);
        _motorTool->setStopAction(MotorStopAction::HOLD);
    }

    MotorManager::~MotorManager()
    {
        _motorLeft->stop();
        _motorRight->stop();
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

    absl::Status MotorManager::turnLeft(LaunchType launch, int speed = 200, int distance = 0, std::function<void()> stopCallback = nullptr)
    {
        absl::Status status = turn(launch, speed, distance, stopCallback, TurnDirection::LEFT);
        if (!status.ok())
        {
            return status;
        }
        return absl::OkStatus();
    }


    absl::Status MotorManager::turnRight(LaunchType launch, int speed = 200, int distance = 0, std::function<void()> stopCallback = nullptr)
    {
        absl::Status status = turn(launch, speed, distance, stopCallback, TurnDirection::RIGHT);
        if (!status.ok())
        {
            return status;
        }
        return absl::OkStatus();
    }

    void MotorManager::onDirectionChange(std::function<void(TurnDirection)> callback)
    {
        _directionChangeListeners.push_back(callback);
    }

    int MotorManager::getMaxSpeed()
    {
        return _motorLeft->getMaxSpeed();
    }

    void MotorManager::move(LaunchType launch, int speed, int distance, std::function<void()> stopCallback)
    {
        moveNow(speed, distance, stopCallback);
    }

    absl::Status MotorManager::turn(LaunchType launch, int speed, int distance, std::function<void()> stopCallback, TurnDirection direction)
    {
        while (!((_motorLeft->getState().front() != MotorState::HOLDING || _motorLeft->getState().front() != MotorState::STOPPED) &&
               (_motorRight->getState().front() != MotorState::HOLDING || _motorRight->getState().front() != MotorState::STOPPED)))
        {
            // wait
        }

        if (direction == TurnDirection::LEFT)
        {
            _motorLeft->setDutyCycle(speed);
            _motorLeft->setCommand(MotorCommand::RUN_DIRECT);
        }
        else if (direction == TurnDirection::RIGHT)
        {
            _motorRight->setDutyCycle(speed);
            _motorRight->setCommand(MotorCommand::RUN_DIRECT);
        }

        // wait for the turn to finish
        while (true)
        {
            absl::StatusOr<int> gyroValue = SensorManager::readGyro();
            if (!gyroValue.ok())
            {
                return gyroValue.status();
            }

            if (direction == TurnDirection::LEFT)
            {
                if (gyroValue.value() < distance - EV3_GYRO_TURN_TOLERANCE)
                {
                    break;
                }
            }
            else if (direction == TurnDirection::RIGHT)
            {
                if (gyroValue.value() > distance + EV3_GYRO_TURN_TOLERANCE)
                {
                    break;
                }
            }
        }

        _motorLeft->stop();
        _motorRight->stop();

        return absl::OkStatus();
    }

    void MotorManager::moveNow(int speed, int distance, std::function<void()> stopCallback)
    {
        // call the direction change listeners
        if (speed < 0)
        {
            if (_prevTurnDirection == TurnDirection::BACKWARD) {
                for (auto listener : _directionChangeListeners)
                {
                    listener(TurnDirection::FORWARD);
                }
            }
            _prevTurnDirection = TurnDirection::BACKWARD;
        } else {
            if (_prevTurnDirection == TurnDirection::FORWARD) {
                for (auto listener : _directionChangeListeners)
                {
                    listener(TurnDirection::BACKWARD);
                }
            }
            _prevTurnDirection = TurnDirection::FORWARD;
        }

        while (!((_motorLeft->getState().front() != MotorState::HOLDING || _motorLeft->getState().front() != MotorState::STOPPED) &&
               (_motorRight->getState().front() != MotorState::HOLDING || _motorRight->getState().front() != MotorState::STOPPED)))
        {
            // wait
        }

        if (speed != 0)
            _motorLeft->setSpeed(speed);
            _motorRight->setSpeed(speed);

        if (distance != 0)
        {
            _motorLeft->stop();
            _motorRight->stop();

            _motorLeft->setPositionSp(distance);
            _motorRight->setPositionSp(distance);

            _motorLeft->setCommand(MotorCommand::RUN_TO_REL_POS);
            _motorRight->setCommand(MotorCommand::RUN_TO_REL_POS);


            if (stopCallback != nullptr)
            {
                stopCallback();
            }
        }

    }
}