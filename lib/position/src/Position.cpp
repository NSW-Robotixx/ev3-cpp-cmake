#include "Position.hpp"

namespace finder::position
{
    math::Vector2 Position::getPosition()
    {
        return m_motor_position.getPosition();
    }

    float Position::getAngle()
    {
        return m_motor_position.getAngle();
    }
}