#include <gtest/gtest.h>

#include <math/Vector2.hpp>

TEST(Vector2, DefaultConstructor)
{
    finder::math::Vector2 v;
    EXPECT_EQ(v.x, 0.0f);
    EXPECT_EQ(v.y, 0.0f);
}

TEST(Vector2, Constructor)
{
    finder::math::Vector2 v(1.0f, 2.0f);
    EXPECT_EQ(v.x, 1.0f);
    EXPECT_EQ(v.y, 2.0f);
}

TEST(Vector2, AssignOperator)
{
    finder::math::Vector2 v1(1.0f, 2.0f);
    finder::math::Vector2 v2 = v1;
    EXPECT_EQ(v2.x, 1.0f);
    EXPECT_EQ(v2.y, 2.0f);
}

TEST(Vector2, Magnitude)
{
    finder::math::Vector2 v(1.0f, 2.0f);
    EXPECT_FLOAT_EQ(v.magnitude(), 2.23606797749979f);
}

TEST(Vector2, Normalize)
{
    finder::math::Vector2 v(1.0f, 2.0f);
    finder::math::Vector2 n = v.normalize();
    EXPECT_FLOAT_EQ(n.x, 0.4472135954999579f);
    EXPECT_FLOAT_EQ(n.y, 0.8944271909999159f);
}

TEST(Vector2, Dot)
{
    finder::math::Vector2 v1(1.0f, 2.0f);
    finder::math::Vector2 v2(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v1.dot(v2), 11.0f);
}

TEST(Vector2, Addition)
{
    finder::math::Vector2 v1(1.0f, 2.0f);
    finder::math::Vector2 v2(3.0f, 4.0f);
    finder::math::Vector2 v3 = v1 + v2;
    EXPECT_FLOAT_EQ(v3.x, 4.0f);
    EXPECT_FLOAT_EQ(v3.y, 6.0f);
}

TEST(Vector2, Subtraction)
{
    finder::math::Vector2 v1(1.0f, 2.0f);
    finder::math::Vector2 v2(3.0f, 4.0f);
    finder::math::Vector2 v3 = v1 - v2;
    EXPECT_FLOAT_EQ(v3.x, -2.0f);
    EXPECT_FLOAT_EQ(v3.y, -2.0f);
}

TEST(Vector2, Multiplication)
{
    finder::math::Vector2 v(1.0f, 2.0f);
    finder::math::Vector2 v2 = v * 2.0f;
    EXPECT_FLOAT_EQ(v2.x, 2.0f);
    EXPECT_FLOAT_EQ(v2.y, 4.0f);
}

TEST(Vector2, Division)
{
    finder::math::Vector2 v(1.0f, 2.0f);
    finder::math::Vector2 v2 = v / 2.0f;
    EXPECT_FLOAT_EQ(v2.x, 0.5f);
    EXPECT_FLOAT_EQ(v2.y, 1.0f);
}

TEST(Vector2, AdditionAssign)
{
    finder::math::Vector2 v1(1.0f, 2.0f);
    finder::math::Vector2 v2(3.0f, 4.0f);
    v1 += v2;
    EXPECT_FLOAT_EQ(v1.x, 4.0f);
    EXPECT_FLOAT_EQ(v1.y, 6.0f);
}

TEST(Vector2, SubtractionAssign)
{
    finder::math::Vector2 v1(1.0f, 2.0f);
    finder::math::Vector2 v2(3.0f, 4.0f);
    v1 -= v2;
    EXPECT_FLOAT_EQ(v1.x, -2.0f);
    EXPECT_FLOAT_EQ(v1.y, -2.0f);
}

TEST(Vector2, MultiplicationAssign)
{
    finder::math::Vector2 v(1.0f, 2.0f);
    v *= 2.0f;
    EXPECT_FLOAT_EQ(v.x, 2.0f);
    EXPECT_FLOAT_EQ(v.y, 4.0f);
}

TEST(Vector2, DivisionAssign)
{
    finder::math::Vector2 v(1.0f, 2.0f);
    v /= 2.0f;
    EXPECT_FLOAT_EQ(v.x, 0.5f);
    EXPECT_FLOAT_EQ(v.y, 1.0f);
}

TEST(Vector2, Equality)
{
    finder::math::Vector2 v1(1.0f, 2.0f);
    finder::math::Vector2 v2(1.0f, 2.0f);
    EXPECT_TRUE(v1 == v2);
}

TEST(Vector2, Inequality)
{
    finder::math::Vector2 v1(1.0f, 2.0f);
    finder::math::Vector2 v2(3.0f, 4.0f);
    EXPECT_TRUE(v1 != v2);
}

TEST(Vector2, LessThan)
{
    finder::math::Vector2 v1(1.0f, 2.0f);
    finder::math::Vector2 v2(3.0f, 4.0f);
    EXPECT_TRUE(v1 < v2);
}

TEST(Vector2, GreaterThan)
{
    finder::math::Vector2 v1(3.0f, 4.0f);
    finder::math::Vector2 v2(1.0f, 2.0f);
    EXPECT_TRUE(v1 > v2);
}

TEST(Vector2, StreamOutput)
{
    finder::math::Vector2 v(1.0f, 2.0f);
    std::stringstream ss;
    ss << v;
    EXPECT_EQ(ss.str(), "Vector2(1, 2)");
}

TEST(Vector2, LessThanOrEqual)
{
    finder::math::Vector2 v1(1.0f, 2.0f);
    finder::math::Vector2 v2(3.0f, 4.0f);
    EXPECT_TRUE(v1 <= v2);
}

TEST(Vector2, GreaterThanOrEqual)
{
    finder::math::Vector2 v1(3.0f, 4.0f);
    finder::math::Vector2 v2(1.0f, 2.0f);
    EXPECT_TRUE(v1 >= v2);
}

TEST(Vector2, Lerp)
{
    finder::math::Vector2 v1(1.0f, 2.0f);
    finder::math::Vector2 v2(3.0f, 4.0f);
    finder::math::Vector2 v3 = finder::math::Vector2::lerp(v1, v2, 0.5f);
    EXPECT_FLOAT_EQ(v3.x, 2.0f);
    EXPECT_FLOAT_EQ(v3.y, 3.0f);
}