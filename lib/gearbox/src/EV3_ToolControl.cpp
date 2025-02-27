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

    boost::leaf::result<void> ToolControl::moveToAbsToolPosition(int position, int speed)
    {
        if (!isInitialized())
        {
            return boost::leaf::new_error(std::logic_error("ToolControl not initialized"));
        }

        _motorTool->setSpeed(speed);
        boost::leaf::result<void> status = _motorTool->moveToRelPosition(position);
        if (!status)
        {
            return status;
        }

        _motorTool->waitUntilStopped();

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
        spdlog::trace("ToolControl::moveToolForever(): Moving tool forever at speed {}", speed);

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
        spdlog::trace("ToolControl::stopTool(): Stopping tool");

        if (!isInitialized())
        {
            return boost::leaf::new_error(std::logic_error("ToolControl not initialized"));
        }

        return _motorTool->stop();
    }

    boost::leaf::result<bool> ToolControl::isToolBlocked()
    {
        spdlog::trace("ToolControl::isToolBlocked(): Checking if tool is blocked");

        bool isBlocked = false;

        if (!isInitialized())
        {
            spdlog::error("DeviceManager not initialized");
            return boost::leaf::new_error(std::logic_error("ToolControl not initialized"));
        }

        int position = _motorTool->getPosition();
        spdlog::debug("ToolControl::isToolBlocked(): Tool position: {}", position);


        spdlog::debug("ToolControl::isToolBlocked(): Moving tool to check if it is blocked");
        boost::leaf::result<void> status = this->moveToolForever(400);
        if (!status)
        {
            spdlog::error("ToolControl::isToolBlocked(): Failed to move tool");
            return status.error();
        }

        spdlog::debug("ToolControl::isToolBlocked(): Waiting for tool to move");
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(EV3_GEAR_BLOCKED_TIMEOUT_MS));

        spdlog::debug("ToolControl::isToolBlocked(): Checking if tool is blocked");
        std::vector<MotorState> states = _motorTool->getState();

        for (MotorState state : states)
        {
            if (state == MotorState::OVERLOADED || state == MotorState::STALLED)
            {
                spdlog::debug("ToolControl::isToolBlocked(): Tool is blocked");
                isBlocked = true;
                break;
            }
        }

        if (_motorTool->getPosition() <= position + EV3_GEAR_BLOCKED_TOLERANCE && _motorTool->getPosition() >= position - EV3_GEAR_BLOCKED_TOLERANCE)
        {
            spdlog::debug("ToolControl::isToolBlocked(): Inferring tool is blocked, position has not changed");
            isBlocked = true;
        }
   
        spdlog::debug("ToolControl::isToolBlocked(): Stopping tool");
        status = this->stopTool();

        if (!status) 
        {
            spdlog::debug("ToolControl::isToolBlocked(): Failed to stop tool");
            return status.error();
        }

        return isBlocked;
    }

} // namespace finder::physical
