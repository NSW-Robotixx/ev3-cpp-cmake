#ifndef FINDER_MATH_VECTOR_HPP
#define FINDER_MATH_VECTOR_HPP

#include <math.h>
#include <iostream>

namespace finder
{
    namespace math
    {
        /// @brief Class that represents a 2D vector with x and y coordinates
        /// @warning Planned to be replaced by Eigen3 library
        class Vector2
        {
            public:
                Vector2() = default;

                /// @brief Construct a new Vector2 object
                /// @param other The other Vector2 object
                Vector2(const Vector2& other) = default;

                /// @brief Assign a new Vector2 object
                /// @param other The other Vector2 object
                Vector2(Vector2&& other) = default;

                /// @brief Assign a new Vector2 object
                /// @param other The other Vector2 object
                /// @return Vector2& The assigned Vector2 object
                Vector2& operator=(const Vector2& other) = default;

                /// @brief Move operator
                /// @param other The other Vector2 object
                /// @return Vector2& The moved Vector2 object
                Vector2& operator=(Vector2&& other) = default;

                ~Vector2() = default;

                /// @brief Construct a new Vector2 object
                /// @param x X coordinate
                /// @param y Y coordinate
                Vector2(float x, float y) : x(x), y(y) {}

                /// @brief X coordinate
                float x = 0.0f;

                /// @brief Y coordinate
                float y = 0.0f;

                /// @brief Calculate the magnitude of the vector
                /// @details sqrt(x^2 + y^2) = length of the vector
                /// @return float The magnitude of the vector
                float magnitude() const
                {
                    return sqrt(x * x + y * y);
                }

                /// @brief Normalize the vector
                /// @details Divide the vector by its magnitude
                /// @return Vector2 The normalized vector
                Vector2 normalize() const
                {
                    float mag = magnitude();
                    return Vector2(x / mag, y / mag);
                }

                /// @brief Calculate the dot product of two vectors
                /// @details x1 * x2 + y1 * y2
                /// @param other The other vector
                /// @return float The dot product of the two vectors
                float dot(const Vector2& other) const
                {
                    return x * other.x + y * other.y;
                }

                /// @brief Calculate the distance between two vectors
                /// @details sqrt((x1 - x2)^2 + (y1 - y2)^2)
                /// @param other The other vector
                /// @return The distance between the two vectors as a double
                double distanceTo(const Vector2& other) const
                {
                    return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
                }
                
                /// @brief Add two vectors
                /// @details (x1 + x2, y1 + y2)
                /// @param other The other vector
                /// @return Vector2 The sum of the two vectors
                Vector2 operator+(const Vector2& other) const
                {
                    return Vector2(x + other.x, y + other.y);
                }

                /// @brief Subtract two vectors
                /// @details (x1 - x2, y1 - y2)
                /// @param other The other vector
                /// @return Vector2 The difference of the two vectors
                Vector2 operator-(const Vector2& other) const
                {
                    return Vector2(x - other.x, y - other.y);
                }

                /// @brief Multiply a vector by a scalar
                /// @details (x * scalar, y * scalar)
                /// @param scalar The scalar to multiply the vector by
                /// @return Vector2 The vector multiplied by the scalar
                Vector2 operator*(float scalar) const
                {
                    return Vector2(x * scalar, y * scalar);
                }

                /// @brief Divide a vector by a scalar
                /// @details (x / scalar, y / scalar)
                /// @param scalar The scalar to divide the vector by
                /// @return Vector2 The vector divided by the scalar
                Vector2 operator/(float scalar) const
                {
                    return Vector2(x / scalar, y / scalar);
                }

                /// @brief Add two vectors
                /// @details (x1 + x2, y1 + y2)
                /// @param other The other vector
                /// @return Vector2& The sum of the two vectors
                Vector2& operator+=(const Vector2& other)
                {
                    x += other.x;
                    y += other.y;
                    return *this;
                }

                /// @brief Subtract two vectors
                /// @details (x1 - x2, y1 - y2)
                /// @param other The other vector
                /// @return Vector2& The difference of the two vectors
                Vector2& operator-=(const Vector2& other)
                {
                    x -= other.x;
                    y -= other.y;
                    return *this;
                }

                /// @brief Multiply a vector by a scalar
                /// @details (x * scalar, y * scalar)
                /// @param scalar The scalar to multiply the vector by
                /// @return Vector2& The vector multiplied by the scalar
                Vector2& operator*=(float scalar)
                {
                    x *= scalar;
                    y *= scalar;
                    return *this;
                }

                /// @brief Divide a vector by a scalar
                /// @details (x / scalar, y / scalar)
                /// @param scalar The scalar to divide the vector by
                /// @return Vector2& The vector divided by the scalar
                Vector2& operator/=(float scalar)
                {
                    x /= scalar;
                    y /= scalar;
                    return *this;
                }
                
                /// @brief Compare two vectors for equality
                /// @details x1 == x2 && y1 == y2
                /// @param other The other vector
                /// @return bool True if the vectors are equal, false otherwise
                bool operator==(const Vector2& other) const
                {
                    return x == other.x && y == other.y;
                }

                /// @brief Compare two vectors for inequality
                /// @details x1 != x2 || y1 != y2
                /// @param other The other vector
                /// @return bool True if the vectors are not equal, false otherwise
                bool operator!=(const Vector2& other) const
                {
                    return !(*this == other);
                }

                /// @brief Compare two vectors for less than
                /// @details x1 < x2 && y1 < y2
                /// @param other The other vector
                /// @return bool True if the vector is less than the other, false otherwise
                bool operator<(const Vector2& other) const
                {
                    return x < other.x && y < other.y;
                }

                /// @brief Compare two vectors for less than or equal
                /// @details x1 <= x2 && y1 <= y2
                /// @param other The other vector
                /// @return bool True if the vector is less than or equal to the other, false otherwise
                bool operator<=(const Vector2& other) const
                {
                    return x <= other.x && y <= other.y;
                }

                /// @brief Compare two vectors for greater than
                /// @details x1 > x2 && y1 > y2
                /// @param other The other vector
                /// @return bool True if the vector is greater than the other, false otherwise
                bool operator>(const Vector2& other) const
                {
                    return x > other.x && y > other.y;
                }

                /// @brief Compare two vectors for greater than or equal
                /// @details x1 >= x2 && y1 >= y2
                /// @param other The other vector
                /// @return bool True if the vector is greater than or equal to the other, false otherwise
                bool operator>=(const Vector2& other) const
                {
                    return x >= other.x && y >= other.y;
                }

                /// @brief Linearly interpolate between two vectors
                /// @details a + (b - a) * t
                /// @param a The start vector
                /// @param b The end vector
                /// @param t The interpolation value
                /// @return Vector2 The interpolated vector
                static Vector2 lerp(const Vector2& a, const Vector2& b, float t)
                {
                    return a + (b - a) * t;
                }

                /// @brief Stream operator
                /// @details Outputs the vector as Vector2(x, y)
                /// @param os The output stream
                /// @param v The vector to output
                /// @return std::ostream& The output stream
                friend std::ostream& operator<<(std::ostream& os, const Vector2& v)
                {
                    os << "Vector2(" << v.x << ", " << v.y << ")";
                    return os;
                }
        };
    } // namespace math
    
} // namespace finder



#endif // FINDER_MATH_VECTOR_HPP