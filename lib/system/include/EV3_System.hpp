#ifndef __EV3_SYSTEM_HPP__
#define __EV3_SYSTEM_HPP__

#include <Logger.hpp>
#include <Vector3.hpp>
#include <vector>

namespace finder::system
{
    class System
    {
        public:
            System();
            ~System();

            void start();
            void stop();
    };
} // namespace finder::system

#endif // __EV3_SYSTEM_HPP__