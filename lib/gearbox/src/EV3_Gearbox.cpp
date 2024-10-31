#include "EV3_Gearbox.hpp"

finder::physical::GearboxManager::GearboxManager()
{
    
}

finder::physical::GearboxManager::~GearboxManager()
{
}

absl::Status finder::physical::GearboxManager::setGear(GearboxGears gear)
{
    if (!isInitialized())
    {
        return absl::FailedPreconditionError("GearboxManager not initialized");
    }

    absl::Status status = _motorShift->moveToPosition(gear);
    if (!status.ok())
    {
        return status;
    }

    return absl::OkStatus();
}
