#include <gtest/gtest.h>

#include "math/Vector3.hpp"

TEST(Vector3, DefaultConstructor)
{
    finder::math::Vector3 v;
    EXPECT_EQ(v.x, 0.0f);
    EXPECT_EQ(v.y, 0.0f);
    EXPECT_EQ(v.z, 0.0f);
}

TEST(Vector3, Constructor)
{
    finder::math::Vector3 v(1.0f, 2.0f, 3.0f);
    EXPECT_EQ(v.x, 1.0f);
    EXPECT_EQ(v.y, 2.0f);
    EXPECT_EQ(v.z, 3.0f);
}

TEST(Vector3, Magnitude)
{
    finder::math::Vector3 v(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(v.magnitude(), 3.7416573867739413f);
}

TEST(Vector3, Normalize)
{
    finder::math::Vector3 v(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 n = v.normalize();
    EXPECT_FLOAT_EQ(n.x, 0.2672612419124244f);
    EXPECT_FLOAT_EQ(n.y, 0.5345224838248488f);
    EXPECT_FLOAT_EQ(n.z, 0.8017837257372732f);
}

TEST(Vector3, Dot)
{
    finder::math::Vector3 v1(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2(4.0f, 5.0f, 6.0f);
    EXPECT_FLOAT_EQ(v1.dot(v2), 32.0f);
}

TEST(Vector3, Cross)
{
    finder::math::Vector3 v1(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2(4.0f, 5.0f, 6.0f);
    finder::math::Vector3 c = v1.cross(v2);
    EXPECT_FLOAT_EQ(c.x, -3.0f);
    EXPECT_FLOAT_EQ(c.y, 6.0f);
    EXPECT_FLOAT_EQ(c.z, -3.0f);
}

TEST(Vector3, Addition)
{
    finder::math::Vector3 v1(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2(4.0f, 5.0f, 6.0f);
    finder::math::Vector3 v3 = v1 + v2;
    EXPECT_FLOAT_EQ(v3.x, 5.0f);
    EXPECT_FLOAT_EQ(v3.y, 7.0f);
    EXPECT_FLOAT_EQ(v3.z, 9.0f);
}

TEST(Vector3, Subtraction)
{
    finder::math::Vector3 v1(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2(4.0f, 5.0f, 6.0f);
    finder::math::Vector3 v3 = v1 - v2;
    EXPECT_FLOAT_EQ(v3.x, -3.0f);
    EXPECT_FLOAT_EQ(v3.y, -3.0f);
    EXPECT_FLOAT_EQ(v3.z, -3.0f);
}

TEST(Vector3, Multiplication)
{
    finder::math::Vector3 v(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2 = v * 2.0f;
    EXPECT_FLOAT_EQ(v2.x, 2.0f);
    EXPECT_FLOAT_EQ(v2.y, 4.0f);
    EXPECT_FLOAT_EQ(v2.z, 6.0f);
}

TEST(Vector3, Division)
{
    finder::math::Vector3 v(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2 = v / 2.0f;
    EXPECT_FLOAT_EQ(v2.x, 0.5f);
    EXPECT_FLOAT_EQ(v2.y, 1.0f);
    EXPECT_FLOAT_EQ(v2.z, 1.5f);
}

TEST(Vector3, CompoundAddition)
{
    finder::math::Vector3 v1(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2(4.0f, 5.0f, 6.0f);
    v1 += v2;
    EXPECT_FLOAT_EQ(v1.x, 5.0f);
    EXPECT_FLOAT_EQ(v1.y, 7.0f);
    EXPECT_FLOAT_EQ(v1.z, 9.0f);
}

TEST(Vector3, CompoundSubtraction)
{
    finder::math::Vector3 v1(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2(4.0f, 5.0f, 6.0f);
    v1 -= v2;
    EXPECT_FLOAT_EQ(v1.x, -3.0f);
    EXPECT_FLOAT_EQ(v1.y, -3.0f);
    EXPECT_FLOAT_EQ(v1.z, -3.0f);
}

TEST(Vector3, CompoundMultiplication)
{
    finder::math::Vector3 v(1.0f, 2.0f, 3.0f);
    v *= 2.0f;
    EXPECT_FLOAT_EQ(v.x, 2.0f);
    EXPECT_FLOAT_EQ(v.y, 4.0f);
    EXPECT_FLOAT_EQ(v.z, 6.0f);
}

TEST(Vector3, CompoundDivision)
{
    finder::math::Vector3 v(1.0f, 2.0f, 3.0f);
    v /= 2.0f;
    EXPECT_FLOAT_EQ(v.x, 0.5f);
    EXPECT_FLOAT_EQ(v.y, 1.0f);
    EXPECT_FLOAT_EQ(v.z, 1.5f);
}

TEST(Vector3, Equality)
{
    finder::math::Vector3 v1(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2(1.0f, 2.0f, 3.0f);
    EXPECT_TRUE(v1 == v2);
}

TEST(Vector3, Inequality)
{
    finder::math::Vector3 v1(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2(4.0f, 5.0f, 6.0f);
    EXPECT_TRUE(v1 != v2);
}

TEST(Vector3, StreamOutput)
{
    finder::math::Vector3 v(1.0f, 2.0f, 3.0f);
    std::stringstream ss;
    ss << v;
    EXPECT_EQ(ss.str(), "Vector3(1, 2, 3)");
}

TEST(Vector3, LessThan)
{
    finder::math::Vector3 v1(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2(4.0f, 5.0f, 6.0f);
    EXPECT_TRUE(v1 < v2);
}

TEST(Vector3, LessThanOrEqual)
{
    finder::math::Vector3 v1(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2(4.0f, 5.0f, 6.0f);
    EXPECT_TRUE(v1 <= v2);
}

TEST(Vector3, GreaterThan)
{
    finder::math::Vector3 v1(4.0f, 5.0f, 6.0f);
    finder::math::Vector3 v2(1.0f, 2.0f, 3.0f);
    EXPECT_TRUE(v1 > v2);
}

TEST(Vector3, GreaterThanOrEqual)
{
    finder::math::Vector3 v1(4.0f, 5.0f, 6.0f);
    finder::math::Vector3 v2(1.0f, 2.0f, 3.0f);
    EXPECT_TRUE(v1 >= v2);
}

TEST(Vector3, Lerp)
{
    finder::math::Vector3 v1(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2(4.0f, 5.0f, 6.0f);
    finder::math::Vector3 v3 = finder::math::Vector3::lerp(v1, v2, 0.5f);
    EXPECT_FLOAT_EQ(v3.x, 2.5f);
    EXPECT_FLOAT_EQ(v3.y, 3.5f);
    EXPECT_FLOAT_EQ(v3.z, 4.5f);
}

TEST(Vector3, Slerp)
{
    finder::math::Vector3 v1(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2(4.0f, 5.0f, 6.0f);
    finder::math::Vector3 v3 = finder::math::Vector3::slerp(v1, v2, 0.5f);
    EXPECT_FLOAT_EQ(v3.x, 2.5f);
    EXPECT_FLOAT_EQ(v3.y, 3.5f);
    EXPECT_FLOAT_EQ(v3.z, 4.5f);
}

TEST(Vector3, Nlerp)
{
    finder::math::Vector3 v1(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2(4.0f, 5.0f, 6.0f);
    finder::math::Vector3 v3 = finder::math::Vector3::nlerp(v1, v2, 0.5f);
    EXPECT_FLOAT_EQ(v3.x, 0.26726123690605164f);
    EXPECT_FLOAT_EQ(v3.y, 0.5345224738121033f);
    EXPECT_FLOAT_EQ(v3.z, 0.8017836809158325f);
}

TEST(Vector3, Distance)
{
    finder::math::Vector3 v1(1.0f, 2.0f, 3.0f);
    finder::math::Vector3 v2(4.0f, 5.0f, 6.0f);
    EXPECT_FLOAT_EQ(v1.distance(v2), 5.196152210235596f);
}

