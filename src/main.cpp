#include "EV3_conf.hpp"

#include <Logger.hpp>
#include <iostream>
#include <stdio.h>
#include <chrono>


#include <EV3_System.hpp>

finder::log::Logger logger = finder::log::Logger();
finder::system::System ev3_system = finder::system::System();

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

    logger.info("Starting application...");

    ev3_system.start();

//    finder::engines::movement::MovementEngine movementEngine = finder::engines::movement::MovementEngine();
//
//    movementEngine.move(finder::math::Vector2{100, 100});
//    movementEngine.move(finder::math::Vector2{100, 100});
//    movementEngine.move(finder::math::Vector2{100, 100});
//    movementEngine.move(finder::math::Vector2{100, 100});

    

    while (true)
    {
        std::cout << "Press enter to continue..." << std::endl;
        std::cin.get();
        break;
    }

    logger.success("Application finished.");
    return 0;
}
