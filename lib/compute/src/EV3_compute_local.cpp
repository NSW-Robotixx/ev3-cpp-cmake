#include "EV3_compute_local.hpp"

namespace finder::compute
{
    pathfind::AStar::Generator EV3_compute::m_pathfinder;
    pathfind::SmoothPath EV3_compute::m_smooth_path;

    boost::leaf::result<std::vector<math::Vector2>> EV3_compute::getSmoothPath(const std::vector<math::Vector2> &path)
    {
        boost::leaf::result<std::vector<math::Vector2>> result = m_smooth_path.smoothPath(path);

        if (!result)
        {
            return result.error();
        }

        return m_smooth_path.smoothPath(result.value());
    }

    boost::leaf::result<std::vector<math::Vector2>> EV3_compute::getAStarPath(const math::Vector2 &start, const math::Vector2 &end)
    {
        return m_pathfinder.findPath(start, end);
    }

} // namespace finder::compute
