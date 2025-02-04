#include <EV3_System.hpp>

namespace finder::system
{
    math::Vector2 System::m_currentPosition = math::Vector2(0, 0);
    std::deque<math::Vector3> System::m_destinations;
    std::deque<math::Vector3> System::m_path;
    int System::m_currentDestinationIndex = 0;

    System::System()
    {
        // // stop motors on program exit (ctrl+c)
        // signal(SIGINT, [](int signum) {
        //     spdlog::info("Caught signal: {}", signum);
        //     finder::physical::MotorManager::stop();
        //     exit(signum);
        // });
    }

    boost::leaf::result<void> System::start()
    {
        spdlog::info("Path: ");
        int pathSize = sizeof(m_path)/sizeof(m_path[0]);

        for (int i = m_currentDestinationIndex; i < pathSize; i++)
        {
            spdlog::info("Moving to point x: " + std::to_string(m_path[i].x) + " y: " + std::to_string(m_path[i].y));
            m_currentDestinationIndex = i;

            if (m_path[i].x < 0 || m_path[i].y < 0)
            {
                spdlog::info("Pause Reached");
                m_currentDestinationIndex++;
                break;
            }

            // check if the next point is the last point
            // if (i == pathSize - 1)
            // {
            //     finder::engines::movement::MovementEngine::moveToPoint(m_path[i]); // Move to the next point
            //     break;
            // }

            finder::engines::movement::MovementEngine::moveToPoint(m_path[i]); // Move to the next point

            finder::position::MotorPosition::setPosition(math::Vector2(m_path[i].x, m_path[i].y)); // Update the position


            // finder::engines::movement::MovementEngine::turn(physical::TurnDirection::LEFT, point.y, EV3_TURN_SPEED); 
        }

        return boost::leaf::result<void>();
    }

    void System::read()
    {
        std::vector<math::Vector3> pathYaml = ConfigReader::readDestinationsFromFile();
        m_destinations.insert(m_destinations.end(), pathYaml.begin(), pathYaml.end());
        
        for (auto &destination : m_destinations)
        {
            boost::leaf::result<finder::pathfind::AStar::CoordinateList> result = m_compute.getAStarPath(math::Vector2(destination.x, destination.y), m_currentPosition);
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

            path.end()->x = destination.x;

            // add the z coordinates back to the path

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