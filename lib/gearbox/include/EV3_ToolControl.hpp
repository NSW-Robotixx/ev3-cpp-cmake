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
            absl::Status setToolPosition(int position);

            /// @brief Get the tool position
            /// @return absl::StatusOr<int> The position of the tool in Motor tachometer counts or an error
            absl::StatusOr<int> getToolPosition();

            /// @brief Move the tool infinitely
            /// @return absl::Status
            absl::Status moveToolForever();

            /// @brief Stop all tool movement
            /// @return absl::Status
            absl::Status stopTool();
    
        private:
            int _currentPosition;
    };
} // namespace finder::physical
