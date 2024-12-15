#ifndef __MOVEMENT_ENGINE_HPP__
#define __MOVEMENT_ENGINE_HPP__

#include <Vector2.hpp>
#include <compute/include/EV3_compute_local.hpp>
#include <pf/SmoothPath.hpp>
#include <utility/RobotMovement/RobotMovement.hpp>
#include <utility/RobotMovement/MovementAction.hpp>
#include <engines/location/LocationEngine.hpp>
#include "MovementParser.hpp"


namespace finder::engines::movement
{
    class MovementEngine {
        public:
            MovementEngine();
            ~MovementEngine();

            static void move(math::Vector2 destination);

        private:
    };
} // namespace finder::movement

#endif // __MOVEMENT_ENGINE_HPP__