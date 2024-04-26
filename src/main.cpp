#include <console/Logger.hpp>
#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <utility/RobotMovement/RobotMovement.hpp>

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

    finder::robot::RobotMovement robotMovement;

    robotMovement.move(finder::robot::MovementType::FORWARD, 100, 100, 1);
    robotMovement.move(finder::robot::MovementType::BACKWARD, 100, 100, 1);
    robotMovement.move(finder::robot::MovementType::TURN_RIGHT, 100, 100, 1);
    robotMovement.move(finder::robot::MovementType::TURN_LEFT, 100, 100, 1);

    while (true)
    {
        std::cout << "Press enter to continue..." << std::endl;
        std::cin.get();
        break;
    }

    logger.success("Application finished.");
    return 0;
}
