#include <gtest/gtest.h>
#include <Line.hpp>

TEST(Line, constructor) {
    finder::math::Line line(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));

    EXPECT_EQ(line.getPoint1(), finder::math::Vector2(0, 0));
    EXPECT_EQ(line.getPoint2(), finder::math::Vector2(1, 1));
}

TEST(Line, copyConstructor) {
    finder::math::Line line(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));
    finder::math::Line line2(line);

    EXPECT_EQ(line2.getPoint1(), finder::math::Vector2(0, 0));
    EXPECT_EQ(line2.getPoint2(), finder::math::Vector2(1, 1));
}

TEST(Line, moveConstructor) {
    finder::math::Line line(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));
    finder::math::Line line2(std::move(line));

    EXPECT_EQ(line2.getPoint1(), finder::math::Vector2(0, 0));
    EXPECT_EQ(line2.getPoint2(), finder::math::Vector2(1, 1));
}

TEST(Line, copyAssignment) {
    finder::math::Line line(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));
    finder::math::Line line2(finder::math::Vector2(2, 2), finder::math::Vector2(3, 3));
    line2 = line;

    EXPECT_EQ(line2.getPoint1(), finder::math::Vector2(0, 0));
    EXPECT_EQ(line2.getPoint2(), finder::math::Vector2(1, 1));
}

TEST(Line, moveAssignment) {
    finder::math::Line line(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));
    finder::math::Line line2(finder::math::Vector2(2, 2), finder::math::Vector2(3, 3));
    line2 = std::move(line);

    EXPECT_EQ(line2.getPoint1(), finder::math::Vector2(0, 0));
    EXPECT_EQ(line2.getPoint2(), finder::math::Vector2(1, 1));
}

TEST(Line, setPoint1) {
    finder::math::Line line(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));
    line.setPoint1(finder::math::Vector2(2, 2));

    EXPECT_EQ(line.getPoint1(), finder::math::Vector2(2, 2));
}

TEST(Line, setPoint2) {
    finder::math::Line line(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));
    line.setPoint2(finder::math::Vector2(2, 2));

    EXPECT_EQ(line.getPoint2(), finder::math::Vector2(2, 2));
}

TEST(Line, getLength) {
    finder::math::Line line(finder::math::Vector2(0, 0), finder::math::Vector2(3, 4));

    EXPECT_EQ(line.getLength(), 5);
}

TEST(Line, getAngle) {
    finder::math::Line line(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));

    EXPECT_EQ((int)(line.getAngle()), 45.0);
}

TEST(Line, getAngle2) {
    finder::math::Line line(finder::math::Vector2(0, 0), finder::math::Vector2(1, 0));

    EXPECT_EQ(static_cast<int>(line.getAngle()), 0);
}

TEST(Line, getAngle3) {
    finder::math::Line line(finder::math::Vector2(0, 0), finder::math::Vector2(0, 1));

    EXPECT_EQ((int)(line.getAngle()), 90);
}

TEST(Line, getAngle4) {
    finder::math::Line line(finder::math::Vector2(0, 0), finder::math::Vector2(-1, 0));

    EXPECT_EQ((int)(line.getAngle()), 180.0);
}

TEST(Line, getAngle5) {
    finder::math::Line line(finder::math::Vector2(0, 0), finder::math::Vector2(0, -1));

    EXPECT_EQ((int)(line.getAngle()), -90.0);
}

TEST(Line, getIntersection) {
    finder::math::Line line1(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));
    finder::math::Line line2(finder::math::Vector2(0, 1), finder::math::Vector2(1, 0));

    EXPECT_EQ(line1.getIntersection(line2), finder::math::Vector2(0.5, 0.5));
}   

TEST(Line, isIntersecting) {
    finder::math::Line line1(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));
    finder::math::Line line2(finder::math::Vector2(0, 1), finder::math::Vector2(1, 0));

    ASSERT_TRUE(line1.isIntersecting(line2));
}

TEST(Line, isIntersecting2) {
    finder::math::Line line1(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));
    finder::math::Line line2(finder::math::Vector2(0, 1), finder::math::Vector2(1, 2));

    ASSERT_FALSE(line1.isIntersecting(line2));
}

TEST(Line, isIntersecting3) {
    finder::math::Line line1(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));
    finder::math::Line line2(finder::math::Vector2(0, 1), finder::math::Vector2(1, 1));

    ASSERT_FALSE(line1.isIntersecting(line2));
}

TEST(Line, isIntersecting4) {
    finder::math::Line line1(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));
    finder::math::Line line2(finder::math::Vector2(0, 1), finder::math::Vector2(0, 2));

    ASSERT_FALSE(line1.isIntersecting(line2));
}

TEST(Line, isIntersecting5) {
    finder::math::Line line1(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));
    finder::math::Line line2(finder::math::Vector2(1, 1), finder::math::Vector2(2, 2));

    ASSERT_FALSE(line1.isIntersecting(line2));
}

TEST(Line, operatorEqual) {
    finder::math::Line line1(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));
    finder::math::Line line2(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));

    ASSERT_TRUE(line1 == line2);
}

TEST(Line, operatorNotEqual) {
    finder::math::Line line1(finder::math::Vector2(0, 0), finder::math::Vector2(1, 1));
    finder::math::Line line2(finder::math::Vector2(0, 0), finder::math::Vector2(1, 2));

    ASSERT_TRUE(line1 != line2);
}