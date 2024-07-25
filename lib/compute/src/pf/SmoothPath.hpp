#ifndef __SMOOTH_PATH_HPP__
#define __SMOOTH_PATH_HPP__

#include <vector>

#include <Vector2.hpp>
#include <Line.hpp>
#include "ObstacleManager.hpp"

namespace finder::pathfind
{
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
        static std::vector<math::Vector2> smoothPath(const std::vector<math::Vector2>& path);

        /// @brief Get the path that has been smoothed
        /// @return Smoothed path as a vector of Vector2
        std::vector<math::Vector2> getPath() const;

    private:
        std::vector<math::Vector2> m_path;
    };
} // namespace finder::pf



#endif // __SMOOTH_PATH_HPP__