/*
    Copyright (c) 2015, Damian Barczynski <daan.net@wp.eu>
    Following tool is licensed under the terms and conditions of the ISC license.
    For more information visit https://opensource.org/licenses/ISC.
*/
#ifndef __ASTAR_HPP_8F637DB91972F6C878D41D63F7E7214F__
#define __ASTAR_HPP_8F637DB91972F6C878D41D63F7E7214F__

#include <vector>
#include <functional>
#include <Vector2.hpp>
#include "ObstacleManager.hpp"
#include "../../EV3_conf.hpp"


namespace finder::pathfind {
    /// @brief A* pathfinding algorithm
    class AStar {
    public:
        /// @brief uint type
        typedef unsigned int uint;

        /// @brief Heuristic function type
        typedef std::function<uint(math::Vector2, math::Vector2)> HeuristicFunction;

        /// @brief Coordinate list 
        typedef std::vector<math::Vector2> CoordinateList;

        /// @brief Node class
        struct Node
        {
            /// @brief G value of the node
            uint G;

            /// @brief H value of the node
            uint H;

            /// @brief Coordinates of the node
            math::Vector2 coordinates;

            /// @brief Parent node
            Node *parent;

            /// @brief Constructor
            /// @param coord_ Coordinates of the node
            /// @param parent_ Parent node
            Node(math::Vector2 coord_, Node *parent_ = nullptr);

            /// @brief Get the Score of the node
            uint getScore();
        };

        /// @brief Node set
        using NodeSet = std::vector<Node*>;

        /// @brief Path generator class
        class Generator
        {
            /// @brief Check if the line collides with obstacles
            /// @param coordinates_ Destination coordinates
            /// @param _origin Origin coordinates
            /// @return True if the line collides with obstacles
            bool detectCollision(math::Vector2 coordinates_, math::Vector2 _origin);

            /// @brief Get the Nodes on the list
            /// @param nodes_ Node set
            /// @param coordinates_ Coordinates to find
            /// @return Node
            Node* findNodeOnList(NodeSet& nodes_, math::Vector2 coordinates_);

            /// @brief Release the nodes
            /// @param nodes_ Node set
            void releaseNodes(NodeSet& nodes_);

        public:

            /// @brief Constructor
            Generator();

            /// @brief Set the World size
            /// @param worldSize_ World size
            void setWorldSize(math::Vector2 worldSize_);

            /// @brief Set diagonal movement on or off
            /// @param enable_ Enable diagonal movement
            void setDiagonalMovement(bool enable_);

            /// @brief Set heuristic function
            /// @param heuristic_ Heuristic function
            void setHeuristic(HeuristicFunction heuristic_);

            /// @brief Find the path
            /// @param source_ Source coordinates
            /// @param target_ Target coordinates
            /// @return Coordinate list
            CoordinateList findPath(math::Vector2 source_, math::Vector2 target_);

            /// @brief Add a collision
            /// @param coordinates_ Coordinates of the collision
            void addCollision(math::Vector2 coordinates_);

            /// @brief Remove a collision
            /// @param coordinates_ Coordinates of the collision
            void removeCollision(math::Vector2 coordinates_);

            /// @brief Clear the collisions
            void clearCollisions();

            /// @brief Obstacle manager
            ObstacleManager om = ObstacleManager{};

        private:
            HeuristicFunction heuristic;
            CoordinateList direction, walls;
            math::Vector2 worldSize;
            uint directions;
        };
    private:
        class Heuristic
        {
            static math::Vector2 getDelta(math::Vector2 source_, math::Vector2 target_);

        public:
            static uint manhattan(math::Vector2 source_, math::Vector2 target_);
            static uint euclidean(math::Vector2 source_, math::Vector2 target_);
            static uint octagonal(math::Vector2 source_, math::Vector2 target_);
        };
    };
};

#endif // __ASTAR_HPP_8F637DB91972F6C878D41D63F7E7214F__