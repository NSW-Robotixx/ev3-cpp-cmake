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


namespace finder::pathfind {
    class AStar {
    public:
        using uint = unsigned int;
        using HeuristicFunction = std::function<uint(math::Vector2, math::Vector2)>;

        using CoordinateList = std::vector<math::Vector2>;

        struct Node
        {
            uint G, H;
            math::Vector2 coordinates;
            Node *parent;

            Node(math::Vector2 coord_, Node *parent_ = nullptr);
            uint getScore();
        };

        using NodeSet = std::vector<Node*>;
        class Generator
        {
            bool detectCollision(math::Vector2 coordinates_, math::Vector2 _origin);
            Node* findNodeOnList(NodeSet& nodes_, math::Vector2 coordinates_);
            void releaseNodes(NodeSet& nodes_);

        public:
            Generator();
            void setWorldSize(math::Vector2 worldSize_);
            void setDiagonalMovement(bool enable_);
            void setHeuristic(HeuristicFunction heuristic_);
            CoordinateList findPath(math::Vector2 source_, math::Vector2 target_);
            void addCollision(math::Vector2 coordinates_);
            void removeCollision(math::Vector2 coordinates_);
            void clearCollisions();
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