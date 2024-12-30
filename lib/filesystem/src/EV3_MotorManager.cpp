#include "EV3_MotorManager.hpp"

namespace finder::physical
{
    MotorManager::MotorManager(std::string portBasePath) : DeviceManager(portBasePath)
    {
        spdlog::trace("Initializing MotorManager");

        _motorLeft->setStopAction(MotorStopAction::HOLD);
        _motorRight->setStopAction(MotorStopAction::HOLD);
        _motorShift->setStopAction(MotorStopAction::HOLD);
        _motorTool->setStopAction(MotorStopAction::HOLD);
    }

    MotorManager::~MotorManager()
    {
        spdlog::trace("Destroying MotorManager");

        stop();
    }

    void MotorManager::setSpeed(int speed)
    {
        spdlog::trace("Setting speed to " + std::to_string(speed));

        _motorLeft->setSpeed(speed);
        _motorRight->setSpeed(speed);
    }

    void MotorManager::setDutyCycle(int dutyCycle)
    {
        setDutyCycle(dutyCycle, dutyCycle);
    }

    void MotorManager::setDutyCycle(int dutyCycleLeft, int dutyCycleRight)
    {
        _motorLeft->setDutyCycle(dutyCycleLeft);
        _motorRight->setDutyCycle(dutyCycleRight);
    }

    void MotorManager::moveForward(int distance, int speed)
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

    void MotorManager::moveForwardDirect(int speed)
    {
        moveForwardDirect(speed, speed);
    }

    void MotorManager::moveForwardDirect(int speedLeft, int speedRight)
    {
        spdlog::trace("Moving forward direct at speed " + std::to_string(speedLeft) + " " + std::to_string(speedRight));

        _motorLeft->setDutyCycle(speedLeft);
        _motorRight->setDutyCycle(speedRight);

        _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
        _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);

        spdlog::trace("Motors started");
    }

    void MotorManager::moveBackward(int distance, int speed)
    {
        moveForward(-distance, speed);
    }

    void MotorManager::turn(TurnDirection direction, int angle, int speed)
    {
        spdlog::trace("MotorManager::turn()");
        spdlog::trace("Turning " + (direction == TurnDirection::LEFT ? std::string("left") : std::string("right")) + " " + std::to_string(angle) + " at speed " + std::to_string(speed));

        switch (direction)
        {
        case TurnDirection::LEFT:
            _motorLeft->setPositionSp(-angle);
            _motorRight->setPositionSp(angle);
            break;

        case TurnDirection::RIGHT:
            _motorLeft->setPositionSp(angle);
            _motorRight->setPositionSp(-angle);
            break;

        default:
            spdlog::error("Invalid turn direction");
            return;
        }

        _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
        _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
    

        for (boost::leaf::result<int> result = _gyroSensor->getValue(0); result && result.value() < angle; result = _gyroSensor->getValue(0))
        {
            spdlog::trace("Current angle: " + std::to_string(result.value()));
        }
    
        _motorLeft->stop();
        _motorRight->stop();

        spdlog::trace("Motors stopped");
    }

    void MotorManager::stop()
    {
        spdlog::trace("Stopping motors");

        _motorLeft->stop();
        _motorRight->stop();

        spdlog::trace("Motors stopped");
    }

    boost::leaf::result<int> MotorManager::getPosition(DeviceID port)
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
    
    boost::leaf::result<int> MotorManager::getSpeed(DeviceID port)
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
    
    
    boost::leaf::result<std::vector<MotorState>> MotorManager::getState(DeviceID port)
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
