#include "EV3_ToolControl.hpp"


namespace finder::physical
{
    ToolControl::ToolControl()
    {
        // absl::call_once(_device_manager_init_once_flag, &DeviceManager::init);

        _currentGear = 0;
    }

    ToolControl::~ToolControl()
    {
    }

    boost::leaf::result<void> ToolControl::setAbsToolPosition(int position)
    {
        if (!isInitialized())
        {
            return boost::leaf::new_error(std::logic_error("ToolControl not initialized"));
        }

        boost::leaf::result<void> status = _motorTool->moveToAbsPosition(position);
        if (!status)
        {
            return status;
        }

        return boost::leaf::result<void>();
    }

    boost::leaf::result<int> ToolControl::getAbsToolPosition()
    {
        if (!isInitialized())
        {
            return boost::leaf::new_error(std::logic_error("ToolControl not initialized"));
        }

        return _motorTool->getPosition();
    }

    boost::leaf::result<void> ToolControl::moveToolForever(int speed)
    {
        if (!isInitialized())
        {
            return boost::leaf::new_error(std::logic_error("ToolControl not initialized"));
        }

        boost::leaf::result<void> status;

        _motorTool->setSpeed(speed);
        status = (_motorTool->setCommand(MotorCommand::RUN_FOREVER));

        if (!status)
        {
            return status;
        }

        return boost::leaf::result<void>();
    }

    boost::leaf::result<void> ToolControl::stopTool()
    {
        if (!isInitialized())
        {
            return boost::leaf::new_error(std::logic_error("ToolControl not initialized"));
        }

        return _motorTool->stop();
    }

    boost::leaf::result<bool> ToolControl::isToolBlocked()
    {
        bool isBlocked = false;

        if (!isInitialized())
        {
            return boost::leaf::new_error(std::logic_error("ToolControl not initialized"));
        }

        boost::leaf::result<void> status = this->moveToolForever(100);
        if (!status)
        {
            return status.error();
        }

        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(EV3_GEAR_BLOCKED_TIMEOUT_MS));

        std::vector<MotorState> states = _motorTool->getState();

        for (MotorState state : states)
        {
            if (state == MotorState::OVERLOADED || state == MotorState::STALLED)
            {
                isBlocked = true;
                break;
            }
        }

        status = (this->stopTool());

        if (status) 
        {
            return status.error();
        }

        return isBlocked;
    }

} // namespace finder::physical
