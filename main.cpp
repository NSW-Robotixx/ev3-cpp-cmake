#include <console/Logger.hpp>
#include <physical/display/WindowManager.hpp>
#include <physical/display/Window.hpp>
#include <iostream>

finder::console::Logger logger = finder::console::Logger();

int main(int argc, char const *argv[])
{
    using namespace finder::physical::display;

    logger.info("Starting application...");

    finder::physical::display::ScreenManager screenManager = finder::physical::display::ScreenManager();

    std::shared_ptr<Window> window = screenManager.createWindow("Window 1", 0, 0, 100, 100);

    window->fill(DisplayColors::DISPLAY_BLACK);

    window->drawRectangle(10, 10, 50, 50, DisplayColors::DISPLAY_WHITE);

    screenManager.updateAll();

    screenManager.pushToScreen();

    logger.info("Application finished.");
    return 0;
}
