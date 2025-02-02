#include "Position.hpp"

namespace finder::position
{
    finder::position::MotorPosition Position::m_motor_position = finder::position::MotorPosition(EV3_DEFAULT_PORT_BASE_PATH);
    finder::position::SensorPosition Position::m_sensor_position = finder::position::SensorPosition(EV3_DEFAULT_PORT_BASE_PATH);

    math::Vector2 Position::getPosition()
    {
        Eigen::Vector2d position = m_motor_position.getPosition();
        return math::Vector2(position.x(), position.y());
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