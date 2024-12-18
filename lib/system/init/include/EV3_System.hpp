#include "../../EV3_conf.hpp"

#include <Vector2.hpp>
#include <Vector3.hpp>
#include <EV3_compute_local.hpp>
#include <ConfigReader.hpp>
#include <MovementEngine.hpp>

#include <deque>

#include <spdlog/spdlog.h>
#include <boost/leaf.hpp>

#if EV3_COMPUTE_MODULE_TCP_ENABLED
#include <EV3_System_tcp.hpp>
#endif

namespace finder::system
{

    /// @brief Class that represents the system and handles the communication with the compute module
    class System
    {
    public:
        System() = default;
        ~System() = default;

        /// @brief Start the system, if enabled the system will connect to the compute module
        boost::leaf::result<void> start();

        /// @brief Stop the system and disconnect from the compute module
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