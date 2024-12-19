#include "MovementEngine.hpp"

namespace finder::engines::movement
{

    MovementEngine::MovementEngine()
    {

    }

    MovementEngine::~MovementEngine()
    {

    }

    void MovementEngine::move(math::Vector2 destination)
    {
        double lineAngle = math::Line(position::Position::getPosition(), destination).getAngle();
        double lineAngleReverse = lineAngle + 180;
        lineAngleReverse = lineAngleReverse > 360 ? lineAngleReverse - 360 : lineAngleReverse;

        if (lineAngle < lineAngleReverse) {
            if (position::Position::getAngle() > lineAngle) {
                physical::MotorManager::turn(physical::TurnDirection::RIGHT, position::Position::getAngle() - lineAngle, 100);
            } else {
                physical::MotorManager::turn(physical::TurnDirection::LEFT, lineAngle - position::Position::getAngle(), 100);
            }

            physical::MotorManager::moveForward(destination.distanceTo(position::Position::getPosition()), 300);
        } else {
            if (position::Position::getAngle() < lineAngle) {
                physical::MotorManager::turn(physical::TurnDirection::LEFT,position::Position::getAngle() - lineAngle, 100);
            } else {
                physical::MotorManager::turn(physical::TurnDirection::RIGHT,position::Position::getAngle() - lineAngle, 100);
            }

            physical::MotorManager::moveForward(destination.distanceTo(position::Position::getPosition()), 300);
        }
    }
} // namespace finder::movement