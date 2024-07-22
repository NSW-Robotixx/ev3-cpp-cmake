#ifndef __USERINTERFACE_HPP__
#define __USERINTERFACE_HPP__

#include <memory>
#include <future>
#include <atomic>
#include <physical/display/WindowManager.hpp>
#include <physical/buttons/ButtonNotifier.hpp>
#include <log/Logger.hpp>

namespace finder::utility
{
    class UserInterface : public physical::buttons::ButtonNotifier
    {
    public:
        UserInterface();
        static void start();
    private:
        static ::finder::physical::display::WindowManager windowManager;
        static log::Logger logger;
        static std::future<void> _loop_thread;
        static std::atomic<bool> _running;

        void onButtonLeftPressed() override;
        void onButtonRightPressed() override;
        void onButtonUpPressed() override;
        void onButtonDownPressed() override;
        void onButtonEnterPressed() override;
        void onButtonBackPressed() override;

        void onButtonLeftReleased() override;
        void onButtonRightReleased() override;
        void onButtonUpReleased() override;
        void onButtonDownReleased() override;
        void onButtonEnterReleased() override;
        void onButtonBackReleased() override;


        static void loop();
    };   
} // namespace finder::utility


#endif // __USERINTERFACE_HPP__