#include <EV3_System.hpp>
#include "../../EV3_conf.hpp"

namespace finder::system
{
    System::System()
    {
    }

    void System::start()
    {
        m_destinations = ConfigReader::readDestinationsFromFile();

#if EV3_COMPUTE_LOCAL
        // Start the compute module
        m_compute.start();

#endif
    }

} // namespace finder::system
