#include "EV3_MovementEngine.hpp"

namespace finder::engines::movement
{
    MovementEngine::MovementEngine(std::string portBasePath) : DeviceManager(portBasePath)
    {
        spdlog::trace("Initializing MovementEngine");

        _motorLeft->setStopAction(MotorStopAction::HOLD);
        _motorRight->setStopAction(MotorStopAction::HOLD);
        _motorShift->setStopAction(MotorStopAction::HOLD);
        _motorTool->setStopAction(MotorStopAction::HOLD);

        _gyroSensor->calibrateGyro();
    }

    MovementEngine::~MovementEngine()
    {
        spdlog::trace("Destroying MovementEngine");

        stop();
    }

    void MovementEngine::moveToPoint(math::Vector2 destination)
    {
        double lineAngle = math::Line(position::Position::getPosition(), destination).getAngle();
        double lineAngleReverse = lineAngle + 180;
        lineAngleReverse = lineAngleReverse > 360 ? lineAngleReverse - 360 : lineAngleReverse;

        if (lineAngle < lineAngleReverse) {
            if (position::Position::getAngle() > lineAngle) {
                turn(physical::TurnDirection::RIGHT, position::Position::getAngle() - lineAngle, EV3_TURN_SPEED);
            } else {
                turn(physical::TurnDirection::LEFT, lineAngle - position::Position::getAngle(), EV3_TURN_SPEED);
            }

            moveForward(destination.distanceTo(position::Position::getPosition()), 300);
        } else {
            if (position::Position::getAngle() < lineAngle) {
                turn(physical::TurnDirection::LEFT, position::Position::getAngle() - lineAngle, EV3_TURN_SPEED);
            } else {
                turn(physical::TurnDirection::RIGHT, position::Position::getAngle() - lineAngle, EV3_TURN_SPEED);
            }

            moveBackward(destination.distanceTo(position::Position::getPosition()), 300);
        }
    }


    void MovementEngine::setSpeed(int speed)
    {
        spdlog::trace("Setting speed to " + std::to_string(speed));

        _motorLeft->setSpeed(speed);
        _motorRight->setSpeed(speed);
    }

    void MovementEngine::setDutyCycle(int dutyCycle)
    {
        setDutyCycle(dutyCycle, dutyCycle);
    }

    void MovementEngine::setDutyCycle(int dutyCycleLeft, int dutyCycleRight)
    {
        _motorLeft->setDutyCycle(dutyCycleLeft);
        _motorRight->setDutyCycle(dutyCycleRight);
    }

    void MovementEngine::moveForward(int distance, int speed)
    {
        spdlog::trace("Moving forward " + std::to_string(distance) + " at speed " + std::to_string(speed));

        setSpeed(speed);

        _motorLeft->setPositionSp(distance);
        _motorRight->setPositionSp(distance);

        _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
        _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);

        _motorLeft->waitUntilStopped();
        _motorRight->waitUntilStopped();

        spdlog::trace("Motors stopped");
    }

    void MovementEngine::moveForwardDirect(int speed)
    {
        moveForwardDirect(speed, speed);
    }

    void MovementEngine::moveForwardDirect(int speedLeft, int speedRight)
    {
        spdlog::trace("Moving forward direct at speed " + std::to_string(speedLeft) + " " + std::to_string(speedRight));

        _motorLeft->setDutyCycle(speedLeft);
        _motorRight->setDutyCycle(speedRight);

        _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
        _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);

        spdlog::trace("Motors started");
    }

    void MovementEngine::moveBackward(int distance, int speed)
    {
        moveForward(-distance, speed);
    }

    void MovementEngine::turn(TurnDirection direction, int angle, int speed)
    {
        spdlog::trace("MovementEngine::turn()");
        spdlog::trace("Turning " + (direction == TurnDirection::LEFT ? std::string("left") : std::string("right")) + " " + std::to_string(angle) + " at speed " + std::to_string(speed));

        if (speed > 100) {
            spdlog::warn("Speed is higher than 100, setting to 100");
            speed = 100;
        }

        switch (direction)
        {
        case TurnDirection::LEFT:
            _motorLeft->setDutyCycle(-speed);
            _motorRight->setDutyCycle(speed);
            break;

        case TurnDirection::RIGHT:
            _motorLeft->setDutyCycle(speed);
            _motorRight->setDutyCycle(-speed);
            break;

        default:
            spdlog::error("Invalid turn direction");
            return;
        }

        _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
        _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
    

        switch (direction)  
        {
        case TurnDirection::LEFT:
            for (boost::leaf::result<int> result = _gyroSensor->getValue(0); result && result.value() < angle; result = _gyroSensor->getValue(0)) 
            {
                spdlog::info("Target angle: " + std::to_string(angle));
                spdlog::info("Current Sensor Angle: " + std::to_string(result.value()));
                spdlog::info("Current Motor Angle: " + std::to_string(position::Position::getAngle()));
            }
            break;
        
        case TurnDirection::RIGHT:
            for (boost::leaf::result<int> result = _gyroSensor->getValue(0); result && result.value() > angle; result = _gyroSensor->getValue(0)) 
            {
                spdlog::info("Target angle: " + std::to_string(angle));
                spdlog::info("Current Sensor Angle: " + std::to_string(result.value()));
                spdlog::info("Current Motor Angle: " + std::to_string(position::Position::getAngle()));
            }
            break;

        default:
            spdlog::error("Invalid turn direction");
            break;
        }

        _motorLeft->stop();
        _motorRight->stop();

        spdlog::trace("Motors stopped");
    }

    void MovementEngine::stop()
    {
        spdlog::trace("Stopping motors");

        _motorLeft->stop();
        _motorRight->stop();

        spdlog::trace("Motors stopped");
    }

    boost::leaf::result<int> MovementEngine::getPosition(DeviceID port)
    {
        switch (port)
        {
        case DeviceID::MOTOR_LEFT:
            return _motorLeft->getPosition();
            break;

        case DeviceID::MOTOR_RIGHT:
            return _motorRight->getPosition();
            break;

        case DeviceID::MOTOR_SHIFT:
            return _motorShift->getPosition();
            break;

        case DeviceID::MOTOR_TOOL:
            return _motorTool->getPosition();
            break;

        default:
            spdlog::error("Invalid motor port");
            break;
        }

        return boost::leaf::new_error(std::invalid_argument("Invalid motor port"));
    }
    
    boost::leaf::result<int> MovementEngine::getSpeed(DeviceID port)
    {
        switch (port)
        {
        case DeviceID::MOTOR_LEFT:
            return _motorLeft->getSpeed();
            break;

        case DeviceID::MOTOR_RIGHT:
            return _motorRight->getSpeed();
            break;

        case DeviceID::MOTOR_SHIFT:
            return _motorShift->getSpeed();
            break;

        case DeviceID::MOTOR_TOOL:
            return _motorTool->getSpeed();
            break;

        default:
            spdlog::error("Invalid motor port");
            break;
        }

        return boost::leaf::new_error(std::invalid_argument("Invalid motor port"));
    }
    
    
    boost::leaf::result<std::vector<MotorState>> MovementEngine::getState(DeviceID port)
    {
        switch (port)
        {
        case DeviceID::MOTOR_LEFT:
            return _motorLeft->getState();
            break;

        case DeviceID::MOTOR_RIGHT:
            return _motorRight->getState();
            break;

        case DeviceID::MOTOR_SHIFT:
            return _motorShift->getState();
            break;

        case DeviceID::MOTOR_TOOL:
            return _motorTool->getState();
            break;

        default:
            spdlog::error("Invalid motor port");
            break;
        }

        return boost::leaf::new_error(std::invalid_argument("Invalid motor port"));
    }
} // namespace finder::physica
