#include <EV3_MotorManager.hpp>

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
            /// @return absl::Status
            absl::Status setAbsToolPosition(int position);

            /// @brief Get the tool position
            /// @return absl::StatusOr<int> The position of the tool in Motor tachometer counts or an error
            absl::StatusOr<int> getAbsToolPosition();

            /// @brief Move the tool infinitely
            /// @param speed The speed to move the tool at
            /// @return absl::Status
            absl::Status moveToolForever(int speed);

            /// @brief Stop all tool movement
            /// @return absl::Status
            absl::Status stopTool();

            /// @brief check if tool is blocked
            /// @return absl::StatusOr<bool> True if blocked, false if not or an error
            absl::StatusOr<bool> isToolBlocked();

    
        private:

            int _currentGear;
    };
} // namespace finder::physical
