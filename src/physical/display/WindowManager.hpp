#ifndef __SCREEN_MANAGER_HPP__
#define __SCREEN_MANAGER_HPP__

#include <memory>
#include <vector>
#include <string>

#include <physical/display/Screen.hpp>
#include <physical/display/Window.hpp>
#include <console/Logger.hpp>

namespace finder::physical::display
{
    class ScreenManager
    {
        public:
            ScreenManager();
            ~ScreenManager();

            static void addWindow(std::shared_ptr<Window> window);
            static void removeWindow(std::shared_ptr<Window> window);
            static void removeWindow(int index);
            static void removeWindow(std::string name);
            static std::shared_ptr<Window> getWindow(int index);
            static std::shared_ptr<Window> getWinodw(std::string name);
            static std::shared_ptr<Window> createWindow(std::string name, int x, int y, int width, int height);

            static void updateAll();
            static void remoteUpdate(int index);
            static void remoteUpdate(std::string name);

            static void pushToScreen();
            static void clearScreen();
        private:
            static finder::console::Logger _logger;
            static std::vector<std::shared_ptr<Window>> windows;
            static Screen screen;
    };
} // namespace finder::physical::display


#endif // __SCREEN_MANAGER_HPP__