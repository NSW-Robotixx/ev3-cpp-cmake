#include "ObstacleManager.hpp"

namespace finder::pathfind
{
    std::vector<math::Line> ObstacleManager::_obstacles = {};

    ObstacleManager::ObstacleManager()
    {
    }

    bool ObstacleManager::checkForIntersect(math::Vector2 origin, math::Vector2 destination)
    {
        return false;
    }

} // namespace finder::pathfind
