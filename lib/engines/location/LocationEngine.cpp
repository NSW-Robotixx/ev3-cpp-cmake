#include "LocationEngine.hpp"

namespace finder::engines::location
{
    math::Vector2 LocationEngine::_position;
    double LocationEngine::_heading;

    LocationEngine::LocationEngine(std::string portBasePath) : DeviceManager(portBasePath)
    {
        _position = math::Vector2(0, 0);
    }

    LocationEngine::~LocationEngine()
    {
    }

    void LocationEngine::update()
    {
        _gyroSensor->getValue(0);   
    }

    math::Vector2 LocationEngine::getPosition()
    {
        return _position;
    }

    void LocationEngine::setPosition(math::Vector2 position)
    {
        _position = position;
    }
} // namespace finder::engines::location