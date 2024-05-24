#include "MovementParser.hpp"

namespace finder::engines::movement
{
    MovementParser::MovementParser()
    {
    }

    MovementParser::~MovementParser()
    {
    }

    void MovementParser::parse(std::vector<math::Vector2> path)
    {
        double lineAngle;

        for (math::Vector2 point : path) {
            parse(point);
        }        
    }

    void MovementParser::parse(math::Vector2 destination)
    {
        double lineAngle = math::Line(location::LocationEngine::getPosition(), destination).getAngle();
        double lineAngleReverse = lineAngle + 180;
        lineAngleReverse = lineAngleReverse > 360 ? lineAngleReverse - 360 : lineAngleReverse;

        if (lineAngle < lineAngleReverse) {
            if (location::LocationEngine::getHeading() > lineAngle) {
                _robotMovement.move(robot::RobotMovement::MovementType::TURN_RIGHT, lineAngle - location::LocationEngine::getHeading(), 100, 1);
            } else {
                _robotMovement.move(robot::RobotMovement::MovementType::TURN_LEFT, lineAngle - location::LocationEngine::getHeading(), 100, 1);
            }

            _robotMovement.move(robot::RobotMovement::MovementType::FORWARD, location::LocationEngine::getPosition().distanceTo(destination), 300, 1);
        } else {
            if (location::LocationEngine::getHeading() < lineAngle) {
                _robotMovement.move(robot::RobotMovement::MovementType::TURN_LEFT, location::LocationEngine::getHeading() - lineAngle, 100, 1);
            } else {
                _robotMovement.move(robot::RobotMovement::MovementType::TURN_RIGHT, location::LocationEngine::getHeading() - lineAngle, 100, 1);
            }

            _robotMovement.move(robot::RobotMovement::MovementType::BACKWARD, location::LocationEngine::getPosition().distanceTo(destination), 300, 1);
        }
    }
} // namespace finder::engines::movement