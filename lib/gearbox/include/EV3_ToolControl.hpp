#include <EV3_MotorManager.hpp>

#include <chrono>

#include "../../EV3_conf.hpp"

namespace finder::physical
{
    /// @brief Tool control class
    class ToolControl : public DeviceManager
    {
        public:
            /// @brief Constructor for ToolControl
            ToolControl();
            ~ToolControl();
            
            /// @brief Set the tool position
            /// @param position The position to set the tool to
            /// @return boost::leaf::result<void>
            boost::leaf::result<void> setAbsToolPosition(int position);

            /// @brief Get the tool position
            /// @return boost::leaf::result<int> The position of the tool in Motor tachometer counts or an error
            boost::leaf::result<int> getAbsToolPosition();

            /// @brief Move the tool infinitely
            /// @param speed The speed to move the tool at
            /// @return boost::leaf::result<void>
            boost::leaf::result<void> moveToolForever(int speed);

            /// @brief Stop all tool movement
            /// @return boost::leaf::result<void>
            boost::leaf::result<void> stopTool();

            /// @brief check if tool is blocked
            /// @return boost::leaf::result<bool> True if blocked, false if not or an error
            boost::leaf::result<bool> isToolBlocked();

    
        private:

            int _currentGear;
    };
} // namespace finder::physical
