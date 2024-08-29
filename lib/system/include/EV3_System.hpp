#ifndef __EV3_SYSTEM_HPP__
#define __EV3_SYSTEM_HPP__

#include <Logger.hpp>
#include <Vector3.hpp>
#include <ConfigReader.hpp>
#include <vector>
#include <deque>

#if EV3_COMPUTE_LOCAL
#include <EV3_compute_tcp.hpp>
#else

#endif

namespace finder::system
{
    class System
    {
        public:
            System();
            ~System();

            void start();
            void stop();

        private:
            std::deque<math::Vector3> m_destinations;
            compute::EV3_compute m_compute;
    };
} // namespace finder::system

#endif // __EV3_SYSTEM_HPP__