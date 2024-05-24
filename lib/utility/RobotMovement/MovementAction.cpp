// #include "MovementAction.hpp"

// namespace finder::robot
// {
//     bool MovementAction::_initialized = false;
//     uint MovementAction::_defaultSpeed = 200;
//     ::finder::console::Logger MovementAction::_logger{};
//     std::shared_ptr<::finder::physical::MotorPort> MovementAction::_motorLeft{};
//     std::shared_ptr<::finder::physical::MotorPort> MovementAction::_motorRight{};

//     MovementAction::MovementAction(MovementType type, int distance, int speed, float arcRatio = 1)
//     {
//         if (!_initialized) {
//             ::finder::physical::PortManager _portManager{};

//             _motorLeft = _portManager.borrowMotor(::finder::physical::PortManager::DevicePort::OUTPUT_A);
//             _motorRight = _portManager.borrowMotor(::finder::physical::PortManager::DevicePort::OUTPUT_B);

//             _initialized = true;
//         }

//         if (speed <= 0) {
//             speed = _defaultSpeed;
//         }

//         switch (type)
//         {
//         case MovementType::FORWARD:
//             moveForward(distance, speed, arcRatio);
//             break;
        
//         case MovementType::BACKWARD:
//             moveBackward(distance, speed, arcRatio);
//             break;

//         case MovementType::TURN_LEFT:
//             turnLeft(distance, speed, arcRatio);
//             break;
        
//         case MovementType::TURN_RIGHT:
//             turnRight(distance, speed, arcRatio);
//             break;

//         case MovementType::TURN_ARC_LEFT:
//             turnArcLeft(distance, speed, arcRatio);
//             break;

//         case MovementType::TURN_ARC_RIGHT:
//             turnArcRight(distance, speed, arcRatio);
//             break;

//         default:
//             _logger.error(std::string{"Movement type not recognized: "}.append(std::to_string(static_cast<int>(type))));
//             break;
//         }
//     }

//     void MovementAction::moveForward(int distance, int speed, float arcRatio = 1)
//     {
//         if (_motorLeft->isEnabled() && _motorRight->isEnabled()) {
//             _motorLeft->setPolarity(physical::MotorPolarity::NORMAL);
//             _motorRight->setPolarity(physical::MotorPolarity::NORMAL);

//             _motorLeft->setSpeed(speed);
//             _motorRight->setSpeed(speed);

//             if (distance <= 0) {
//                 _motorLeft->setCommand(physical::MotorCommand::RUN_FOREVER);
//                 _motorRight->setCommand(physical::MotorCommand::RUN_FOREVER);
//             } else {
//                 _motorLeft->setPositionSp(distance);
//                 _motorRight->setPositionSp(distance);

//                 _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
//                 _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
//             }
//         } else {
//             _logger.error("Motors are not enabled");
//         }
//     }

//     void MovementAction::moveBackward(int distance, int speed, float arcRatio = 1)
//     {
//         if (_motorLeft->isEnabled() && _motorRight->isEnabled()) {
//             _motorLeft->setPolarity(physical::MotorPolarity::INVERSED);
//             _motorRight->setPolarity(physical::MotorPolarity::INVERSED);

//             _motorLeft->setSpeed(speed);
//             _motorRight->setSpeed(speed);

//             if (distance <= 0) {
//                 _motorLeft->setCommand(physical::MotorCommand::RUN_FOREVER);
//                 _motorRight->setCommand(physical::MotorCommand::RUN_FOREVER);
//             } else {
//                 _motorLeft->setPositionSp(distance);
//                 _motorRight->setPositionSp(distance);

//                 _motorLeft->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
//                 _motorRight->setCommand(physical::MotorCommand::RUN_TO_REL_POS);
//             }
//         } else {
//             _logger.error("Motors are not enabled");
//         }
//     }

//     void MovementAction::turnLeft(int distance, int speed, float arcRatio = 1)
//     {
//         if (_motorLeft->isEnabled() && _motorRight->isEnabled()) {
//             _motorLeft->setPolarity(physical::MotorPolarity::NORMAL);
//             _motorRight->setPolarity(physical::MotorPolarity::NORMAL);

//             _motorLeft->setDutyCycle(speed);
//             _motorRight->setDutyCycle(speed * LEFT_RIGHT_SWITCH);

//             if (distance <= 0) {
//                 _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
//                 _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
//             } else {
//                 _motorLeft->setPositionSp(distance);
//                 _motorRight->setPositionSp(distance);

//                 _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
//                 _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
//             }
//         } else {
//             _logger.error("Motors are not enabled");
//         }
//     }

//     void MovementAction::turnRight(int distance, int speed, float arcRatio = 1)
//     {
//         if (_motorLeft->isEnabled() && _motorRight->isEnabled()) {
//             _motorLeft->setPolarity(physical::MotorPolarity::INVERSED);
//             _motorRight->setPolarity(physical::MotorPolarity::INVERSED);

//             _motorLeft->setDutyCycle(speed);
//             _motorRight->setDutyCycle(speed * LEFT_RIGHT_SWITCH);

//             if (distance <= 0) {
//                 _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
//                 _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
//             } else {
//                 _motorLeft->setPositionSp(distance);
//                 _motorRight->setPositionSp(distance);

//                 _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
//                 _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
//             }
//         } else {
//             _logger.error("Motors are not enabled");
//         }
//     }

//     void MovementAction::turnArcLeft(int distance, int speed, float arcRatio)
//     {
//         if (_motorLeft->isEnabled() && _motorRight->isEnabled()) {
//             _motorLeft->setPolarity(physical::MotorPolarity::INVERSED);
//             _motorRight->setPolarity(physical::MotorPolarity::INVERSED);

//             _motorLeft->setDutyCycle(speed * arcRatio);
//             _motorRight->setDutyCycle(speed * LEFT_RIGHT_SWITCH);

//             if (distance <= 0) {
//                 _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
//                 _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
//             } else {
//                 _motorLeft->setPositionSp(distance);
//                 _motorRight->setPositionSp(distance);

//                 _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
//                 _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
//             }
//         } else {
//             _logger.error("Motors are not enabled");
//         }
//     }

//     void MovementAction::turnArcRight(int distance, int speed, float arcRatio)
//     {
//         if (_motorLeft->isEnabled() && _motorRight->isEnabled()) {
//             _motorLeft->setPolarity(physical::MotorPolarity::INVERSED);
//             _motorRight->setPolarity(physical::MotorPolarity::INVERSED);

//             _motorLeft->setDutyCycle(speed);
//             _motorRight->setDutyCycle(speed * LEFT_RIGHT_SWITCH * arcRatio);

//             if (distance <= 0) {
//                 _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
//                 _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
//             } else {
//                 _motorLeft->setPositionSp(distance);
//                 _motorRight->setPositionSp(distance);

//                 _motorLeft->setCommand(physical::MotorCommand::RUN_DIRECT);
//                 _motorRight->setCommand(physical::MotorCommand::RUN_DIRECT);
//             }
//         } else {
//             _logger.error("Motors are not enabled");
//         }
//     }

// } // namespace finder::robot