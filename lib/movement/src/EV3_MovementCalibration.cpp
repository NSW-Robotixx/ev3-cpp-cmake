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
            _motorLeft->setPositionSp(360);
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
} // namespace finder::engines::movement
