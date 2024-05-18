#ifndef __LOCATION_ENGINE_HPP__
#define __LOCATION_ENGINE_HPP__

#include <math/Vector2.hpp>
#include <physical/DeviceManager.hpp>

namespace finder::engines::location
{
    class LocationEngine : public physical::DeviceManager {
        public:
            LocationEngine();
            ~LocationEngine();

            void update();

            math::Vector2 getPosition();
            void setPosition(math::Vector2 position);

        private:
            math::Vector2 _position;
    };
} // namespace finder::engines::location

#endif // __LOCATION_ENGINE_HPP__