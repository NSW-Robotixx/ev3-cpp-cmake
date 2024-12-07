#include "../../EV3_conf.hpp"

#include <Vector2.hpp>
#include <pf/AStar.hpp>
#include <pf/SmoothPath.hpp>

namespace finder::compute
{
    /// @brief  Class for computing paths for the EV3 robot using A* and smoothing algorithms. This class does not use TCP.
    class EV3_compute
    {
        public:
            EV3_compute() = default;
            ~EV3_compute() = default;

            /// @brief Get a smoothed path from a given path, therefore the unused points will be removed.
            /// @param path The path to smooth
            /// @return Smoothed path as a vector of Vector2
            static boost::leaf::result<std::vector<math::Vector2>> getSmoothPath(const std::vector<math::Vector2>& path);

            /// @brief Calculate a path from start to end using A* algorithm. Diagonal movement is allowed.
            /// @param start Beginning point of the path
            /// @param end Ending point of the path
            /// @return Calculated path as a vector of Vector2
            static boost::leaf::result<std::vector<math::Vector2>> getAStarPath(const math::Vector2& start, const math::Vector2& end);

        private:
            static pathfind::AStar::Generator m_pathfinder;
            static pathfind::SmoothPath m_smooth_path;
    };
} // namespace finder::compute
