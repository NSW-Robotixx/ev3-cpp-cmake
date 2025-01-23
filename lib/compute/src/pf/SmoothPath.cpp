#include "SmoothPath.hpp"
#include <EV3_ObstacleManager.hpp>

namespace finder::pathfind
{
    SmoothPath::SmoothPath(const std::vector<math::Vector2>& path)
    {
        m_path = path;
    }

    boost::leaf::result<std::vector<math::Vector2>> SmoothPath::smoothPath(const std::vector<math::Vector2>& path)
    {
        std::vector<math::Vector2> smoothedPath;
        smoothedPath.push_back(path[0]);

        for (size_t i = 1; i < path.size() - 1; i++)
        {
            math::Line line(smoothedPath.back(), path[i + 1]);

            bool isColliding = finder::physical::ObstacleManager::isColliding(Eigen::Vector2i(smoothedPath.back().x, smoothedPath.back().y), Eigen::Vector2i(path[i + 1].x, path[i + 1].y));

            if (isColliding)
            {
                smoothedPath.push_back(path[i]);
            }
        }

        smoothedPath.push_back(path.back());

        return smoothedPath;
    }

    boost::leaf::result<std::vector<math::Vector2>> SmoothPath::getPath() const
    {
        return smoothPath(m_path);
    }    
} // namespace finder::pf
