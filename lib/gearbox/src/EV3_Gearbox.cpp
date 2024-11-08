#include "EV3_Gearbox.hpp"


namespace finder::physical
{
    GearboxManager::GearboxManager()
    {
        
    }

    GearboxManager::~GearboxManager()
    {
    }

    absl::Status GearboxManager::setGear(GearboxGears gear)
    {
        if (!isInitialized())
        {
            return absl::FailedPreconditionError("GearboxManager not initialized");
        }

        absl::Status status = _motorShift->moveToAbsPosition(gear);
        if (!status.ok())
        {
            return status;
        }

        _currentGear = gear;
        return absl::OkStatus();
    }

    absl::StatusOr<GearboxGears> GearboxManager::getGear()
    {
        if (!isInitialized())
        {
            return absl::FailedPreconditionError("GearboxManager not initialized");
        }

        int currentPosition = _motorShift->getPosition();

        // Check if the position is within the range of the gears
        if (currentPosition >= EV3_GEARBOX_GEAR_POS_1 - EV3_GEARBOX_GEAR_POS_TOLERANCE &&
            currentPosition <= EV3_GEARBOX_GEAR_POS_1 + EV3_GEARBOX_GEAR_POS_TOLERANCE)
        {
            return GearboxGears::EV3_GEARBOX_GEAR_1;
        }
        else if (currentPosition >= EV3_GEARBOX_GEAR_POS_2 - EV3_GEARBOX_GEAR_POS_TOLERANCE &&
                 currentPosition <= EV3_GEARBOX_GEAR_POS_2 + EV3_GEARBOX_GEAR_POS_TOLERANCE)
        {
            return GearboxGears::EV3_GEARBOX_GEAR_2;
        }
        else if (currentPosition >= EV3_GEARBOX_GEAR_POS_3 - EV3_GEARBOX_GEAR_POS_TOLERANCE &&
                 currentPosition <= EV3_GEARBOX_GEAR_POS_3 + EV3_GEARBOX_GEAR_POS_TOLERANCE)
        {
            return GearboxGears::EV3_GEARBOX_GEAR_3;
        }
        else if (currentPosition >= EV3_GEARBOX_GEAR_POS_4 - EV3_GEARBOX_GEAR_POS_TOLERANCE &&
                 currentPosition <= EV3_GEARBOX_GEAR_POS_4 + EV3_GEARBOX_GEAR_POS_TOLERANCE)
        {
            return GearboxGears::EV3_GEARBOX_GEAR_4;
        }

        return absl::OutOfRangeError("Position not within gear range");
    }

} // namespace finder::physical
