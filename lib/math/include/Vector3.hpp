#pragma once

#include <math.h>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Vector2.hpp"

namespace finder
{
    namespace math
    {
        class Vector3
        {
            public:
                Vector3() = default;
                Vector3(const Vector3& other) = default;
                Vector3(Vector3&& other) = default;
                Vector3(const math::Vector2 xy, float z): x(xy.x), y(xy.y), z(z) {};
                Vector3(const std::string& str)
                {
                    std::string s = str;
                    s.erase(std::remove(s.begin(), s.end(), '('), s.end());
                    s.erase(std::remove(s.begin(), s.end(), ')'), s.end());
                    std::replace(s.begin(), s.end(), ',', ' ');
                    std::istringstream ss(s);
                    ss >> x >> y >> z;
                }
                Vector3& operator=(const Vector3& other) = default;
                Vector3& operator=(Vector3&& other) = default;
                ~Vector3() = default;

                Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

                float x = 0.0f;
                float y = 0.0f;
                float z = 0.0f;

                std::string toString() const
                {
                    return "Vector3(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
                }

                float magnitude() const
                {
                    return sqrt(x * x + y * y + z * z);
                }

                Vector3 normalize() const
                {
                    float mag = magnitude();
                    return Vector3(x / mag, y / mag, z / mag);
                }

                float dot(const Vector3& other) const
                {
                    return x * other.x + y * other.y + z * other.z;
                }

                Vector3 cross(const Vector3& other) const
                {
                    return Vector3(
                        y * other.z - z * other.y,
                        z * other.x - x * other.z,
                        x * other.y - y * other.x
                    );
                }

                Vector3 operator+(const Vector3& other) const
                {
                    return Vector3(x + other.x, y + other.y, z + other.z);
                }

                Vector3 operator-(const Vector3& other) const
                {
                    return Vector3(x - other.x, y - other.y, z - other.z);
                }

                Vector3 operator*(float scalar) const
                {
                    return Vector3(x * scalar, y * scalar, z * scalar);
                }

                Vector3 operator/(float scalar) const
                {
                    return Vector3(x / scalar, y / scalar, z / scalar);
                }

                Vector3& operator+=(const Vector3& other)
                {
                    x += other.x;
                    y += other.y;
                    z += other.z;
                    return *this;
                }

                Vector3& operator-=(const Vector3& other)
                {
                    x -= other.x;
                    y -= other.y;
                    z -= other.z;
                    return *this;
                }

                Vector3& operator*=(float scalar)
                {
                    x *= scalar;
                    y *= scalar;
                    z *= scalar;
                    return *this;
                }

                Vector3& operator/=(float scalar)
                {
                    x /= scalar;
                    y /= scalar;
                    z /= scalar;
                    return *this;
                }

                bool operator==(const Vector3& other) const
                {
                    return x == other.x && y == other.y && z == other.z;
                }

                bool operator!=(const Vector3& other) const
                {
                    return x != other.x || y != other.y || z != other.z;
                }

                bool operator<(const Vector3& other) const
                {
                    return x < other.x && y < other.y && z < other.z;
                }

                bool operator<=(const Vector3& other) const
                {
                    return x <= other.x && y <= other.y && z <= other.z;
                }

                bool operator>(const Vector3& other) const
                {
                    return x > other.x && y > other.y && z > other.z;
                }

                bool operator>=(const Vector3& other) const
                {
                    return x >= other.x && y >= other.y && z >= other.z;
                }

                friend std::ostream& operator<<(std::ostream& os, const Vector3& v)
                {
                    os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
                    return os;
                }

                static Vector3 lerp(const Vector3& a, const Vector3& b, float t)
                {
                    return a + (b - a) * t;
                }

                float distance(const Vector3& other) const
                {
                    return (*this - other).magnitude();
                } 
        };
    } // namespace math
} // namespace finder
