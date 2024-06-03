#include "MovementEngine.hpp"

namespace finder::engines::movement
{
    pathfind::AStar::Generator MovementEngine::_astar;

    MovementEngine::MovementEngine()
    {
    }

    MovementEngine::~MovementEngine()
    {
    }

    void MovementEngine::move(math::Vector2 destination)
    {
        if (pathfind::ObstacleManager::isColliding(location::LocationEngine::getPosition(), destination))
        {
            // _movementParser.parse(destination);
        } else {
            std::vector<math::Vector2> path = _astar.findPath(location::LocationEngine::getPosition(), destination);
            path = pathfind::SmoothPath::smoothPath(path);
            // _movementParser.parse(path);
        }
    }
} // namespace finder::movement