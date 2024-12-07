#ifndef __SMOOTH_PATH_HPP__
#define __SMOOTH_PATH_HPP__

#include <vector>
#include <boost/leaf.hpp>

#include <Vector2.hpp>
#include <Line.hpp>
#include "ObstacleManager.hpp"

namespace finder::pathfind
{
    /// @brief Smooth path class to remove unnecessary points from a path
    class SmoothPath
    {
    public:
        /// @brief Construct a new Smooth Path object
        SmoothPath() = default;

        /// @brief Construct a new Smooth Path object
        /// @param path Path to smooth
        SmoothPath(const std::vector<math::Vector2>& path);

        /// @brief Destroy the Smooth Path object
        ~SmoothPath() = default;

        /// @brief Smooth the path using the by removing unnecessary points, if set in Contructor, this will be called automatically
        /// @param path Path to smooth
        /// @return Smoothed path as a vector of Vector2. Prone to change to Eigen3 library
        static boost::leaf::result<std::vector<math::Vector2>> smoothPath(const std::vector<math::Vector2>& path);

        /// @brief Get the path that has been smoothed
        /// @return Smoothed path as a vector of Vector2
        boost::leaf::result<std::vector<math::Vector2>> getPath() const;

    private:
        std::vector<math::Vector2> m_path;
    };
} // namespace finder::pf



#endif // __SMOOTH_PATH_HPP__