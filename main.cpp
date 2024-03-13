#include <console/Logger.hpp>
#include <physical/display/WindowManager.hpp>
#include <physical/display/Window.hpp>
#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <server/webComponents/WebComponentBase.hpp>

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
    using namespace finder::physical::display;

    std::cout << ascii_art_literal << std::endl;

    // wait for 500ms
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    using namespace finder::physical::display;

    // logger.enforceLogLevel(finder::console::Logger::LogLevel::INFO);

    logger.info("Starting application...");

    WindowManager::clearScreen();

    WindowManager::pushToScreen();

    while (true)
    {
        std::cout << "Press enter to continue..." << std::endl;
        std::cin.get();
        break;
    }
    

    logger.info("Application finished.");
    return 0;
}
