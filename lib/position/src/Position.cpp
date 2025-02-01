#include "Position.hpp"

namespace finder::position
{
    math::Vector2 Position::getPosition()
    {
        return m_motor_position.getPosition();
    }

    float Position::getAngle()
    {
        // return m_motor_position.getAngle();
        return m_sensor_position.getAngle();
    }
    
    void Position::updatePosition()
    {
        m_motor_position.updatePosition();
        m_sensor_position.updatePosition();
    }
}