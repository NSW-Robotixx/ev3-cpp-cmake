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

    absl::Status ToolControl::setAbsToolPosition(int position)
    {
        if (!isInitialized())
        {
            return absl::FailedPreconditionError("ToolControl not initialized");
        }

        absl::Status status = _motorTool->moveToAbsPosition(position);
        if (!status.ok())
        {
            return status;
        }

        return absl::OkStatus();
    }

    absl::StatusOr<int> ToolControl::getAbsToolPosition()
    {
        if (!isInitialized())
        {
            return absl::FailedPreconditionError("ToolControl not initialized");
        }

        return _motorTool->getPosition();
    }

    absl::Status ToolControl::moveToolForever(int speed)
    {
        if (!isInitialized())
        {
            return absl::FailedPreconditionError("ToolControl not initialized");
        }

        absl::Status status;

        _motorTool->setSpeed(speed);
        status.Update(_motorTool->setCommand(MotorCommand::RUN_FOREVER));

        if (!status.ok())
        {
            return status;
        }

        return absl::OkStatus();
    }

    absl::Status ToolControl::stopTool()
    {
        if (!isInitialized())
        {
            return absl::FailedPreconditionError("ToolControl not initialized");
        }

        return _motorTool->stop();
    }

    absl::StatusOr<bool> ToolControl::isToolBlocked()
    {
        bool isBlocked = false;

        if (!isInitialized())
        {
            return absl::FailedPreconditionError("ToolControl not initialized");
        }

        absl::Status status = this->moveToolForever(100);
        if (!status.ok())
        {
            return status;
        }

        absl::SleepFor(absl::Milliseconds(EV3_GEAR_BLOCKED_TIMEOUT_MS));

        std::vector<MotorState> states = _motorTool->getState();

        for (MotorState state : states)
        {
            if (state == MotorState::OVERLOADED || state == MotorState::STALLED)
            {
                isBlocked = true;
                break;
            }
        }

        status.Update(this->stopTool());

        return isBlocked;
    }

} // namespace finder::physical
