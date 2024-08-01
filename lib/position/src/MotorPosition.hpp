#include <Vector2.hpp>
#include <EV3_MotorManager.hpp>

namespace finder::position
{
    class MotorPosition
    {
        public:
            MotorPosition();
            ~MotorPosition();

            static void updatePosition();
            static void init();

            static inline math::Vector2 getPosition() { return _position; }

        private:
            static math::Vector2 _position;
            static float _angle;
    };
}