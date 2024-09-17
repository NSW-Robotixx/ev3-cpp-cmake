#ifndef __OBSTACLE_MANAGER_HPP__
#define __OBSTACLE_MANAGER_HPP__

#include <Line.hpp>
#include <vector>

namespace finder::pathfind
{
    class ObstacleManager
    {
        public:
            ObstacleManager();

            /// @brief Check if a line segment collides with any obstacles
            /// @param origin The starting point of the line segment
            /// @param destination The ending point of the line segment
            /// @return True if there is a collision, false otherwise
            static bool isColliding(math::Vector2 origin, math::Vector2 destination);

            /// @brief adds an obstacle to the list of obstacles to avoid
            /// @param obstacle The line segment representing the obstacle
            static void addObstacle(math::Line obstacle);

        private:
            static std::vector<math::Line> _obstacles;
    };
} // namespace finder::pathfind

#endif