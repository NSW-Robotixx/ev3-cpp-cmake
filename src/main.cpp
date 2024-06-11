#include <console/Logger.hpp>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <engines/movement/MovementEngine.hpp>
#include <math/Vector2.hpp>
//#include <SDL.h>

finder::console::Logger logger = finder::console::Logger();

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

    // wait for 500ms
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    logger.info("Starting application...");

    finder::engines::movement::MovementEngine movementEngine = finder::engines::movement::MovementEngine();

    movementEngine.move(finder::math::Vector2{100, 100});
    movementEngine.move(finder::math::Vector2{100, 100});
    movementEngine.move(finder::math::Vector2{100, 100});
    movementEngine.move(finder::math::Vector2{100, 100});

    while (true)
    {
        std::cout << "Press enter to continue..." << std::endl;
        std::cin.get();
        break;
    }

    logger.success("Application finished.");
    return 0;
}
