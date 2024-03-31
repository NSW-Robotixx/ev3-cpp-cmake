#ifndef FINDER_MATH_VECTOR_HPP
#define FINDER_MATH_VECTOR_HPP

#include <math.h>
#include <iostream>

namespace finder
{
    namespace math
    {
        class Vector2
        {
            public:
                Vector2() = default;
                Vector2(const Vector2& other) = default;
                Vector2(Vector2&& other) = default;
                Vector2& operator=(const Vector2& other) = default;
                Vector2& operator=(Vector2&& other) = default;
                ~Vector2() = default;

                Vector2(float x, float y) : x(x), y(y) {}

                float x = 0.0f;
                float y = 0.0f;

                float magnitude() const
                {
                    return sqrt(x * x + y * y);
                }

                Vector2 normalize() const
                {
                    float mag = magnitude();
                    return Vector2(x / mag, y / mag);
                }

                float dot(const Vector2& other) const
                {
                    return x * other.x + y * other.y;
                }

                Vector2 operator+(const Vector2& other) const
                {
                    return Vector2(x + other.x, y + other.y);
                }

                Vector2 operator-(const Vector2& other) const
                {
                    return Vector2(x - other.x, y - other.y);
                }

                Vector2 operator*(float scalar) const
                {
                    return Vector2(x * scalar, y * scalar);
                }

                Vector2 operator/(float scalar) const
                {
                    return Vector2(x / scalar, y / scalar);
                }

                Vector2& operator+=(const Vector2& other)
                {
                    x += other.x;
                    y += other.y;
                    return *this;
                }

                Vector2& operator-=(const Vector2& other)
                {
                    x -= other.x;
                    y -= other.y;
                    return *this;
                }

                Vector2& operator*=(float scalar)
                {
                    x *= scalar;
                    y *= scalar;
                    return *this;
                }

                Vector2& operator/=(float scalar)
                {
                    x /= scalar;
                    y /= scalar;
                    return *this;
                }

                bool operator==(const Vector2& other) const
                {
                    return x == other.x && y == other.y;
                }

                bool operator!=(const Vector2& other) const
                {
                    return !(*this == other);
                }

                bool operator<(const Vector2& other) const
                {
                    return x < other.x && y < other.y;
                }

                bool operator<=(const Vector2& other) const
                {
                    return x <= other.x && y <= other.y;
                }

                bool operator>(const Vector2& other) const
                {
                    return x > other.x && y > other.y;
                }

                bool operator>=(const Vector2& other) const
                {
                    return x >= other.x && y >= other.y;
                }

                static Vector2 lerp(const Vector2& a, const Vector2& b, float t)
                {
                    return a + (b - a) * t;
                }

                friend std::ostream& operator<<(std::ostream& os, const Vector2& v)
                {
                    os << "Vector2(" << v.x << ", " << v.y << ")";
                    return os;
                }
        };
    } // namespace math
    
} // namespace finder



#endif // FINDER_MATH_VECTOR_HPP