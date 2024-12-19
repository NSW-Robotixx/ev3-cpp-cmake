#ifndef __MOVEMENT_ENGINE_HPP__
#define __MOVEMENT_ENGINE_HPP__

#include <Vector2.hpp>
#include <EV3_compute_local.hpp>
#include <pf/SmoothPath.hpp>
#include "MovementParser.hpp"
#include <Position.hpp>
#include <EV3_MotorManager.hpp>

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