#ifndef __SCREEN_MANAGER_HPP__
#define __SCREEN_MANAGER_HPP__

#include <memory>
#include <vector>
#include <string>

#include <physical/display/Screen.hpp>
#include <physical/display/Window.hpp>
#include <Logger.hpp>
#include <linux/input-event-codes.h>

namespace finder::physical::display
{
    class WindowManager
    {

        public:
            WindowManager();
            ~WindowManager();

            static void addWindow(std::shared_ptr<Window> window);
            static void removeWindow(std::shared_ptr<Window> window);
            static void removeWindow(int index);
            static void removeWindow(std::string name);
            static std::shared_ptr<Window> getWindow(int index);
            static std::shared_ptr<Window> getWinodw(std::string name);

            static void updateAll();
            static void remoteUpdate(int index);
            static void remoteUpdate(std::string name);

            static void pushToScreen();
            static void clearScreen();

            static void buttonPressed(int code);
            static void buttonReleased(int code);
        private:
            static finder::log::Logger _logger;
            static std::vector<std::shared_ptr<Window>> windows;
            static Screen screen;
            static std::shared_ptr<Window> _active_window;

            static void setActiveWindow(std::shared_ptr<Window> window);
            static void setActiveWindow(int index);
            static void setActiveWindow(std::string name);
    };
} // namespace finder::physical::display


#endif // __SCREEN_MANAGER_HPP__