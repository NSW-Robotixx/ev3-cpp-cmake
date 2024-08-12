#include <EV3_System.hpp>
#include "../../EV3_conf.hpp"

namespace finder::system
{
    System::System()
    {
    }

    System::~System()
    {
    }

    void System::start()
    {
        std::vector<math::Vector3> desinations = ConfigReader::readDestinationsFromFile();
        m_destinations = std::deque<math::Vector3>(desinations.begin(), desinations.end());

#if EV3_COMPUTE_LOCAL
        // Start the compute module
        m_compute.start();
#endif

        // Start the system
        while (!m_destinations.empty())
        {
            math::Vector3 destination = m_destinations.front();
            m_destinations.pop_front();

            // Send the destination to the compute module

        }

    }

} // namespace finder::system
