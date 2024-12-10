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
        boost::leaf::result<void> status = _motorLeft->stop();
        status = (_motorRight->stop());

        if (!status)
        {
            status = _motorLeft->setCommand(MotorCommand::STOP);
            status = (_motorRight->setCommand(MotorCommand::STOP));

            if (!status)
            {
                spdlog::error("Failed to stop motors: %s", boost::diagnostic_information(status.error()));
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
    boost::leaf::result<void> MotorManager::moveForward(LaunchType launch, int speed = 200, int distance = 0, std::function<void()> stopCallback = nullptr)
    {
        return move(launch, speed, distance, stopCallback);
    }

    boost::leaf::result<void> MotorManager::moveBackward(LaunchType launch, int speed = 200, int distance = 0, std::function<void()> stopCallback = nullptr)
    {
        return move(launch, -speed, distance, stopCallback);
    }

    boost::leaf::result<void> MotorManager::turnLeft(LaunchType launch, int speed = 200, int distance = 0, std::function<void()> stopCallback = nullptr)
    {
        boost::leaf::result<void> status = turn(launch, speed, distance, stopCallback, TurnDirection::LEFT);
        if (!status)
        {
            return status;
        }
        return boost::leaf::result<void>();
    }


    boost::leaf::result<void> MotorManager::turnRight(LaunchType launch, int speed = 200, int distance = 0, std::function<void()> stopCallback = nullptr)
    {
        boost::leaf::result<void> status = turn(launch, speed, distance, stopCallback, TurnDirection::RIGHT);
        if (!status)
        {
            return status;
        }
        return boost::leaf::result<void>();
    }

    void MotorManager::onDirectionChange(std::function<void(TurnDirection)> callback)
    {
        _directionChangeListeners.push_back(callback);
    }

    int MotorManager::getMaxSpeed()
    {
        return _motorLeft->getMaxSpeed();
    }

    boost::leaf::result<void> MotorManager::move(LaunchType launch, int speed, int distance, std::function<void()> stopCallback)
    {
        return moveNow(speed, distance, stopCallback);
    }

    boost::leaf::result<void> MotorManager::turn(LaunchType launch, int speed, int distance, std::function<void()> stopCallback, TurnDirection direction)
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
            boost::leaf::result<int> gyroValue = SensorManager::readGyro();
            if (!gyroValue)
            {
                return gyroValue.error();
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
        
        boost::leaf::result<void> _motorLeftResult = _motorLeft->stop();

        if (!_motorLeftResult) 
        {
            return _motorLeftResult.error();
        }

        boost::leaf::result<void> _motorRightResult = _motorRight->stop();

        if (!_motorRightResult) 
        {
            return _motorRightResult.error();
        }

        return boost::leaf::result<void>();
    }

    boost::leaf::result<void> MotorManager::moveNow(int speed, int distance, std::function<void()> stopCallback)
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
            boost::leaf::result<void> statusLeft;
            boost::leaf::result<void> statusRight;

            int absDestinationLeft = _motorLeft->getPosition() + distance;
            int absDestinationRight = _motorRight->getPosition() + distance;

            do {
                statusLeft = _motorLeft->stop();
                if (statusLeft) { return statusLeft.error(); }

                statusRight = (_motorRight->stop());
                if (statusRight) { return statusRight.error(); }

                statusLeft = (_motorLeft->setPositionSp(absDestinationLeft));
                if (statusLeft) { return statusRight.error(); }

                statusRight = (_motorRight->setPositionSp(absDestinationRight));
                if (statusRight) { return statusRight.error(); }

                statusLeft = (_motorLeft->setCommand(MotorCommand::RUN_TO_ABS_POS));
                if (statusLeft) { return statusRight.error(); }

                statusRight = (_motorRight->setCommand(MotorCommand::RUN_TO_ABS_POS));
                if (statusRight) { return statusRight.error(); }

                if (!statusLeft) {
                    spdlog::error("Failed to move left motor");
                    boost::leaf::result<void> resetStatus = _motorLeft->reset();
                    if (!resetStatus) {
                        spdlog::error("Failed to reset left motor");
                        return resetStatus;
                    }
                }

                if (!statusRight) {
                    spdlog::error("Failed to move right motor");
                    boost::leaf::result<void> resetStatus = _motorRight->reset();
                    if (!resetStatus) {
                        spdlog::error("Failed to reset right motor");
                        return resetStatus;
                    }
                }
            } while (!statusLeft || !statusRight);


            if (stopCallback != nullptr)
            {
                stopCallback();
            }
        }
        return boost::leaf::result<void>();
    }
}