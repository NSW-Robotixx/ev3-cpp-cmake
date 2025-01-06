#pragma once

#include <math.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <boost/leaf/result.hpp>
#include "Vector2.hpp"

namespace finder
{
    namespace math
    {
        /// @brief Class that represents a 3D vector with x, y and z coordinates
        /// @warning Planned to be replaced by Eigen3 library
        class Vector3
        {
            public:
                Vector3() = default;

                /// @brief Construct a new Vector3 object
                /// @param other The other Vector3 object
                Vector3(const Vector3& other) = default;

                /// @brief Move operator
                /// @param other The other Vector3 object
                Vector3(Vector3&& other) = default;

                /// @brief Assign a new Vector3 object from Vector2 and z
                /// @param xy The Vector2 object
                /// @param z The z coordinate to add
                Vector3(const math::Vector2 xy, float z): x(xy.x), y(xy.y), z(z) {};

                /// @brief Assign a new Vector3 object from a string
                /// @param str The string to parse
                Vector3(const std::string& str)
                {
                    std::string s = str;
                    s.erase(std::remove(s.begin(), s.end(), '('), s.end());
                    s.erase(std::remove(s.begin(), s.end(), ')'), s.end());
                    std::replace(s.begin(), s.end(), ',', ' ');
                    std::istringstream ss(s);
                    ss >> x >> y >> z;
                }

                /// @brief Assign a new Vector3 object
                /// @param other The other Vector3 object
                /// @return Vector3& The assigned Vector3 object
                Vector3& operator=(const Vector3& other) = default;

                /// @brief Move operator
                /// @param other The other Vector3 object
                /// @return Vector3& The moved Vector3 object
                Vector3& operator=(Vector3&& other) = default;

                ~Vector3() = default;

                /// @brief Construct a new Vector3 object
                /// @param x X coordinate
                /// @param y Y coordinate
                /// @param z Z coordinate
                Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

                /// @brief X coordinate
                float x = 0.0f;

                /// @brief Y coordinate
                float y = 0.0f;

                /// @brief Z coordinate
                float z = 0.0f;

                /// @brief Convert the vector to a string
                /// @details format: Vector3(x, y, z)
                /// @return std::string The string representation of the vector
                std::string toString() const
                {
                    return "Vector3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
                }

                /// @brief Calculate the magnitude of the vector
                /// @details sqrt(x^2 + y^2 + z^2) = length of the vector
                /// @return float The magnitude of the vector
                float magnitude() const
                {
                    return sqrt(x * x + y * y + z * z);
                }

                /// @brief Normalize the vector
                /// @details Divide the vector by its magnitude
                /// @return Vector3 The normalized vector
                Vector3 normalize() const
                {
                    float mag = magnitude();
                    return Vector3(x / mag, y / mag, z / mag);
                }

                /// @brief Calculate the dot product of two vectors
                /// @details x1 * x2 + y1 * y2 + z1 * z2
                /// @param other The other vector
                /// @return float The dot product of the two vectors
                float dot(const Vector3& other) const
                {
                    return x * other.x + y * other.y + z * other.z;
                }

                /// @brief Calculate the cross product of two vectors
                /// @details (y1 * z2 - z1 * y2, z1 * x2 - x1 * z2, x1 * y2 - y1 * x2)
                /// @param other The other vector
                /// @return Vector3 The cross product of the two vectors
                Vector3 cross(const Vector3& other) const
                {
                    return Vector3(
                        y * other.z - z * other.y,
                        z * other.x - x * other.z,
                        x * other.y - y * other.x
                    );
                }

                /// @brief Add two vectors
                /// @details (x1 + x2, y1 + y2, z1 + z2)
                /// @param other The other vector
                /// @return Vector3 The sum of the two vectors
                Vector3 operator+(const Vector3& other) const
                {
                    return Vector3(x + other.x, y + other.y, z + other.z);
                }

                /// @brief Subtract two vectors
                /// @details (x1 - x2, y1 - y2, z1 - z2)
                /// @param other The other vector
                /// @return Vector3 The difference of the two vectors
                Vector3 operator-(const Vector3& other) const
                {
                    return Vector3(x - other.x, y - other.y, z - other.z);
                }

                /// @brief Multiply a vector by a scalar
                /// @details (x * scalar, y * scalar, z * scalar)
                /// @param scalar The scalar to multiply the vector by
                /// @return Vector3 The vector multiplied by the scalar
                Vector3 operator*(float scalar) const
                {
                    return Vector3(x * scalar, y * scalar, z * scalar);
                }

                /// @brief Divide a vector by a scalar
                /// @details (x / scalar, y / scalar, z / scalar)
                /// @param scalar The scalar to divide the vector by
                /// @return Vector3 The vector divided by the scalar
                Vector3 operator/(float scalar) const
                {
                    return Vector3(x / scalar, y / scalar, z / scalar);
                }

                /// @brief Add two vectors
                /// @details (x1 + x2, y1 + y2, z1 + z2)
                /// @param other The other vector
                /// @return Vector3& The sum of the two vectors
                Vector3& operator+=(const Vector3& other)
                {
                    x += other.x;
                    y += other.y;
                    z += other.z;
                    return *this;
                }

                /// @brief Subtract two vectors
                /// @details (x1 - x2, y1 - y2, z1 - z2)
                /// @param other The other vector
                /// @return Vector3& The difference of the two vectors
                Vector3& operator-=(const Vector3& other)
                {
                    x -= other.x;
                    y -= other.y;
                    z -= other.z;
                    return *this;
                }

                /// @brief Multiply a vector by a scalar
                /// @details (x * scalar, y * scalar, z * scalar)
                /// @param scalar The scalar to multiply the vector by
                /// @return Vector3& The vector multiplied by the scalar
                Vector3& operator*=(float scalar)
                {
                    x *= scalar;
                    y *= scalar;
                    z *= scalar;
                    return *this;
                }

                /// @brief Divide a vector by a scalar
                /// @details (x / scalar, y / scalar, z / scalar)
                /// @param scalar The scalar to divide the vector by
                /// @return Vector3& The vector divided by the scalar
                Vector3& operator/=(float scalar)
                {
                    x /= scalar;
                    y /= scalar;
                    z /= scalar;
                    return *this;
                }

                /// @brief Compare two vectors
                /// @details x1 == x2 && y1 == y2 && z1 == z2
                /// @param other The other vector
                /// @return bool True if the vectors are equal, false otherwise
                bool operator==(const Vector3& other) const
                {
                    return x == other.x && y == other.y && z == other.z;
                }

                /// @brief Compare two vectors
                /// @details x1 != x2 || y1 != y2 || z1 != z2
                /// @param other The other vector
                /// @return bool True if the vectors are not equal, false otherwise
                bool operator!=(const Vector3& other) const
                {
                    return x != other.x || y != other.y || z != other.z;
                }

                /// @brief Compare two vectors
                /// @details x1 < x2 && y1 < y2 && z1 < z2
                /// @param other The other vector
                /// @return bool True if the vector is less than the other, false otherwise
                bool operator<(const Vector3& other) const
                {
                    return x < other.x && y < other.y && z < other.z;
                }

                /// @brief Compare two vectors
                /// @details x1 <= x2 && y1 <= y2 && z1 <= z2
                /// @param other The other vector
                /// @return bool True if the vector is less than or equal to the other, false otherwise
                bool operator<=(const Vector3& other) const
                {
                    return x <= other.x && y <= other.y && z <= other.z;
                }

                /// @brief Compare two vectors
                /// @details x1 > x2 && y1 > y2 && z1 > z2
                /// @param other The other vector
                /// @return bool True if the vector is greater than the other, false otherwise
                bool operator>(const Vector3& other) const
                {
                    return x > other.x && y > other.y && z > other.z;
                }

                /// @brief Compare two vectors
                /// @details x1 >= x2 && y1 >= y2 && z1 >= z2
                /// @param other The other vector
                /// @return bool True if the vector is greater than or equal to the other, false otherwise
                bool operator>=(const Vector3& other) const
                {
                    return x >= other.x && y >= other.y && z >= other.z;
                }

                /// @brief Convert the vector to a string
                /// @details format: Vector3(x, y, z)
                /// @param os The output stream
                /// @param v The vector to output
                /// @return std::ostream& The output stream
                friend std::ostream& operator<<(std::ostream& os, const Vector3& v)
                {
                    os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
                    return os;
                }

                /// @brief Linear interpolation between two vectors
                /// @details a + (b - a) * t
                /// @param a The start vector
                /// @param b The end vector
                /// @param t The interpolation value
                /// @return Vector3 The interpolated vector
                static Vector3 lerp(const Vector3& a, const Vector3& b, float t)
                {
                    return a + (b - a) * t;
                }

                /// @brief Calculate the distance between two vectors
                /// @details sqrt((x1 - x2)^2 + (y1 - y2)^2 + (z1 - z2)^2)
                /// @param other The other vector
                /// @return float The distance between the two vectors
                float distance(const Vector3& other) const
                {
                    return (*this - other).magnitude();
                } 
        };
    } // namespace math
} // namespace finder
