#include "../../EV3_conf.hpp"

#include <Vector2.hpp>
#include <Vector3.hpp>
#include <MotorPosition.hpp>
#include <EV3_compute_local.hpp>
#include <ConfigReader.hpp>
#include <EV3_MovementEngine.hpp>
#include <EV3_Gearbox.hpp>
#include <EV3_ToolControl.hpp>
#include <EV3_ObstacleManager.hpp>

#include <deque>
#include <unistd.h>
#include <signal.h>

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
        System();
        ~System() = default;

        /// @brief Start the system, if enabled the system will connect to the compute module
        /// @return boost::leaf::result<void>
        boost::leaf::result<void> start();

        /// @brief Read the destinations from the file and set them as destinations
        void read();

        /// @brief Stop the system and disconnect from the compute module
        void stop();

    private:
        #if EV3_COMPUTE_MODULE_TCP_ENABLED
        finder::system::SystemTcp m_compute;
        #else
        finder::compute::EV3_compute m_compute;
        #endif

        static finder::engines::movement::GearboxManager m_gearbox;
        static finder::engines::movement::ToolControl m_tool;

        static math::Vector2 m_currentPosition;
        static std::deque<Destination> m_destinations;
        static std::deque<Destination> m_path;

        static int m_currentDestinationIndex;
    };
} // namespace finder::system