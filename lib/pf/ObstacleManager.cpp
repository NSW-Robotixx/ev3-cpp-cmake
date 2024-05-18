#include "ObstacleManager.hpp"

namespace finder::pathfind
{
    std::vector<math::Line> ObstacleManager::_obstacles = {};

    ObstacleManager::ObstacleManager()
    {
    }

    bool ObstacleManager::isColliding(math::Vector2 origin, math::Vector2 destination)
    {
        bool collision = false;

        for (const math::Line& obstacle : _obstacles)
        {
            if (obstacle.isIntersecting(math::Line(origin, destination)))
            {
                collision = true;
                break;
            }
        }

        return collision;
    }

} // namespace finder::pathfind
