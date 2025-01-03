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

        spdlog::info("Path: ");
        for (auto &point : m_path)
        {
            spdlog::info("x: " + std::to_string(point.x) + " y: " + std::to_string(point.y));

            finder::engines::movement::MovementEngine::move(point); // Move to the next point
        }
        #endif

        return boost::leaf::result<void>();
    }

    void System::read()
    {
        std::vector<math::Vector3> path = ConfigReader::readDestinationsFromFile();
        m_destinations.insert(m_destinations.end(), path.begin(), path.end());
        
        for (auto &destination : m_destinations)
        {
            boost::leaf::result result = m_compute.getAStarPath(math::Vector2(destination.x, destination.y), m_currentPosition);
            std::vector<math::Vector2> path; 
            if (result) {
                path = result.value();
            } else {
                spdlog::error("Failed to get path, please check the input");
                return; 
            }
            result = m_compute.getSmoothPath(path);

            if (result) {
                path = result.value();
            } else {
                spdlog::error("Failed to get smooth path, please check the log for errors");
                return;
            }

            path.erase(path.begin());
            m_path.insert(m_path.end(), path.begin(), path.end());
            m_currentPosition = math::Vector2(destination.x, destination.y);
        }
    }

    void System::stop()
    {
        #if EV3_COMPUTE_MODULE_TCP_ENABLED
        m_compute.stop();
        #else
        #endif

        spdlog::info("System stopped");
    }

} // namespace finder::system