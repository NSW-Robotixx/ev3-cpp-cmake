#include "EV3_Gearbox.hpp"


namespace finder::physical
{
    int GearboxManager::_gearStartOffset = 0;

    GearboxManager::GearboxManager()
    {
        
    }

    GearboxManager::~GearboxManager()
    {
    }

    boost::leaf::result<void> GearboxManager::setGear(GearboxGears gear)
    {
        if (!isInitialized())
        {
            return boost::leaf::new_error(std::logic_error("GearboxManager not initialized"));
        }

        boost::leaf::result<void> status = _motorShift->moveToAbsPosition(gear);
        if (!status)
        {
            return status;
        }

        _currentGear = gear;
        return boost::leaf::result<void>();
    }

    boost::leaf::result<GearboxGears> GearboxManager::getGear()
    {
        if (!isInitialized())
        {
            return boost::leaf::new_error(std::logic_error("GearboxManager not initialized"));
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

        return boost::leaf::new_error(std::out_of_range("Position not withing gear range"));
    }

    boost::leaf::result<void> GearboxManager::calibrate()
    {
        if (!isInitialized())
        {
            return boost::leaf::new_error(std::logic_error("GearboxManager not initialized"));
        }

        ToolControl toolControl = ToolControl{};

        std::array<GearboxGears, 4> gears = {GearboxGears::EV3_GEARBOX_GEAR_1,
                                             GearboxGears::EV3_GEARBOX_GEAR_2,
                                             GearboxGears::EV3_GEARBOX_GEAR_3,
                                             GearboxGears::EV3_GEARBOX_GEAR_4};

        for (GearboxGears gear : gears)
        {
            boost::leaf::result<void> status = setGear(gear);
            if (!status)
            {
                return status;
            }

            boost::leaf::result<bool> statusBlocked = toolControl.isToolBlocked();

            if (!status)
            {
                return statusBlocked.error();
            }

            if (statusBlocked.value())
            {
                _gearStartOffset = gear;
            }   
        }

        return boost::leaf::new_error(std::invalid_argument("Function not implemented"));
    }

} // namespace finder::physical
