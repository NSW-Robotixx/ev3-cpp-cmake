#include "RobotMovement.hpp"

namespace finder::robot
{
    console::Logger RobotMovement::_logger{};

    unsigned long int RobotMovement::_movementID = 0;

    std::queue<std::function<void(int, int, double)>> RobotMovement::_movementQueue;
    std::atomic<bool> RobotMovement::_isProcessingMovementQueue;

    std::future<void> RobotMovement::_movementQueueFuture;

    RobotMovement::RobotMovement(std::string portBasePath): DeviceManager(portBasePath)
    {

        _logger.debug("Initializing RobotMovement");
        _logger.debug(_motorLeft->getBasePath());
        _logger.debug(_motorRight->getBasePath());
        _logger.debug(_motorShift->getBasePath());
        _logger.debug(_motorTool->getBasePath());
        _logger.debug("RobotMovement initialized");

        _isProcessingMovementQueue = false;
        // _movementQueueFuture = std::async(std::launch::async, processMovementQueue);
        processMovementQueue();
    }

    RobotMovement::~RobotMovement()
    {
        stop();
    }

    void RobotMovement::move(MovementType type, int distance = 0, int speed = 300, float arcRatio = 1)
    {
        switch (type)
        {
        case MovementType::FORWARD:
            _movementQueue.push(&moveForward);
            break;

        case MovementType::BACKWARD:
            _movementQueue.push(&moveBackward);
            break;

        case MovementType::TURN_LEFT:
            _movementQueue.push(&turnLeft);
            break;

        case MovementType::TURN_RIGHT:
            _movementQueue.push(&turnRight);
            break;

        case MovementType::TURN_ARC_LEFT:
            _movementQueue.push(&turnArcLeft);
            break;

        case MovementType::TURN_ARC_RIGHT:
            _movementQueue.push(&turnArcRight);
            break;
        
        default:
            throw std::invalid_argument("Invalid movement type");
        }

        // if (!_isProcessingMovementQueue) {
            // _movementQueueFuture = std::async(std::launch::async, RobotMovement::processMovementQueue);
        // } 
        processMovementQueue();
    }


    void RobotMovement::stop()
    {
       
    }

    void RobotMovement::setSpeed(int speed)
    {
        _speed = speed;
    }

    void RobotMovement::setDutyCycle(int dutyCycle)
    {
        _dutyCycle = dutyCycle;
    }

    void RobotMovement::awaitMotorReady()
    {
        // std::vector<::finder::physical::MotorState> _leftState = _motorLeft->getState();
        // std::vector<::finder::physical::MotorState> _rightState = _motorRight->getState();

        // while (
        //     std::find(_rightState.begin(), _rightState.end(), ::finder::physical::MotorState::HOLDING) == _rightState.end() ||
        //     std::find(_leftState.begin(), _leftState.end(), ::finder::physical::MotorState::HOLDING) == _leftState.end()
        // ) {
        //     _leftState = _motorLeft->getState();
        //     _rightState = _motorRight->getState();
        // }
    }

    void RobotMovement::processMovementQueue()
    {
        _isProcessingMovementQueue = true;

        while (_movementQueue.size() > 0) {
            std::function<void(int, int, double)> action = _movementQueue.front();
            _movementQueue.pop();

            awaitMotorReady();

            action(_speed, _dutyCycle, _arcRatio);
        }

        _isProcessingMovementQueue = false;
    }






    void RobotMovement::moveForward(int distance, int speed, float arcRatio = 1)
    {
        if (_motorLeft->isEnabled() && _motorRight->isEnabled()) {
            _motorLeft->setPolarity(physical::MotorPolarity::NORMAL);
            _motorRight->setPolarity(physical::MotorPolarity::NORMAL);

            _motorLeft->setSpeed(speed);
            _motorRight->setSpeed(speed);

            if (distance <= 0) {
                _motorLeft->setCommand(physical::MotorCommand::RUN_FOREVER);
                _motorRight->setCommand(physical::MotorCommand::RUN_FOREVER);
            } else {
                _motorLeft->setPositionSp(distance);
                _motorRight->setPositionSp(distance);

                _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
                _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
            }
        } else {
            _logger.error("Motors are not enabled");
        }
    }

    void RobotMovement::moveBackward(int distance, int speed, float arcRatio = 1)
    {
        if (_motorLeft->isEnabled() && _motorRight->isEnabled()) {
            _motorLeft->setPolarity(physical::MotorPolarity::INVERSED);
            _motorRight->setPolarity(physical::MotorPolarity::INVERSED);

            _motorLeft->setSpeed(speed);
            _motorRight->setSpeed(speed);

            if (distance <= 0) {
                _motorLeft->setCommand(physical::MotorCommand::RUN_FOREVER);
                _motorRight->setCommand(physical::MotorCommand::RUN_FOREVER);
            } else {
                _motorLeft->setPositionSp(distance);
                _motorRight->setPositionSp(distance);

                _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
                _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
            }
        } else {
            _logger.error("Motors are not enabled");
        }
    }

    void RobotMovement::turnLeft(int distance, int speed, float arcRatio = 1)
    {
        if (_motorLeft->isEnabled() && _motorRight->isEnabled()) {
            _motorLeft->setPolarity(physical::MotorPolarity::NORMAL);
            _motorRight->setPolarity(physical::MotorPolarity::NORMAL);

            _motorLeft->setDutyCycle(speed);
            _motorRight->setDutyCycle(speed * LEFT_RIGHT_SWITCH);

            if (distance <= 0) {
                _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
                _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
            } else {
                _motorLeft->setPositionSp(distance);
                _motorRight->setPositionSp(distance);

                _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
                _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
            }
        } else {
            _logger.error("Motors are not enabled");
        }
    }

    void RobotMovement::turnRight(int distance, int speed, float arcRatio = 1)
    {
        if (_motorLeft->isEnabled() && _motorRight->isEnabled()) {
            _motorLeft->setPolarity(physical::MotorPolarity::INVERSED);
            _motorRight->setPolarity(physical::MotorPolarity::INVERSED);

            _motorLeft->setDutyCycle(speed);
            _motorRight->setDutyCycle(speed * LEFT_RIGHT_SWITCH);

            if (distance <= 0) {
                _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
                _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
            } else {
                _motorLeft->setPositionSp(distance);
                _motorRight->setPositionSp(distance);

                _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
                _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
            }
        } else {
            _logger.error("Motors are not enabled");
        }
    }

    void RobotMovement::turnArcLeft(int distance, int speed, float arcRatio)
    {
        if (_motorLeft->isEnabled() && _motorRight->isEnabled()) {
            _motorLeft->setPolarity(physical::MotorPolarity::INVERSED);
            _motorRight->setPolarity(physical::MotorPolarity::INVERSED);

            _motorLeft->setDutyCycle(speed * arcRatio);
            _motorRight->setDutyCycle(speed * LEFT_RIGHT_SWITCH);

            if (distance <= 0) {
                _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
                _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
            } else {
                _motorLeft->setPositionSp(distance);
                _motorRight->setPositionSp(distance);

                _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
                _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
            }
        } else {
            _logger.error("Motors are not enabled");
        }
    }

    void RobotMovement::turnArcRight(int distance, int speed, float arcRatio)
    {
        if (_motorLeft->isEnabled() && _motorRight->isEnabled()) {
            _motorLeft->setPolarity(physical::MotorPolarity::INVERSED);
            _motorRight->setPolarity(physical::MotorPolarity::INVERSED);

            _motorLeft->setDutyCycle(speed);
            _motorRight->setDutyCycle(speed * LEFT_RIGHT_SWITCH * arcRatio);

            if (distance <= 0) {
                _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
                _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
            } else {
                _motorLeft->setPositionSp(distance);
                _motorRight->setPositionSp(distance);

                _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
                _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
            }
        } else {
            _logger.error("Motors are not enabled");
        }
    }

} // namespace finder::robot