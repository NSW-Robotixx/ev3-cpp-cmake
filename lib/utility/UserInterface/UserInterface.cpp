#include "UserInterface.hpp"

namespace finder::utility
{
    physical::display::WindowManager UserInterface::windowManager = physical::display::WindowManager{};
    log::Logger UserInterface::logger = log::Logger();

    UserInterface::UserInterface()
    {
        this->start();
    }

    void UserInterface::start()
    {
        _loop_thread = std::async(std::launch::async, &UserInterface::loop);
    }

    void UserInterface::loop()
    {
        while (_running)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            windowManager.updateAll();
            windowManager.pushToScreen();
        }
    }

    void UserInterface::onButtonLeftPressed()
    {
        windowManager.buttonPressed(KEY_LEFT);
        logger.debug("Left button pressed");
    }

    void UserInterface::onButtonRightPressed()
    {
        windowManager.buttonPressed(KEY_RIGHT);
        logger.debug("Right button pressed");
    }

    void UserInterface::onButtonUpPressed()
    {
        windowManager.buttonPressed(KEY_UP);
        logger.debug("Up button pressed");
    }

    void UserInterface::onButtonDownPressed()
    {
        windowManager.buttonPressed(KEY_DOWN);
        logger.debug("Down button pressed");
    }

    void UserInterface::onButtonEnterPressed()
    {
        windowManager.buttonPressed(KEY_ENTER);
        logger.debug("Enter button pressed");
    }

    void UserInterface::onButtonBackPressed()
    {
        windowManager.buttonPressed(KEY_BACK);
        logger.debug("Back button pressed");
    }

    void UserInterface::onButtonLeftReleased()
    {
        windowManager.buttonReleased(KEY_LEFT);
        logger.debug("Left button released");
    }

    void UserInterface::onButtonRightReleased()
    {
        windowManager.buttonReleased(KEY_RIGHT);
        logger.debug("Right button released");
    }

    void UserInterface::onButtonUpReleased()
    {
        windowManager.buttonReleased(KEY_UP);
        logger.debug("Up button released");
    }

    void UserInterface::onButtonDownReleased()
    {
        windowManager.buttonReleased(KEY_DOWN);
        logger.debug("Down button released");
    }

    void UserInterface::onButtonEnterReleased()
    {
        windowManager.buttonReleased(KEY_ENTER);
        logger.debug("Enter button released");
    }

    void UserInterface::onButtonBackReleased()
    {
        windowManager.buttonReleased(KEY_BACK);
        logger.debug("Back button released");
    }

} // namespace finder::utility