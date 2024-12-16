#include <EV3_MotorManager.hpp>
#include <EV3_ToolControl.hpp>
#include "../../EV3_conf.hpp"

#include <array>

namespace finder::physical
{
    /// @brief Manage the connected gearboxes

    enum GearboxGears {
        EV3_GEARBOX_GEAR_1 = EV3_GEARBOX_GEAR_POS_1,
        EV3_GEARBOX_GEAR_2 = EV3_GEARBOX_GEAR_POS_2,
        EV3_GEARBOX_GEAR_3 = EV3_GEARBOX_GEAR_POS_3,
        EV3_GEARBOX_GEAR_4 = EV3_GEARBOX_GEAR_POS_4,
        EV3_GEARBOX_GEAR_NONE = 0
    };

    /// @brief Gearbox controller
    class GearboxManager : public DeviceManager
    {
        public:
            /// @brief Constructor for GearboxManager
            /// @param portBasePath Path to the base path uof the gearboxes
            GearboxManager();
            ~GearboxManager();
            
            /// @brief set the gear of the gearbox
            /// @return boost::leaf::result<void>
            /// @param gear Which gear to set the gearbox to
            boost::leaf::result<void> setGear(GearboxGears gear);

            /// @brief get the current gear of the gearbox
            /// @return boost::leaf::result<GearboxGears>
            boost::leaf::result<GearboxGears> getGear();


            /// @brief calibrate the gearbox
            /// @return boost::leaf::result<void>
            boost::leaf::result<void> calibrate();

    
        private:
            GearboxGears _currentGear = GearboxGears::EV3_GEARBOX_GEAR_NONE;

            static int _gearStartOffset;
    };
}