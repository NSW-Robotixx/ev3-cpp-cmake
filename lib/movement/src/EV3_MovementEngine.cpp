#include "EV3_MovementEngine.hpp"

namespace finder::engines::movement
{
    int MovementEngine::_target_angle = 0;

    MovementEngine::MovementEngine(std::string portBasePath) : DeviceManager(portBasePath)
    {
        spdlog::trace("Initializing MovementEngine");

        _motorLeft.reset();
        _motorRight.reset();

        _motorLeft->setStopAction(MotorStopAction::HOLD);
        _motorRight->setStopAction(MotorStopAction::HOLD);
        _motorShift->setStopAction(MotorStopAction::HOLD);
        _motorTool->setStopAction(MotorStopAction::HOLD);

        _motorLeft->setPolarity(MotorPolarity::NORMAL);
        _motorRight->setPolarity(MotorPolarity::NORMAL);

        _motorLeft->setRampDownSpeed(3000);
        _motorRight->setRampDownSpeed(3000);

        _motorLeft->setRampUpSpeed(3000);
        _motorRight->setRampUpSpeed(3000);

        _gyroSensor->calibrateGyro();
    }

    MovementEngine::~MovementEngine()
    {
        spdlog::trace("Destroying MovementEngine");

        stop();
    }

    void MovementEngine::moveToPoint(math::Vector3 destination)
    {
        if (destination.x <= 1 || destination.y <= 1)
        {
            spdlog::info("Pause Reached, not moving");
            return;
        }

        double lineAngle = math::Line(position::Position::getPosition(), {destination.x, destination.y}).getAngle();
        double lineAngleReverse = std::fmod(lineAngle + 180, 360);

        spdlog::debug("Turning to angle: " + std::to_string(lineAngle));    

        if (lineAngle < lineAngleReverse) {
            spdlog::debug("Turning to normal angle: " + std::to_string(lineAngle));
            if (position::Position::getAngle() > lineAngle) {
                turn(physical::TurnDirection::RIGHT, round(lineAngle), EV3_TURN_SPEED);
                _target_angle = round(lineAngle);
            } else {
                turn(physical::TurnDirection::LEFT, round(lineAngle), EV3_TURN_SPEED);
                _target_angle = round(lineAngle);
            }

            moveForward(math::Vector2{destination.x, destination.y}.distanceTo(position::Position::getPosition()), EV3_DRIVE_SPEED);
        } else {
            spdlog::debug("Turning to reverse angle: " + std::to_string(lineAngleReverse));
            if (position::Position::getAngle() < lineAngleReverse) {
                turn(physical::TurnDirection::LEFT, round(lineAngleReverse), EV3_TURN_SPEED);
                _target_angle = round(lineAngleReverse);
            } else {
                turn(physical::TurnDirection::RIGHT, round(lineAngleReverse), EV3_TURN_SPEED);
                _target_angle = round(lineAngleReverse);
            }

            moveBackward(math::Vector2{destination.x, destination.y}.distanceTo(position::Position::getPosition()), EV3_DRIVE_SPEED);
        }

        if (destination.z > -1)
        {
            spdlog::debug("Turning to second angle: " + std::to_string(destination.z));
            if (position::Position::getAngle() > destination.z) {
                turn(physical::TurnDirection::RIGHT, round(destination.z), EV3_TURN_SPEED);
            } else {
                turn(physical::TurnDirection::LEFT, round(destination.z), EV3_TURN_SPEED);
            }
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
        
        finder::position::MotorPosition::notifyMovementStart(distance);
        
        #if EV3_DRIVE_MODE_USE_GYRO == 1
        spdlog::trace("Using motor speed control");

        
        _motorLeft->setDutyCycle(EV3_TURN_SPEED);
        _motorRight->setDutyCycle(EV3_TURN_SPEED);
        
        _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
        _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);

        int _motor_left_start_position = _motorLeft->getPosition();
        int _motor_right_start_position = _motorRight->getPosition();
        
        // if (distance < 0)
        // {
        //     spdlog::info("Distance is negative, reversing direction");
        //     _motor_left_start_position *= -1;
        //     _motor_right_start_position *= -1;
        // }
        
        spdlog::trace("Motor Left Start Position: " + std::to_string(_motor_left_start_position));
        spdlog::trace("Motor Right Start Position: " + std::to_string(_motor_right_start_position));
        spdlog::trace("Motor Left Target Position: " + std::to_string(distance * EV3_MOTOR_DISTANCE_PER_DEGREE + _motor_left_start_position));
        spdlog::trace("Motor Right Target Position: " + std::to_string(distance * EV3_MOTOR_DISTANCE_PER_DEGREE + _motor_right_start_position));
        
        while (true)
        {
            bool singleMotorStopped = false;

            if (distance < 0)
            {
                if (_motorLeft->getPosition() <= distance * EV3_MOTOR_DISTANCE_PER_DEGREE + _motor_left_start_position)
                {
                    spdlog::debug("Left motor reached target position");
                    _motorLeft->stop();
                    
                    if (singleMotorStopped)
                    {
                        break;
                    }

                    singleMotorStopped = true;
                }   

                if (_motorRight->getPosition() <= distance * EV3_MOTOR_DISTANCE_PER_DEGREE + _motor_right_start_position)
                {
                    spdlog::debug("Right motor reached target position");
                    _motorRight->stop();

                    if (singleMotorStopped)
                    {
                        break;
                    }

                    singleMotorStopped = true;
                } 
            } else {

                if (_motorLeft->getPosition() >= distance * EV3_MOTOR_DISTANCE_PER_DEGREE + _motor_left_start_position)
                {
                    spdlog::debug("Left motor reached target position");
                    _motorLeft->stop();
                    
                    if (singleMotorStopped)
                    {
                        break;
                    }

                    singleMotorStopped = true;
                }

                if (_motorRight->getPosition() >= distance * EV3_MOTOR_DISTANCE_PER_DEGREE + _motor_right_start_position)
                {
                    spdlog::debug("Right motor reached target position");
                    _motorRight->stop();
    
                    if (singleMotorStopped)
                    {
                        break;
                    }
    
                    singleMotorStopped = true;
                }
            }   

            
            int _current_angle = _gyroSensor->getValue(0).value();

            if (speed > 0) 
            {
                _motorLeft->setDutyCycle(speed - abs(_current_angle - _target_angle));
                _motorRight->setDutyCycle(speed + (_current_angle - _target_angle));
            }

            spdlog::debug("Current angle: " + std::to_string(_current_angle));
            spdlog::debug("Motor Left Position: " + std::to_string(_motorLeft->getPosition()));
            spdlog::debug("Motor Right Position: " + std::to_string(_motorRight->getPosition()));
        }

        #else
        spdlog::trace("Using motor position control");

        setSpeed(speed);
        
        _motorLeft->setPositionSp(distance * EV3_MOTOR_DISTANCE_PER_DEGREE);
        _motorRight->setPositionSp(distance * EV3_MOTOR_DISTANCE_PER_DEGREE);
        
        _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
        _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
        
        // _motorLeft->waitUntilStopped(&position::Position::updatePosition);
        // _motorRight->waitUntilStopped(&position::Position::updatePosition);
        
        while (true)
        {
            finder::position::MotorPosition::updatePosition();
            
            auto leftState = _motorLeft->getState();
            auto rightState = _motorRight->getState();
            if (std::find(leftState.begin(), leftState.end(), MotorState::HOLDING) != leftState.end() &&
            std::find(rightState.begin(), rightState.end(), MotorState::HOLDING) != rightState.end())
            {
                
                spdlog::trace("Motors stopped");
                break;
            }
            
            if (std::find(leftState.begin(), leftState.end(), MotorState::STALLED) != leftState.end() ||
            std::find(rightState.begin(), rightState.end(), MotorState::STALLED) != rightState.end())
            {
                spdlog::error("Motor stalled");
                stop();

                break;
            }
        }
        #endif
        
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
        spdlog::info("Turning " + (direction == TurnDirection::LEFT ? std::string("left") : std::string("right")) + " " + std::to_string(angle) + " at speed " + std::to_string(speed));

        double startAngleDiff = abs(_gyroSensor->getValue(0).value() - angle);
        int checkCount = 0;

        if (angle == _gyroSensor->getValue(0).value()) {
            spdlog::info("Already at target angle");
            return;
        }

        if (speed > 100) {
            spdlog::warn("Speed is higher than 100, setting to 100");
            speed = 100;
        }

        if (_gyroSensor->getValue(0).value() == round(angle)) {
            spdlog::info("Already at target angle");
            return;
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

        std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

        _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
        _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);

        switch (direction)  
        {
        case TurnDirection::LEFT:
            while (true) 
            {
                std::chrono::time_point<std::chrono::system_clock> loopStart = std::chrono::system_clock::now();

                boost::leaf::result<int> result = _gyroSensor->getValue(0);
                if (!result || result.value() >= angle - EV3_GYRO_TURN_TOLERANCE) 
                {
                    spdlog::info("Target angle reached: " + std::to_string(angle) + " Current angle: " + std::to_string(result.value()));
                    break;
                }
                spdlog::debug("Target angle: " + std::to_string(angle));
                spdlog::debug("Current Sensor Angle: " + std::to_string(result.value()));
                spdlog::debug("Current Motor Angle: " + std::to_string(position::MotorPosition::getAngle()));

                spdlog::debug("\rTarget angle: " + std::to_string(angle) + " Current angle: " + std::to_string(result.value()));

                double angleDiff = abs(result.value() - angle);
                double newSpeed = static_cast<double>(speed) - (static_cast<double>(speed) * (1 - (static_cast<double>(angleDiff) / static_cast<double>(startAngleDiff))));

                double newSpeedSlowStart = static_cast<double>(speed) - (static_cast<double>(speed) * (static_cast<double>(angleDiff) / static_cast<double>(startAngleDiff)));

                int leftDutyCycle = -round(std::min(newSpeed, newSpeedSlowStart)) - 15;
                int rightDutyCycle = round(std::min(newSpeed, newSpeedSlowStart)) + 15;
                setDutyCycle(leftDutyCycle, rightDutyCycle);

                spdlog::debug("Start Angle Diff: " + std::to_string(startAngleDiff));
                spdlog::debug("Angle Diff: " + std::to_string(angleDiff));
                spdlog::debug("New Speed: " + std::to_string(static_cast<int>(newSpeed)));


                // if (direction == TurnDirection::LEFT)
                // {
                //     _motorLeft->setDutyCycle(-speed - abs(result.value() - angle));
                //     _motorRight->setDutyCycle(speed + abs(result.value() - angle));
                // }
                // else
                // {
                //     _motorLeft->setDutyCycle(speed + abs(result.value() - angle));
                //     _motorRight->setDutyCycle(-speed - abs(result.value() - angle));
                // }

                checkCount++;

                std::chrono::time_point<std::chrono::system_clock> loopEnd = std::chrono::system_clock::now();

                std::chrono::duration<double> elapsed_seconds = loopEnd - loopStart;

                spdlog::info("Elapsed time for loop execution: " + std::to_string(elapsed_seconds.count()) + " seconds");

            }
            break;
        
        case TurnDirection::RIGHT:
            while (true) 
            {
                boost::leaf::result<int> result = _gyroSensor->getValue(0);
                if (!result || result.value() <= angle + EV3_GYRO_TURN_TOLERANCE) 
                {
                    spdlog::info("Target angle reached: " + std::to_string(angle) + " Current angle: " + std::to_string(result.value()));
                    break;
                }
                spdlog::debug("Target angle: " + std::to_string(angle));
                spdlog::debug("Current Sensor Angle: " + std::to_string(result.value()));
                spdlog::debug("Current Motor Angle: " + std::to_string(position::MotorPosition::getAngle()));

                double angleDiff = abs(result.value() - angle);
                double newSpeed = static_cast<double>(speed) - (static_cast<double>(speed) * (1 - (static_cast<double>(angleDiff) / static_cast<double>(startAngleDiff))));

                double newSpeedSlowStart = static_cast<double>(speed) - (static_cast<double>(speed) * (static_cast<double>(angleDiff) / static_cast<double>(startAngleDiff)));

                int leftDutyCycle =   round(std::min(newSpeed, newSpeedSlowStart)) + 15;
                int rightDutyCycle = -round(std::min(newSpeed, newSpeedSlowStart)) - 15;
                setDutyCycle(leftDutyCycle, rightDutyCycle);

                // _motorLeft->setDutyCycle(speed + abs(result.value() - angle));
                // _motorRight->setDutyCycle(-speed - abs(result.value() - angle));
            }
            break;

        default:
            spdlog::error("Invalid turn direction");
            break;
        }


        _motorLeft->stop();
        _motorRight->stop();

        // position::Position::updatePosition();

        std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;

        spdlog::info("Checked " + std::to_string(checkCount) + " times in " + std::to_string(elapsed_seconds.count()) + " seconds: " + std::to_string(checkCount / elapsed_seconds.count()) + " checks per second");

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
