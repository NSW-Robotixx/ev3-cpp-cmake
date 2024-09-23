#ifndef __LINE_HPP__
#define __LINE_HPP__

#define _USE_MATH_DEFINES
#include <cmath>
#include "Vector2.hpp"

namespace finder::math {
    /// @brief Class that represents a line in 2D space
    /// @details A line is represented by two Vector2 points
    /// @warning May be replaced by Eigen3 library

    class Line {
        public:
            /// @brief Construct a new Line object
            /// @param p1 Point 1
            /// @param p2 Point 2
            Line(const Vector2& p1, const Vector2& p2);

            /// @brief Construct a new Line object
            /// @param other The other Line object
            Line(const Line& other);

            /// @brief Move operator
            /// @param other The other Line object
            Line(Line&& other) noexcept;

            ~Line() = default;

            /// @brief Assign a new Line object
            /// @param other The other Line object
            /// @return Line& The assigned Line object
            Line& operator=(const Line& other);

            /// @brief Move operator
            /// @param other The other Line object
            /// @return Line& The moved Line object
            Line& operator=(Line&& other) noexcept;

            /// @brief Get the first point of the line
            /// @return The first point of the line as a Vector2
            Vector2 getPoint1() const;

            /// @brief Get the second point of the line
            /// @return The second point of the line as a Vector2
            Vector2 getPoint2() const;

            /// @brief Set the first point of the line
            /// @param p1 The first point of the line
            void setPoint1(const Vector2& p1);

            /// @brief Set the second point of the line
            /// @param p2 The second point of the line
            void setPoint2(const Vector2& p2);

            /// @brief Get the length of the line
            /// @return The length of the line as a double
            double getLength() const;

            /// @brief Get the angle of the line
            /// @details The angle is calculated in radians. The angle is calculated from the x-axis
            /// @return The angle of the line as a double
            double getAngle() const;

            /// @brief Get the intersection point of two lines
            /// @details The intersection point is calculated using the line intersection formula
            /// @param other The other line
            /// @return The intersection point as a Vector2
            Vector2 getIntersection(const Line& other) const;

            /// @brief Check if two lines are intersecting
            /// @details The lines are intersecting if the intersection point is within the bounds of the lines.
            /// @param other The other line
            /// @return True if the lines are intersecting, false otherwise
            bool isIntersecting(const Line& other) const;

            /// @brief Check if two lines are equal
            /// @details p1 == p1 && p2 == p2
            /// @param other The other line
            /// @return True if the lines are equal, false otherwise            
            bool operator==(const Line& other) const;

            /// @brief Check if two lines are not equal
            /// @details p1 != p1 || p2 != p2
            /// @param other The other line
            /// @return True if the lines are not equal, false otherwise
            bool operator!=(const Line& other) const;

        private:
            Vector2 _p1;
            Vector2 _p2;
            
            /// @brief Check if three points are in a counter-clockwise order
            /// @details The points are in a counter-clockwise order if the slope of the line from a to b is less than the slope of the line from a to c
            /// @param a The first point
            /// @param b The second point
            /// @param c The third point
            /// @return True if the points are in a counter-clockwise order, false otherwise
            bool counterClockwise(const Vector2& a, const Vector2& b, const Vector2& c) const;
    };

} // namespace finder::math

#endif // __LINE_HPP__