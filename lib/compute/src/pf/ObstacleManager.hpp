#ifndef __OBSTACLE_MANAGER_HPP__
#define __OBSTACLE_MANAGER_HPP__

#include <math/Line.hpp>
#include <vector>

namespace finder::pathfind
{
    class ObstacleManager
    {
        public:
            ObstacleManager();

            static bool isColliding(math::Vector2 origin, math::Vector2 destination);

            static void addObstacle(math::Line obstacle);

        private:
            static std::vector<math::Line> _obstacles;
    };
} // namespace finder::pathfind

#endif