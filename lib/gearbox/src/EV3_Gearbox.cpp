#include "EV3_Gearbox.hpp"


namespace finder::physical
{
    int GearboxManager::_gearStartOffset = 0;

    GearboxManager::GearboxManager() : DeviceManager()
    {
        spdlog::trace("Initializing GearboxManager");

        // this->init("/sys/class/");
    }

    GearboxManager::~GearboxManager()
    {
    }

    boost::leaf::result<void> GearboxManager::setGear(GearboxGears gear)
    {
        spdlog::trace("Setting gear to {}", gear);

        if (!isInitialized())
        {
            spdlog::error("GearboxManager not initialized");
            return boost::leaf::new_error(std::logic_error("GearboxManager not initialized"));
        }

        _motorShift->setSpeed(EV3_GEARBOX_SHIFT_SPEED);

        boost::leaf::result<void> status = _motorShift->moveToAbsPosition(gear + _gearStartOffset);

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
        spdlog::trace("Calibrating gearbox");

        if (!isInitialized())
        {
            spdlog::error("GearboxManager not initialized");
            return boost::leaf::new_error(std::logic_error("GearboxManager not initialized"));
        }

        _motorShift->reset();

        ToolControl toolControl = ToolControl{};

        std::array<GearboxGears, 4> gears = {GearboxGears::EV3_GEARBOX_GEAR_1,
                                             GearboxGears::EV3_GEARBOX_GEAR_2,
                                             GearboxGears::EV3_GEARBOX_GEAR_3,
                                             GearboxGears::EV3_GEARBOX_GEAR_4};


        bool _foundBlocked = false;

        for (GearboxGears gear : gears)
        {
            spdlog::trace("Calibrating gear {}", gear);

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
                if (_foundBlocked)
                {
                    spdlog::error("Multiple gears blocked, cannot calibrate");
                    return boost::leaf::new_error(std::runtime_error("Multiple gears blocked, cannot calibrate"));
                }
                _gearStartOffset = gear;
                _foundBlocked = true;
            }   
        }

        // return boost::leaf::new_error(std::invalid_argument("Function not implemented"));
        return boost::leaf::result<void>();
    }

} // namespace finder::physical
