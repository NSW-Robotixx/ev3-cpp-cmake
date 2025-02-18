#pragma once

#include <Eigen/Dense>
#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>

#include <fstream>
#include <filesystem>

#include "../../EV3_conf.hpp"

namespace finder
{
    namespace physical
    {
        /// @brief Class to manage the obstacles
        class ObstacleManager
        {
        public:
            /// @brief Construct a new Obstacle Manager object
            ObstacleManager();
            ~ObstacleManager();

            /// @brief Load the obstacles from the yaml file into the vector
            static void loadObstacles();

            /// @brief Save the obstacles from the vector into the yaml file
            static void saveObstacles();


            /// @brief Add an obstacle to the vector
            /// @param position The position of the obstacle
            static void addObstacle(Eigen::Vector2i position);

            /// @brief Add an obstacle line to the vector
            /// @param start The start of the line
            /// @param end The end of the line
            static void addObstacleLine(Eigen::Vector2f start, Eigen::Vector2f end);

            /// @brief Remove an obstacle from the vector
            /// @param position The position of the obstacle
            static void removeObstacle(Eigen::Vector2i position);

            /// @brief Check if a position is an obstacle
            /// @param position The position to check
            /// @return true if the position is an obstacle
            static bool isObstacle(Eigen::Vector2i position);

            /// @brief Check if a line collides with an obstacle
            /// @param start The start of the line
            /// @param end The end of the line
            /// @return true if the line collides with an obstacle
            static bool isColliding(Eigen::Vector2i start, Eigen::Vector2i end);

            /// @brief Get the nearest obstacle to a position
            /// @param position The position to check
            /// @return The nearest obstacle
            /// @todo Consider lines
            static Eigen::Vector2i getNearestObstacle(Eigen::Vector2i position);

        private:
            static std::vector<Eigen::Vector2i> _obstaclesVector;
            static std::vector<std::array<Eigen::Vector2f, 2>> _obstaclesLines;
        };
    } // namespace physical
} // namespace finder