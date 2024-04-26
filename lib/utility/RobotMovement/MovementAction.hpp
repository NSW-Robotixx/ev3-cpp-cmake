#ifndef __MOVEMENT_ACTION_HPP__
#define __MOVEMENT_ACTION_HPP__

#include <memory>
#include <console/Logger.hpp>
#include <physical/portManager/PortManager.hpp>

#define LEFT_RIGHT_SWITCH -1

namespace finder::robot
{
    enum class MovementType {
        FORWARD = 0,
        BACKWARD = 1,
        TURN_LEFT = 2,
        TURN_RIGHT = 3,
        TURN_ARC_LEFT = 4,
        TURN_ARC_RIGHT = 5
    };

    class MovementAction
    {
        public:
            MovementAction(MovementType type, int distance, int speed, float arcRatio);
            ~MovementAction() = default;

            void moveForward(int distance, int speed);
            void moveBackward(int distance, int speed);
            void turnLeft(int distance, int speed);
            void turnRight(int distance, int speed);
            void turnArcLeft(int distance, int speed, float arcRatio);
            void turnArcRight(int distance, int speed, float arcRatio);

            static int getDefaultSpeed() { return _defaultSpeed; };

        
        private:
            static bool _initialized;
            static uint _defaultSpeed;
            static ::finder::console::Logger _logger;
            static std::shared_ptr<::finder::physical::MotorPort> _motorLeft;
            static std::shared_ptr<::finder::physical::MotorPort> _motorRight;

    };
} // namespace finder::robot


#endif