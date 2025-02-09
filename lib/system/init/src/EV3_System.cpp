#include <EV3_System.hpp>

namespace finder::system
{
    finder::engines::movement::GearboxManager System::m_gearbox;
    finder::engines::movement::ToolControl System::m_tool;
    math::Vector2 System::m_currentPosition = math::Vector2(0, 0);
    std::deque<Destination> System::m_destinations;
    std::deque<Destination> System::m_path;
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
        for (const auto& point : m_path)
        {
            spdlog::info("x: " + std::to_string(point.x) + " y: " + std::to_string(point.y) + " angle: " + std::to_string(point.angle));
        }

        int pathSize = m_path.size();

        spdlog::debug("Path size: " + std::to_string(pathSize));

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

            finder::engines::movement::MovementEngine::moveToPoint(math::Vector3(m_path[i].x, m_path[i].y, m_path[i].angle)); // Move to the next point

            finder::position::MotorPosition::setPosition(math::Vector2(m_path[i].x, m_path[i].y)); // Update the position

            if (m_path[i].gear > -1)
            {
                switch (m_path[i].gear)
                {
                case 0:
                    m_gearbox.setGear(finder::physical::GearboxGears::EV3_GEARBOX_GEAR_1);
                    break;
                case 1:
                    m_gearbox.setGear(finder::physical::GearboxGears::EV3_GEARBOX_GEAR_2);
                    break;
                case 2:
                    m_gearbox.setGear(finder::physical::GearboxGears::EV3_GEARBOX_GEAR_3);
                    break;
                case 3:
                    m_gearbox.setGear(finder::physical::GearboxGears::EV3_GEARBOX_GEAR_4);            
                    break;
                
                default:
                    spdlog::error("Invalid gear: " + std::to_string(m_path[i].gear));
                    break;
                }
            }

            if (m_path[i].tool != "")
            {
                if (m_path[i].tool == "inf")
                {
                    m_tool.moveToolForever(EV3_MOTOR_TOOL_SPEED);
                }
                else if (m_path[i].tool == "-inf")
                {
                    m_tool.moveToolForever(-EV3_MOTOR_TOOL_SPEED);
                }
                else
                {
                    m_tool.moveToAbsToolPosition(std::stoi(m_path[i].tool), EV3_MOTOR_TOOL_SPEED);
                }
            }


            // finder::engines::movement::MovementEngine::turn(physical::TurnDirection::LEFT, point.y, EV3_TURN_SPEED); 
        }

        spdlog::info("Finished path");

        return boost::leaf::result<void>();
    }

    void System::read()
    {
        std::vector<Destination> pathYaml = ConfigReader::readDestinationsFromFile();
        m_destinations.insert(m_destinations.end(), pathYaml.begin(), pathYaml.end());
        
        for (const auto& destination : m_destinations)
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


            // add the angle coordinates back to the path
            std::vector<Destination> pathWithAngle;
            for (auto &point : path)
            {
                pathWithAngle.push_back(Destination(point.x, point.y, -1, -1, "", -1));
            }

            pathWithAngle.back().angle = destination.angle; 
            pathWithAngle.back().gear = destination.gear;
            pathWithAngle.back().tool = destination.tool;
            pathWithAngle.back().wait = destination.wait;


            m_path.insert(m_path.end(), pathWithAngle.begin(), pathWithAngle.end());
            m_currentPosition = math::Vector2(destination.x, destination.y);
        }

        spdlog::info("Path read: ");
        for (const auto& point : m_path)
        {
            spdlog::info("x: " + std::to_string(point.x) + " y: " + std::to_string(point.y) + " angle: " + std::to_string(point.angle));
        }
    }

    void System::stop()
    {
        #if EV3_COMPUTE_MODULE_TCP_ENABLED
        m_compute.stop();
        #else
        spdlog::info("TCP compute module is not enabled.");
        #endif

        spdlog::info("System stopped");
    }

} // namespace finder::system