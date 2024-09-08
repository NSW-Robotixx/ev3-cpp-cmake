#include "../../EV3_conf.hpp"

#include <Vector2.hpp>
#include <pf/AStar.hpp>
#include <pf/SmoothPath.hpp>

namespace finder::compute
{
    class EV3_compute
    {
        public:
            EV3_compute() = default;
            ~EV3_compute() = default;

            static std::vector<math::Vector2> getSmoothPath(const std::vector<math::Vector2>& path);
            static std::vector<math::Vector2> getAStarPath(const math::Vector2& start, const math::Vector2& end);

        private:
            static pathfind::AStar::Generator m_pathfinder;
            static pathfind::SmoothPath m_smooth_path;
    };
} // namespace finder::compute
