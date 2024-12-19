#include "MotorPosition.hpp"
#include <EV3_SensorManager.hpp>

namespace finder::position
{
    math::Vector2 MotorPosition::_position;
    float MotorPosition::_angle;

    MotorPosition::MotorPosition()
    {
        init();
    }

    MotorPosition::~MotorPosition()
    {
    }

    void MotorPosition::updatePosition()
    {
    }

    void MotorPosition::init()
    {
        
    }

} // namespace finder::position
