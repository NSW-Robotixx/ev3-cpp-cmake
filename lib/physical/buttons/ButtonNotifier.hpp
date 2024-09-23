#if !defined(_MSC_VER)

#ifndef __BUTTONNOTIFIER_H__
#define __BUTTONNOTIFIER_H__ 

#include <future>
#include <vector>
#include <linux/input.h>
#include <linux/input-event-codes.h>
#include <fstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <mutex>

#define EVENT_PATH "/dev/input/by-path/platform-gpio_keys-event"

namespace finder::physical::buttons
{
    /// @brief Class that listens for button presses and notifies the derived class
    class ButtonNotifier {
        private:
            /// @brief Thread that listens for button presses
            static std::future<void> _listener_thread;

            /// @brief File stream for the input event
            static std::ifstream _ifstream;

            /// @brief Flag to exit the thread
            static bool _exit_thread;

            /// @brief Previous key that was pressed
            static __u16 _previous_key;

            /// @brief Mutex for the button notifier
            static std::mutex _mutex;

            /// @brief Instance of the button notifier as this is a singleton
            static std::unique_ptr<ButtonNotifier> _pinstance;
            

            void Dispatcher();

        protected:
            ButtonNotifier();

            /// @brief Triggered when the back button is pressed
            virtual void onButtonBackPressed();

            /// @brief Triggered when the enter button is pressed
            virtual void onButtonEnterPressed();

            /// @brief Triggered when the up button is pressed
            virtual void onButtonUpPressed();

            /// @brief Triggered when the down button is pressed
            virtual void onButtonDownPressed();
            
            /// @brief Triggered when the left button is pressed
            virtual void onButtonLeftPressed();

            /// @brief Triggered when the right button is pressed
            virtual void onButtonRightPressed();


            /// @brief Triggered when the back button is released
            virtual void onButtonBackReleased();

            /// @brief Triggered when the enter button is released
            virtual void onButtonEnterReleased();

            /// @brief Triggered when the up button is released
            virtual void onButtonUpReleased();

            /// @brief Triggered when the down button is released
            virtual void onButtonDownReleased();

            /// @brief Triggered when the left button is released
            virtual void onButtonLeftReleased();

            /// @brief Triggered when the right button is released
            virtual void onButtonRightReleased();

        public:
            ButtonNotifier(ButtonNotifier& other) = delete;

            /// @brief Remove the operator= as this is a singleton
            void operator=(const ButtonNotifier&) = delete;

            /// @brief Get the instance of the button notifier as this is a singleton
            /// @return Pointer to the button notifier
            static std::unique_ptr<ButtonNotifier>& GetInstance();

            /// @brief Start the button notifier
            static void start();

            /// @brief Stop the button notifier
            static void stop();
    };
} // namespace finder::physical::buttons

#endif // __BUTTONNOTIFIER_H__

#endif // _MSC_VER