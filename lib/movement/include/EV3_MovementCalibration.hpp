#include <Vector2.hpp>
#include <DeviceManager.hpp>

namespace finder::engines::movement
{
    class  MovementCalibration : public finder::physical::DeviceManager
    {
        public:
            MovementCalibration();
            ~MovementCalibration() = default;

            void start();

            int getMinSpeed() const { return min_speed; }

        private:
            static int min_speed_direct;
            static int min_speed;
    };
} // namespace finder::engines::movement