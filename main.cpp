#include <console/Logger.hpp>
#include <physical/display/WindowManager.hpp>
#include <physical/display/Window.hpp>
#include <iostream>
#include <stdio.h>
#include <thread>
#include <chrono>

finder::console::Logger logger = finder::console::Logger();

constexpr auto& ascii_art_literal = R"(
___________________________________________
    _____                       __         
    /    '   ,             /  /    )       
---/__-----------__----__-/---- _ /----)__-
  /        /   /   ) /   /        )   /   )
_/________/___/___/_(___/___(____/___/_____
)";

int main(int argc, char const *argv[])
{
    std::cout << ascii_art_literal << std::endl;

    // wait for 500ms
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    using namespace finder::physical::display;

    // logger.enforceLogLevel(finder::console::Logger::LogLevel::INFO);

    logger.info("Starting application...");

    finder::physical::display::ScreenManager screenManager = finder::physical::display::ScreenManager();

    screenManager.clearScreen();

    screenManager.pushToScreen();

    while (true)
    {
        std::cout << "Press enter to continue..." << std::endl;
        std::cin.get();
        break;
    }
    

    std::shared_ptr<Window> window = screenManager.createWindow("Window 1", 0, 0, 100, 100);

    window->fill(DisplayColors::DISPLAY_BLACK);

    window->drawRectangle(10, 10, 50, 50, DisplayColors::DISPLAY_WHITE);
    window->drawCircle(50, 50, 20, DISPLAY_WHITE);
    window->drawTriangle(10, 10, 50, 10, 50, 50, DISPLAY_WHITE);
    // window->drawText(10, 10, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", DISPLAY_WHITE);
    window->drawText(10, 30, "test", DISPLAY_WHITE);
    logger.debug("drew text");


    screenManager.updateAll();

    while (true) {
        screenManager.pushToScreen();
    }


    logger.info("Application finished.");
    return 0;
}
