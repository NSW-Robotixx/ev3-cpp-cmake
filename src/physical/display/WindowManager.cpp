#include <physical/display/WindowManager.hpp>

namespace finder::physical::display
{
    finder::console::Logger ScreenManager::_logger = finder::console::Logger();
    std::vector<std::shared_ptr<Window>> ScreenManager::windows;
    Screen ScreenManager::screen = Screen();

    ScreenManager::ScreenManager()
    {

    }

    ScreenManager::~ScreenManager()
    {

    }

    void ScreenManager::addWindow(std::shared_ptr<Window> window)
    {
        windows.push_back(window);
    }

    void ScreenManager::removeWindow(std::shared_ptr<Window> window)
    {
        for (int i = 0; i < windows.size(); i++)
        {
            if (windows[i] == window)
            {
                windows.erase(windows.begin() + i);
                return;
            }
        }
    }

    void ScreenManager::removeWindow(int index)
    {
        windows.erase(windows.begin() + index);
    }

    void ScreenManager::removeWindow(std::string name)
    {
        for (int i = 0; i < windows.size(); i++)
        {
            if (windows[i]->getName() == name)
            {
                windows.erase(windows.begin() + i);
                return;
            }
        }
    }

    std::shared_ptr<Window> ScreenManager::getWindow(int index)
    {
        if (index < windows.size())
        {
            return windows[index];
        }
        else
        {
            return nullptr;
        }
    }

    std::shared_ptr<Window> ScreenManager::getWinodw(std::string name)
    {
        for (auto &window : windows)
        {
            if (window->getName() == name)
            {
                return window;
            }
        } 
        return nullptr;
    }

    std::shared_ptr<Window> ScreenManager::createWindow(std::string name, int x, int y, int width, int height)
    {
        std::shared_ptr<Window> window = std::make_shared<Window>(name, width, height, x, y);
        windows.push_back(window);
        return window;
    }

    void ScreenManager::updateAll()
    {
        for (auto &window : windows)
        {
            window->update();
        }
    }

    void ScreenManager::remoteUpdate(int index)
    {
        if (index < windows.size())
        {
            windows[index]->update();
        }
    }

    void ScreenManager::remoteUpdate(std::string name)
    {
        for (auto &window : windows)
        {
            if (window->getName() == name)
            {
                window->update();
                return;
            }
        }
    }

    void ScreenManager::pushToScreen()
    {
        for (auto &window : windows)
        {
            _logger.debug("Drawing window: " + window->getName() + " at x: " + std::to_string(window->getStartX()) + " y: " + std::to_string(window->getStartY()));
            for (int y = 0; y < window->getHeight(); y++)
            {
                _logger.debug("Drawing row: " + std::to_string(y + window->getStartY()));
                for (int x = 0; x < window->getWidth(); x++)
                {
                    _logger.debug("Drawing pixel at x: " + std::to_string(x + window->getStartX()) + " y: " + std::to_string(y + window->getStartY()));
                    screen.drawPixel(x + window->getStartX(), y + window->getStartY(), window->getPixels()[y * window->getWidth() + x]);
                    _logger.debug("Pixel drawn");
                }
            }
        }
    }

    void ScreenManager::clearScreen()
    {
        screen.clear();
    }
} // namespace finder::physical::display