#include <Vector2.hpp>
#include <DeviceManager.hpp>

namespace finder::engines::movement
{
    /// @brief Class that handles the movement calibration
    class  MovementCalibration : public finder::physical::DeviceManager
    {
        public:
            MovementCalibration();
            ~MovementCalibration() = default;

            /// @brief Start the movement calibration
            void start();

            /// @brief Retrieves the minimum speed of the movement calibration
            /// @return The minimum speed as an integer
            int getMinSpeed() const { return min_speed; }

            int calibrateTurnAngle(int angle, int speed);

        private:
            static int min_speed_direct;
            static int min_speed;
    };
} // namespace finder::engines::movement