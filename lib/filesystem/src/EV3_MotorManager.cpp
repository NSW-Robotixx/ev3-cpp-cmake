#include "EV3_MotorManager.hpp"

namespace finder::physical
{
    TurnDirection MotorManager::_prevTurnDirection = TurnDirection::FORWARD;
    std::vector<std::function<void(TurnDirection)>> MotorManager::_directionChangeListeners;

    log4cplus::Logger MotorManager::_logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("MotorManager"));
    
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
        absl::Status status = _motorLeft->stop();
        status.Update(_motorRight->stop());

        if (!status.ok())
        {
            status = _motorLeft->setCommand(MotorCommand::STOP);
            status.Update(_motorRight->setCommand(MotorCommand::STOP));

            if (!status.ok())
            {
                LOG4CPLUS_FATAL_FMT(_logger, LOG4CPLUS_TEXT("Failed to stop motors: %s"), status.message());
            }
        }
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
    absl::Status MotorManager::moveForward(LaunchType launch, int speed = 200, int distance = 0, std::function<void()> stopCallback = nullptr)
    {
        return move(launch, speed, distance, stopCallback);
    }

    absl::Status MotorManager::moveBackward(LaunchType launch, int speed = 200, int distance = 0, std::function<void()> stopCallback = nullptr)
    {
        return move(launch, -speed, distance, stopCallback);
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

    absl::Status MotorManager::move(LaunchType launch, int speed, int distance, std::function<void()> stopCallback)
    {
        return moveNow(speed, distance, stopCallback);
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
            ABSL_RETURN_IF_ERROR(_motorLeft->setCommand(MotorCommand::RUN_DIRECT));
        }
        else if (direction == TurnDirection::RIGHT)
        {
            _motorRight->setDutyCycle(speed);
            ABSL_RETURN_IF_ERROR(_motorRight->setCommand(MotorCommand::RUN_DIRECT));
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
        
        absl::Status status = _motorLeft->stop();
        status.Update(_motorRight->stop());

        return status;
    }

    absl::Status MotorManager::moveNow(int speed, int distance, std::function<void()> stopCallback)
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
            absl::Status statusLeft;
            absl::Status statusRight;

            int absDestinationLeft = _motorLeft->getPosition() + distance;
            int absDestinationRight = _motorRight->getPosition() + distance;

            do {
                statusLeft.Update(_motorLeft->stop());
                statusRight.Update(_motorRight->stop());

                statusLeft.Update(_motorLeft->setPositionSp(absDestinationLeft));
                statusRight.Update(_motorRight->setPositionSp(absDestinationRight));

                statusLeft.Update(_motorLeft->setCommand(MotorCommand::RUN_TO_ABS_POS));
                statusRight.Update(_motorRight->setCommand(MotorCommand::RUN_TO_ABS_POS));

                if (!statusLeft.ok()) {
                    LOG4CPLUS_FATAL_FMT(_logger, LOG4CPLUS_TEXT("Failed to move left motor: %s"), statusLeft.message());
                    absl::Status resetStatus = _motorLeft->reset();
                    if (!resetStatus.ok()) {
                        LOG4CPLUS_FATAL_FMT(_logger, LOG4CPLUS_TEXT("Failed to reset left motor: %s"), resetStatus.message());
                        return resetStatus;
                    }
                }

                if (!statusRight.ok()) {
                    LOG4CPLUS_FATAL_FMT(_logger, LOG4CPLUS_TEXT("Failed to move right motor: %s"), statusRight.message());
                    absl::Status resetStatus = _motorRight->reset();
                    if (!resetStatus.ok()) {
                        LOG4CPLUS_FATAL_FMT(_logger, LOG4CPLUS_TEXT("Failed to reset right motor: %s"), resetStatus.message());
                        return resetStatus;
                    }
                }
            } while (!statusLeft.ok() || !statusRight.ok());


            if (stopCallback != nullptr)
            {
                stopCallback();
            }
        }
        return absl::OkStatus();
    }
}