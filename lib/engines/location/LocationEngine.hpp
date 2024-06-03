#ifndef __LOCATION_ENGINE_HPP__
#define __LOCATION_ENGINE_HPP__

#include <math/Vector2.hpp>
#include <physical/DeviceManager.hpp>

namespace finder::engines::location
{
    class LocationEngine : public physical::DeviceManager {
        public:
            LocationEngine(std::string portBasePath);
            ~LocationEngine();

            static void update();

            static math::Vector2 getPosition();
            static void setPosition(math::Vector2 position);

            static double getHeading() { return _heading; };
            static void setHeading(double heading) { _heading = heading; };

        private:
            static math::Vector2 _position;
            static double _heading;
    };
} // namespace finder::engines::location

#endif // __LOCATION_ENGINE_HPP__