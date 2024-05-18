#ifndef __MOVEMENT_ENGINE_HPP__
#define __MOVEMENT_ENGINE_HPP__

#include <math/Vector2.hpp>
#include <pf/AStar.hpp>
#include <utility/RobotMovement/RobotMovement.hpp>
#include <utility/RobotMovement/MovementAction.hpp>


namespace finder::engines::movement
{
    class MovementEngine {
        public:
            MovementEngine();
            ~MovementEngine();

            static void move(math::Vector2 destination);

        private:
            static pathfind::ObstacleManager _obstacleManager;
            static pathfind::AStar _astar;

    };
} // namespace finder::movement

#endif // __MOVEMENT_ENGINE_HPP__