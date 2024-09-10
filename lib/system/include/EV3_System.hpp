#include "../../EV3_conf.hpp"

#include <Vector2.hpp>
#include <Vector3.hpp>
#include <EV3_compute.hpp>
#include <ConfigReader.hpp>
#include <Logger.hpp>

#include <deque>

#if EV3_COMPUTE_MODULE_TCP_ENABLED
#include <EV3_System_tcp.hpp>
#endif

namespace finder::system
{
    class System
    {
    public:
        System() = default;
        ~System() = default;

        void start();
        void stop();

    private:
        #if EV3_COMPUTE_MODULE_TCP_ENABLED
        finder::system::SystemTcp m_compute;
        #else
        finder::compute::EV3_compute m_compute;
        #endif

        static math::Vector2 m_currentPosition;
        static std::deque<math::Vector3> m_destinations;
        static std::deque<math::Vector2> m_path;
    };
} // namespace finder::system