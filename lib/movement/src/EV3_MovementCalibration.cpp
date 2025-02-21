#include "EV3_MovementCalibration.hpp"


namespace finder::engines::movement
{
    int MovementCalibration::min_speed_direct = 0;
    int MovementCalibration::min_speed = 0;

    MovementCalibration::MovementCalibration()
    {
    }
    
    void MovementCalibration::start()
    {
        _motorLeft->reset();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        int start_position = _motorLeft->getPosition();
        int current_speed = 0;
        
        spdlog::info("Starting calibration");

        while (true)
        {
            bool stalled = false;
            current_speed += 10;
            _motorLeft->setSpeed(current_speed);
            _motorLeft->setPositionSp(720);
            _motorLeft->setCommand(physical::MotorCommand::RUN_TO_ABS_POS);

            std::this_thread::sleep_for(std::chrono::milliseconds(50));

            for (auto state : _motorLeft->getState())
            {
                if (state == physical::MotorState::STALLED)
                {
                    spdlog::info("Motor stopped");
                    stalled = true;
                    break;
                }
                if (state == physical::MotorState::HOLDING)
                {
                    spdlog::info("Motor holding");
                    stalled = false;
                    break;
                }
            }

            if (stalled)
            {
                min_speed = current_speed;

                spdlog::info("Min speed: {}", min_speed);

                _motorLeft->setSpeed(EV3_DRIVE_SPEED);
                _motorLeft->setPositionSp(start_position);
                _motorLeft->setCommand(physical::MotorCommand::RUN_TO_ABS_POS);
                
                break;
            }
        }
    }
    int MovementCalibration::calibrateTurnAngle(int angle, int speed)
    {
        spdlog::trace("Calibrating turn angle");

        // calibrate gyro
        
        _gyroSensor->calibrateGyro();
        
        _motorLeft->reset();
        _motorRight->reset();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        _motorLeft->setStopAction(physical::MotorStopAction::HOLD);
        _motorRight->setStopAction(physical::MotorStopAction::HOLD);
        _motorLeft->setRampDownSpeed(500);
        _motorRight->setRampDownSpeed(500);
        _motorLeft->setRampUpSpeed(500);
        _motorRight->setRampUpSpeed(500);
        
        int start_angle = _gyroSensor->getValue(0).value();
        int current_angle = _gyroSensor->getValue(0).value();
        finder::math::Vector2 current_motor_position = {_motorLeft->getPosition(), _motorRight->getPosition()};

        spdlog::debug("Starting position: " + std::to_string(current_motor_position.x) + " " + std::to_string(current_motor_position.y));
        
        int target_angle = (current_angle + angle) % 360;

        spdlog::debug("Current angle: " + std::to_string(current_angle));
        spdlog::debug("Target angle: " + std::to_string(target_angle));

        _motorLeft->setDutyCycle(speed);
        _motorRight->setDutyCycle(-speed);

        _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
        _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);

        while (true)
        {
            int current_angle = _gyroSensor->getValue(0).value();
            if (current_angle >= target_angle - EV3_GYRO_TURN_TOLERANCE)
            {
                spdlog::info("Target angle reached: " + std::to_string(target_angle) + " Current angle: " + std::to_string(current_angle));
                break;
            }
            spdlog::debug("Target angle: " + std::to_string(target_angle));
            spdlog::debug("Current Sensor Angle: " + std::to_string(current_angle));
        }

        _motorLeft->stop();
        _motorRight->stop();

        finder::math::Vector2 new_motor_position = {_motorLeft->getPosition(), _motorRight->getPosition()};
        finder::math::Vector2 motor_position_diff = new_motor_position - current_motor_position;

        spdlog::debug("Motor position diff: " + std::to_string(motor_position_diff.x) + " " + std::to_string(motor_position_diff.y));
        
        // rotate back to original position

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        _motorLeft->setDutyCycle(-speed);
        _motorRight->setDutyCycle(speed);
        

        _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
        _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);

        target_angle = start_angle;
        
        while (true)
        {
            int current_angle = _gyroSensor->getValue(0).value();
            if (current_angle <= target_angle + EV3_GYRO_TURN_TOLERANCE)
            {
                spdlog::info("Target angle reached: " + std::to_string(target_angle) + " Current angle: " + std::to_string(current_angle));
                break;
            }
            spdlog::debug("Target angle: " + std::to_string(target_angle));
            spdlog::debug("Current Sensor Angle: " + std::to_string(current_angle));
        }

        _motorLeft->stop();
        _motorRight->stop();
        

        finder::math::Vector2 new_motor_start_position = {_motorLeft->getPosition(), _motorRight->getPosition()};
        finder::math::Vector2 motor_start_position_diff = new_motor_start_position - current_motor_position;


        spdlog::debug("Motor start position difference: " + std::to_string(motor_start_position_diff.x) + " " + std::to_string(motor_start_position_diff.y));

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        
        spdlog::info("Repeating with calibration results");

        
        _motorLeft->setPositionSp(motor_position_diff.x);
        _motorRight->setPositionSp(motor_position_diff.y);

        _motorLeft->setSpeed(EV3_DRIVE_SPEED);
        _motorRight->setSpeed(EV3_DRIVE_SPEED);

        _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
        _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);

        while (true)
        {
            if (_motorLeft->isStalled() || _motorRight->isStalled())
            {
                spdlog::info("Stalled");
                break;
            }

            if (_motorLeft->isHolding() && _motorRight->isHolding())
            {
                spdlog::info("Holding");
                break;
            }
        }
        
        spdlog::info("Gyro angle: " + std::to_string(_gyroSensor->getValue(0).value()));

        // turn back to original position
        _motorLeft->setPositionSp(current_motor_position.x);
        _motorRight->setPositionSp(current_motor_position.y);

        

        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 

        _motorLeft->setSpeed(EV3_DRIVE_SPEED);
        _motorRight->setSpeed(EV3_DRIVE_SPEED);

        _motorLeft->setCommand(physical::MotorCommand::RUN_TO_ABS_POS);
        _motorRight->setCommand(physical::MotorCommand::RUN_TO_ABS_POS);

        while (true)
        {
            if (_motorLeft->isStalled() || _motorRight->isStalled())
            {
                spdlog::info("Stalled");
                break;
            }

            if (_motorLeft->isHolding() && _motorRight->isHolding())
            {
                spdlog::info("Holding");
                break;
            }
        }

        spdlog::info("Gyro angle: " + std::to_string(_gyroSensor->getValue(0).value()));


        // calculate the motor movement per degree
        finder::math::Vector2 motor_movement_per_degree_vector = motor_position_diff / angle;
        float motor_movement_per_degree = (motor_movement_per_degree_vector.x + motor_movement_per_degree_vector.y) / 2;

        spdlog::info("Motor movement per degree: " + std::to_string(motor_movement_per_degree));
        spdlog::info("Calibration completed successfully.");

        spdlog::debug("Using new values to turn again");

        _motorLeft->setPositionSp(motor_movement_per_degree * angle*2);
        _motorRight->setPositionSp(-motor_movement_per_degree * angle*2);
        

        current_motor_position = {_motorLeft->getPosition(), _motorRight->getPosition()};

        _motorLeft->setSpeed(EV3_DRIVE_SPEED);
        _motorRight->setSpeed(EV3_DRIVE_SPEED);
        _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
        _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);


        while (true)
        {
            if (_motorLeft->isStalled() || _motorRight->isStalled())
            {
                spdlog::info("Stalled during turn execution");
                break;
            }

            if (_motorLeft->isHolding() && _motorRight->isHolding())
            {
                spdlog::info("Holding after turn execution");
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        spdlog::info("Gyro angle: " + std::to_string(_gyroSensor->getValue(0).value()));

        _motorLeft->setPositionSp(motor_movement_per_degree * angle * 2);
        _motorRight->setPositionSp(-motor_movement_per_degree * angle * 2);


        _motorLeft->setSpeed(EV3_DRIVE_SPEED);
        _motorRight->setSpeed(EV3_DRIVE_SPEED);

        _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
        _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);

        while (true)
        {
            if (_motorLeft->isStalled() || _motorRight->isStalled())
            {
                spdlog::info("Stalled during turn execution");
                break;
            }

            if (_motorLeft->isHolding() && _motorRight->isHolding())
            {
                spdlog::info("Holding after turn execution");
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        spdlog::info("starting gyro angle: " + std::to_string(_gyroSensor->getValue(0).value()));

        return 0;
    }

} // namespace finder::engines::movement
