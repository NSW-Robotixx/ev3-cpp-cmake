#include "EV3_conf.hpp"

#include <spdlog/spdlog.h>
#include <iostream>
#include <stdio.h>
#include <chrono>

// #include <EV3_System.hpp>
#include <EV3_Gearbox.hpp>
#include <DeviceManager.hpp>
#include <EV3_MotorManager.hpp>

// finder::log::Logger logger = finder::log::Logger();
// finder::system::System ev3_system = finder::system::System();
finder::physical::GearboxManager gearbox_manager = finder::physical::GearboxManager();

constexpr auto& ascii_art_literal = R"(
  _____ _           _ _____      
 |  ___(_)_ __   __| |___ / _ __ 
 | |_  | | '_ \ / _` | |_ \| '__|
 |  _| | | | | | (_| |___) | |   
 |_|   |_|_| |_|\__,_|____/|_|   
                                     _        
  _  _      _  __   _/  /_     _     _/ _/_   
 /_//_/|/|//_'//_'/_/  /_//_/ /_'|/._//_//_'|/
/                         _/                  
)";

int main(int argc, char const *argv[])
{
    std::cout << ascii_art_literal << std::endl;

    spdlog::set_level(spdlog::level::trace);

    // logger.info("Starting application...");

    spdlog::debug("Debug message");

    // ev3_system.start();

    // finder::physical::DeviceManager device_manager = finder::physical::DeviceManager("/sys/class/");
//    finder::engines::movement::MovementEngine movementEngine = finder::engines::movement::MovementEngine();
//
//    movementEngine.move(finder::math::Vector2{100, 100});
//    movementEngine.move(finder::math::Vector2{100, 100});
//    movementEngine.move(finder::math::Vector2{100, 100});
//    movementEngine.move(finder::math::Vector2{100, 100});


    gearbox_manager.calibrate();

    finder::physical::MotorManager motor_manager = finder::physical::MotorManager("/sys/class");

    motor_manager.moveForward(100, 400);
    motor_manager.moveBackward(100, 400);

    motor_manager.stop();

    motor_manager.turn(finder::physical::TurnDirection::LEFT, 90, 200);
    motor_manager.turn(finder::physical::TurnDirection::LEFT, -90, 200);
    motor_manager.turn(finder::physical::TurnDirection::RIGHT, 0, 300);


    // while (true)
    // {
    //     std::cout << "Press enter to continue..." << std::endl;
    //     std::cin.get();
    //     break;
    // }

    // logger.success("Application finished.");
    return 0;
}
