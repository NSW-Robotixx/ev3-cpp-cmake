#include <gtest/gtest.h>

#include <pf/AStar.hpp>
#include <pf/SmoothPath.hpp>
#include <EV3_ObstacleManager.hpp>
#include <Vector2.hpp>
#include <vector>

TEST(AStar, findPath) {
    finder::pathfind::AStar::Generator astar;
    std::vector<finder::math::Vector2> path = astar.findPath(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));

    ASSERT_EQ(path.size(), 2);
    ASSERT_EQ(path[0], finder::math::Vector2(1, 1));
    ASSERT_EQ(path[1], finder::math::Vector2(0, 0));
}

TEST(AStar, findPathWithObstacle) {
    finder::physical::ObstacleManager obstacleManager;
    obstacleManager.addObstacleLine(Eigen::Vector2f(0.5, 0.5), Eigen::Vector2f(1.5, 1.5));

    finder::pathfind::AStar::Generator astar;
    std::vector<finder::math::Vector2> path = astar.findPath(finder::math::Vector2(0, 2), finder::math::Vector2(2, 1));

    ASSERT_EQ(path.size(), 4);
    ASSERT_EQ(path[0], finder::math::Vector2(2, 1));
    ASSERT_EQ(path[1], finder::math::Vector2(2, 2));
    ASSERT_EQ(path[2], finder::math::Vector2(1, 2));
    ASSERT_EQ(path[3], finder::math::Vector2(0, 2));
}