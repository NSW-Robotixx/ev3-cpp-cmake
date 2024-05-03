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

            bool checkForIntersect(math::Vector2 origin, math::Vector2 destination);

        private:
            static std::vector<math::Line> _obstacles;
    };
} // namespace finder::pathfind

#endif