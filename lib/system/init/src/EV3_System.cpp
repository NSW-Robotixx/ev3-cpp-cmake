#include <EV3_System.hpp>

namespace finder::system
{
    math::Vector2 System::m_currentPosition = math::Vector2(0, 0);
    std::deque<math::Vector3> System::m_destinations;
    std::deque<math::Vector2> System::m_path;

    boost::leaf::result<void> System::start()
    {
        #if EV3_COMPUTE_MODULE_TCP_ENABLED
        m_compute.start();
        #else 
        std::vector<math::Vector3> path = ConfigReader::readDestinationsFromFile();
        m_destinations.insert(m_destinations.end(), path.begin(), path.end());
        
        for (auto &destination : m_destinations)
        {
            boost::leaf::result result = m_compute.getAStarPath(math::Vector2(destination.x, destination.y), m_currentPosition);
            std::vector<math::Vector2> path; 
            if (result) {
                path = result.value();
            } else {
                return result.error();
            }
            result = m_compute.getSmoothPath(path);

            if (result) {
                path = result.value();
            } else {
                return result.error();
            }

            path.erase(path.begin());
            m_path.insert(m_path.end(), path.begin(), path.end());
            m_currentPosition = math::Vector2(destination.x, destination.y);
        }

        log::Logger::info("Path: ");
        for (auto &point : m_path)
        {
            log::Logger::info("x: " + std::to_string(point.x) + " y: " + std::to_string(point.y));
        }
        #endif

        return boost::leaf::result<void>();
    }

    void System::stop()
    {
        #if EV3_COMPUTE_MODULE_TCP_ENABLED
        m_compute.stop();
        #else
        #endif

        log::Logger::info("System stopped");
    }

} // namespace finder::system