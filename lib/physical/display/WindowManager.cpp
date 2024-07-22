#if !defined(_MSC_VER)

#include <physical/display/WindowManager.hpp>
#include "WindowManager.hpp"

namespace finder::physical::display
{
    finder::log::Logger WindowManager::_logger = finder::log::Logger();
    std::vector<std::shared_ptr<Window>> WindowManager::windows;
    Screen WindowManager::screen = Screen();
    std::shared_ptr<Window> WindowManager::_active_window = nullptr;

    WindowManager::WindowManager()
    {
        _logger.setMinLevel(finder::log::LogLevel::INFO);
    }

    WindowManager::~WindowManager()
    {

    }

    void WindowManager::addWindow(std::shared_ptr<Window> window)
    {
        windows.push_back(window);
    }

    void WindowManager::removeWindow(std::shared_ptr<Window> window)
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

    void WindowManager::removeWindow(int index)
    {
        windows.erase(windows.begin() + index);
    }

    void WindowManager::removeWindow(std::string name)
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

    std::shared_ptr<Window> WindowManager::getWindow(int index)
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

    std::shared_ptr<Window> WindowManager::getWinodw(std::string name)
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

    void WindowManager::updateAll()
    {
        for (auto &window : windows)
        {
            window->update();
        }
    }

    void WindowManager::remoteUpdate(int index)
    {
        if (index < windows.size())
        {
            windows[index]->update();
        }
    }

    void WindowManager::remoteUpdate(std::string name)
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

    void WindowManager::pushToScreen()
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

    void WindowManager::clearScreen()
    {
        screen.clear();
    }

    void WindowManager::buttonPressed(int code)
    {
        if (_active_window == nullptr)
        {
            return;
        }
        
        switch (code)
        {
        case KEY_LEFT:
            _active_window->_button_left_pressed = true;
            break;
        case KEY_RIGHT:
            _active_window->_button_right_pressed = true;
            break;
        case KEY_UP:
            _active_window->_button_up_pressed = true;
            break;
        case KEY_DOWN:
            _active_window->_button_down_pressed = true;
            break;
        case KEY_ENTER:
            _active_window->_button_enter_pressed = true;
            break;
        case KEY_BACK:
            _active_window->_button_back_pressed = true;
            break;
        default:
            break;
        }
    }

    void WindowManager::buttonReleased(int code)
    {
        if (_active_window == nullptr)
        {
            return;
        }
        
        switch (code)
        {
        case KEY_LEFT:
            _active_window->_button_left_released = true;
            break;
        case KEY_RIGHT:
            _active_window->_button_right_released = true;
            break;
        case KEY_UP:
            _active_window->_button_up_released = true;
            break;
        case KEY_DOWN:
            _active_window->_button_down_released = true;
            break;
        case KEY_ENTER:
            _active_window->_button_enter_released = true;
            break;
        case KEY_BACK:
            _active_window->_button_back_released = true;
            break;
        default:
            break;
        }
    }

    void WindowManager::setActiveWindow(std::shared_ptr<Window> window)
    {
        for (auto& win : windows)
        {
            if (win->getName() == window->getName())
            {
                throw new std::invalid_argument{"Window name already taken"};
            }
        }
        _active_window = window;
    }

    void WindowManager::setActiveWindow(int index)
    {
        if (index >= 0 && index < windows.size()) 
        {
            _active_window = windows[index];
            return;
        }
        throw new std::invalid_argument{"Index for new active Window out of range"};
    }

    void WindowManager::setActiveWindow(std::string name)
    {
        for (auto& window : windows)
        {
            if (window->getName() == name)
            {
                _active_window = window;
                return;
            }
        }
        throw new std::invalid_argument{"No matching window name to assign to active Window"};
    }
} // namespace finder::physical::display

#endif // !defined(_MSC_VER)