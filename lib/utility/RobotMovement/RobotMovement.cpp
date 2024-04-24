#include "RobotMovement.hpp"

namespace finder::robot
{
    std::shared_ptr<physical::MotorPort> RobotMovement::_motorLeft;
    std::shared_ptr<physical::MotorPort> RobotMovement::_motorRight;
    std::shared_ptr<physical::MotorPort> RobotMovement::_motorShift;
    std::shared_ptr<physical::MotorPort> RobotMovement::_motorTool;

    int RobotMovement::_speed = 50;
    int RobotMovement::_dutyCycle = 50;

    finder::console::Logger RobotMovement::_logger;

    unsigned long int RobotMovement::_movementID;
    std::mutex RobotMovement::_movementIDMutex;

    std::future<void> _movementFuture;


    RobotMovement::RobotMovement()
    {

        _logger.debug("Initializing RobotMovement");
        _logger.debug(_motorLeft->getBasePath());
        _logger.debug(_motorRight->getBasePath());
        _logger.debug(_motorShift->getBasePath());
        _logger.debug(_motorTool->getBasePath());
        _logger.debug("RobotMovement initialized");
    }

    RobotMovement::~RobotMovement()
    {
    }

    void RobotMovement::moveForward()
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            if(_motorLeft->isEnabled() && _motorRight->isEnabled())
            {
                _motorLeft->setSpeed(_speed);
                _motorRight->setSpeed(_speed);

                _motorLeft->setCommand(physical::MotorCommand::RUN_FOREVER);
                _motorRight->setCommand(physical::MotorCommand::RUN_FOREVER);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::moveForward(int distance)
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            if(_motorLeft->isEnabled() && _motorRight->isEnabled())
            {
                _motorLeft->setSpeed(_speed);
                _motorRight->setSpeed(_speed);

                _motorLeft->setPositionSp(distance);
                _motorRight->setPositionSp(distance);

                _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
                _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::moveForward(int distance, int speed)
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            if(_motorLeft->isEnabled() && _motorRight->isEnabled())
            {
                _motorLeft->setSpeed(speed);
                _motorRight->setSpeed(speed);

                _motorLeft->setPositionSp(distance);
                _motorRight->setPositionSp(distance);

                _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
                _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::moveBackward()
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            if(_motorLeft->isEnabled() && _motorRight->isEnabled())
            {
                _motorLeft->setPolarity(physical::MotorPolarity::INVERSED);
                _motorRight->setPolarity(physical::MotorPolarity::INVERSED);

                _motorLeft->setSpeed(_speed);
                _motorRight->setSpeed(_speed);

                _motorLeft->setCommand(physical::MotorCommand::RUN_FOREVER);
                _motorRight->setCommand(physical::MotorCommand::RUN_FOREVER);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::moveBackward(int distance)
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            if(_motorLeft->isEnabled() && _motorRight->isEnabled())
            {
                _motorLeft->setPolarity(physical::MotorPolarity::INVERSED);
                _motorRight->setPolarity(physical::MotorPolarity::INVERSED);

                _motorLeft->setSpeed(_speed);
                _motorRight->setSpeed(_speed);

                _motorLeft->setPositionSp(distance);
                _motorRight->setPositionSp(distance);

                _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
                _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::moveBackward(int distance, int speed)
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            if(_motorLeft->isEnabled() && _motorRight->isEnabled())
            {
                _motorLeft->setPolarity(physical::MotorPolarity::INVERSED);
                _motorRight->setPolarity(physical::MotorPolarity::INVERSED);

                _motorLeft->setSpeed(speed);
                _motorRight->setSpeed(speed);

                _motorLeft->setPositionSp(distance);
                _motorRight->setPositionSp(distance);

                _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
                _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::turnLeft()
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            if(_motorLeft->isEnabled() && _motorRight->isEnabled())
            {
                _motorLeft->setDutyCycle(_dutyCycle);
                _motorRight->setDutyCycle(LEFT_RIGHT_SWITCH * _dutyCycle);

                _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
                _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::turnLeft(int angle)
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            _logger.warn("Not implemented yet");
            if(_motorLeft->isEnabled() && _motorRight->isEnabled())
            {
                _motorLeft->setDutyCycle(_dutyCycle);
                _motorRight->setDutyCycle(LEFT_RIGHT_SWITCH * _dutyCycle);

                _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
                _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::turnLeft(int angle, int speed)
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            _logger.warn("Not implemented yet");
            if(_motorLeft->isEnabled() && _motorRight->isEnabled())
            {
                _motorLeft->setDutyCycle(speed);
                _motorRight->setDutyCycle(LEFT_RIGHT_SWITCH * speed);

                _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
                _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::turnRight()
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            if(_motorLeft->isEnabled() && _motorRight->isEnabled())
            {
                _motorLeft->setDutyCycle(LEFT_RIGHT_SWITCH * _dutyCycle);
                _motorRight->setDutyCycle(_dutyCycle);

                _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
                _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::turnRight(int angle)
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            _logger.warn("Not implemented yet");
            if(_motorLeft->isEnabled() && _motorRight->isEnabled())
            {
                _motorLeft->setDutyCycle(LEFT_RIGHT_SWITCH * _dutyCycle);
                _motorRight->setDutyCycle(_dutyCycle);

                _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
                _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::turnRight(int angle, int speed)
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            _logger.warn("Not implemented yet");
            if(_motorLeft->isEnabled() && _motorRight->isEnabled())
            {
                _motorLeft->setDutyCycle(LEFT_RIGHT_SWITCH * speed);
                _motorRight->setDutyCycle(speed);

                _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
                _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::turnArcLeft(int angle)
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            _logger.warn("Not implemented yet");
            if(_motorRight->isEnabled())
            {
                _motorRight->setDutyCycle(_dutyCycle);

                _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::turnArcLeft(int angle, int speed)
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            _logger.warn("Not implemented yet");
            if(_motorRight->isEnabled())
            {
                _motorRight->setDutyCycle(speed);

                _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::turnArcRight(int angle)
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            _logger.warn("Not implemented yet");
            if(_motorLeft->isEnabled())
            {
                _motorLeft->setDutyCycle(_dutyCycle);

                _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::turnArcRight(int angle, int speed)
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            _logger.warn("Not implemented yet");
            if(_motorLeft->isEnabled())
            {
                _motorLeft->setDutyCycle(speed);

                _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::stop()
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            if(_motorLeft->isEnabled() && _motorRight->isEnabled())
            {
                _motorLeft->setCommand(physical::MotorCommand::STOP);
                _motorRight->setCommand(physical::MotorCommand::STOP);
            } else {
                _logger.error("Motor is not enabled");
            }
        });
    }

    void RobotMovement::setSpeed(int speed)
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            _speed = speed;
        });
    }

    void RobotMovement::setDutyCycle(int dutyCycle)
    {
        _movementFuture = std::async(std::launch::async, [&](){
            awaitMotorReady();
            _dutyCycle = dutyCycle;
        });
    }

    void RobotMovement::awaitMotorReady()
    {
        std::vector<::finder::physical::MotorState> _leftState = _motorLeft->getState();
        std::vector<::finder::physical::MotorState> _rightState = _motorRight->getState();

        while (
            std::find(_rightState.begin(), _rightState.end(), ::finder::physical::MotorState::HOLDING) == _rightState.end() ||
            std::find(_leftState.begin(), _leftState.end(), ::finder::physical::MotorState::HOLDING) == _leftState.end()
        ) {
            _leftState = _motorLeft->getState();
            _rightState = _motorRight->getState();
        }
    }

} // namespace finder::robot