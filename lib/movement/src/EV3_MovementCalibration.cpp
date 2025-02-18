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

        int current_angle = _gyroSensor->getValue(0).value();
        finder::math::Vector2 current_motor_position = {_motorLeft->getPosition(), _motorRight->getPosition()};
        
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
        _motorLeft->setDutyCycle(-speed);
        _motorRight->setDutyCycle(speed);
        

        _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
        _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
        
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

        return 0;
    }

} // namespace finder::engines::movement
