#include "SmoothPath.hpp"
#include "ObstacleManager.hpp"

namespace finder::pathfind
{
    SmoothPath::SmoothPath(const std::vector<math::Vector2>& path)
    {
        m_path = smoothPath(m_path);
    }

    std::vector<math::Vector2> SmoothPath::smoothPath(const std::vector<math::Vector2>& path)
    {
        std::vector<math::Vector2> smoothedPath;
        smoothedPath.push_back(path[0]);

        for (size_t i = 1; i < path.size() - 1; i++)
        {
            math::Line line(smoothedPath.back(), path[i + 1]);

            bool isColliding = ObstacleManager::isColliding(smoothedPath.back(), path[i + 1]);

            if (isColliding)
            {
                smoothedPath.push_back(path[i]);
            }
        }

        smoothedPath.push_back(path.back());

        return smoothedPath;
    }

    std::vector<math::Vector2> SmoothPath::getPath() const
    {
        return m_path;
    }    
} // namespace finder::pf
