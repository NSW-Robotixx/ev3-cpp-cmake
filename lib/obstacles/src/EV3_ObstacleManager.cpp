#include <EV3_ObstacleManager.hpp>

namespace finder::physical
{   
    std::vector<Eigen::Vector2i> ObstacleManager::_obstaclesVector;
    std::vector<std::array<Eigen::Vector2f, 2>> ObstacleManager::_obstaclesLines;


    ObstacleManager::ObstacleManager()
    {
        spdlog::trace("ObstacleManager::ObstacleManager()");
    }

    ObstacleManager::~ObstacleManager()
    {
        spdlog::trace("ObstacleManager::~ObstacleManager()");
    }


    /*
        * Load the obstacles from the yaml file into the vector
        * Example:
        * 
        * obstacles:
        *  - x: 100
        *    y: 100
        *  - x: 200
        *    y: 200
        *  - x: 300
        *    y: 300
        * 
    */
    void ObstacleManager::loadObstacles()
    {
        spdlog::trace("ObstacleManager::loadObstacles()");

        // load the obstacles from the yaml file into the vector
        YAML::Node obstaclesFile = YAML::LoadFile(EV3_OBSTACLES_FILE_PATH);
        YAML::Node obstacles = obstaclesFile["obstacles"];
        for (YAML::const_iterator it = obstacles.begin(); it != obstacles.end(); ++it)
        {
            Eigen::Vector2i position;
            position.x() = (*it)["x"].as<int>();
            position.y() = (*it)["y"].as<int>();
            _obstaclesVector.push_back(position);
        }

        YAML::Node obstaclesLines = obstaclesFile["obstacles_lines"];
        for (YAML::const_iterator it = obstaclesLines.begin(); it != obstaclesLines.end(); ++it)
        {
            Eigen::Vector2f start;
            start.x() = (*it)["start"]["x"].as<int>();
            start.y() = (*it)["start"]["y"].as<int>();

            Eigen::Vector2f end;
            end.x() = (*it)["end"]["x"].as<int>();
            end.y() = (*it)["end"]["y"].as<int>();

            _obstaclesLines.push_back({start, end});
        }
    }

    void ObstacleManager::saveObstacles()
    {
        spdlog::trace("ObstacleManager::saveObstacles()");

        // save the obstacles from the vector into the yaml file
        YAML::Node obstacles;
        for (auto &obstacle : _obstaclesVector)
        {
            YAML::Node position;
            position["x"] = obstacle.x();
            position["y"] = obstacle.y();
            obstacles.push_back(position);
        }

        YAML::Node obstaclesFile;
        obstaclesFile["obstacles_vector"] = obstacles;

        YAML::Node obstaclesLines;
        for (auto &obstacle : _obstaclesLines)
        {
            YAML::Node line;
            line["start"]["x"] = obstacle[0].x();
            line["start"]["y"] = obstacle[0].y();
            line["end"]["x"] = obstacle[1].x();
            line["end"]["y"] = obstacle[1].y();
            obstaclesLines.push_back(line);
        }

        obstaclesFile["obstacles_lines"] = obstaclesLines;

        std::ofstream fout(EV3_OBSTACLES_FILE_PATH);
        fout << obstaclesFile;
    }

    void ObstacleManager::addObstacle(Eigen::Vector2i position)
    {
        spdlog::trace("ObstacleManager::addObstacle()");
        _obstaclesVector.push_back(position);
    }

    void ObstacleManager::addObstacleLine(Eigen::Vector2f start, Eigen::Vector2f end)
    {
        spdlog::trace("ObstacleManager::addObstacleLine()");
        
        // add the line to the vector
        _obstaclesLines.push_back({start, end});
    }

    void ObstacleManager::removeObstacle(Eigen::Vector2i position)
    {
        spdlog::trace("ObstacleManager::removeObstacle()");
        _obstaclesVector.erase(std::remove(_obstaclesVector.begin(), _obstaclesVector.end(), position), _obstaclesVector.end());
    }

    bool ObstacleManager::isObstacle(Eigen::Vector2i position)
    {
        spdlog::trace("ObstacleManager::isObstacle()");
        return std::find(_obstaclesVector.begin(), _obstaclesVector.end(), position) != _obstaclesVector.end();
    }

    bool ObstacleManager::isColliding(Eigen::Vector2i start, Eigen::Vector2i end)
    {
        spdlog::trace("ObstacleManager::isColliding()");
        for (auto &obstacle : _obstaclesVector)
        {
            Eigen::Vector2i p1 = start;
            Eigen::Vector2i p2 = end;
            Eigen::Vector2i p3 = obstacle;
            Eigen::Vector2i p4 = obstacle;

            p4.x() = obstacle.x() + 1;

            int denominator = ((p4.y() - p3.y()) * (p2.x() - p1.x())) - ((p4.x() - p3.x()) * (p2.y() - p1.y()));
            int numerator1 = ((p4.x() - p3.x()) * (p1.y() - p3.y())) - ((p4.y() - p3.y()) * (p1.x() - p3.x()));
            int numerator2 = ((p2.x() - p1.x()) * (p1.y() - p3.y())) - ((p2.y() - p1.y()) * (p1.x() - p3.x()));

            // Detect coincident lines (has a problem, read below)
            if (denominator == 0)
                return numerator1 == 0 && numerator2 == 0;

            float r = static_cast<float>(numerator1) / denominator;
            float s = static_cast<float>(numerator2) / denominator;

            return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
        }

        return false;
    }

    Eigen::Vector2i ObstacleManager::getNearestObstacle(Eigen::Vector2i position)
    {
        spdlog::trace("ObstacleManager::getNearestObstacle()");
        Eigen::Vector2i nearestObstacle;
        int minDistance = std::numeric_limits<int>::max();
        for (auto &obstacle : _obstaclesVector)
        {
            int distance = (position - obstacle).norm();
            if (distance < minDistance)
            {
                minDistance = distance;
                nearestObstacle = obstacle;
            }
        }

        return nearestObstacle;
    }
} // namespace finder::physical