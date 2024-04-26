#ifndef __LINE_HPP__
#define __LINE_HPP__

#include "Vector2.hpp"

namespace finder::math {

    class Line {
        public:
            Line(const Vector2& p1, const Vector2& p2);
            Line(const Line& other);
            Line(Line&& other) noexcept;
            ~Line() = default;

            Line& operator=(const Line& other);
            Line& operator=(Line&& other) noexcept;

            Vector2 getPoint1() const;
            Vector2 getPoint2() const;

            void setPoint1(const Vector2& p1);
            void setPoint2(const Vector2& p2);

            double getLength() const;
            double getAngle() const;

            Vector2 getIntersection(const Line& other) const;

            bool operator==(const Line& other) const;
            bool operator!=(const Line& other) const;

        private:
            Vector2 _p1;
            Vector2 _p2;
    };

} // namespace finder::math

#endif // __LINE_HPP__