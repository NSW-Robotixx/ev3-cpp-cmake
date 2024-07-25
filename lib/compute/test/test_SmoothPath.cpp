#include <gtest/gtest.h>

#include <pf/SmoothPath.hpp>
#include <Vector2.hpp>
#include <vector>

TEST(SmoothPath, smoothPath) {
    using namespace finder::pathfind;
    using namespace finder::math;
    SmoothPath smooth_path;

    std::vector<Vector2> result = smooth_path.smoothPath(std::vector<Vector2>{
        Vector2{12, 15},
        Vector2{12, 14},
        Vector2{12, 13},
        Vector2{11, 12},
        Vector2{10, 11},
        Vector2{9, 10},
        Vector2{8, 9},
        Vector2{7, 8},
        Vector2{6, 7},
        Vector2{5, 6},
        Vector2{4, 5},
        Vector2{3, 4},
        Vector2{2, 3},
        Vector2{1, 2}
    });

    std::vector<Vector2> expected_result = {
        Vector2{12, 15},
        Vector2{1, 2}
    };

    ASSERT_EQ(result.size(), expected_result.size());
    for (size_t i = 0; i < result.size(); ++i)
    {
        EXPECT_EQ(result[i], expected_result[i]);
    }
}