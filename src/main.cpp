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

    robotMovement.moveForward(100);
    robotMovement.moveBackward(100);
    robotMovement.turnLeft(90);
    robotMovement.turnRight(90);

    while (true)
    {
        std::cout << "Press enter to continue..." << std::endl;
        std::cin.get();
        break;
    }

    logger.info("Application finished.");
    return 0;
}
