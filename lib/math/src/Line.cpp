#include <Line.hpp>

namespace finder::math {

    Line::Line(const Vector2 &p1, const Vector2 &p2)
    {
        _p1 = p1;
        _p2 = p2;
    }

    Line::Line(const Line &other)
    {
        _p1 = other._p1;
        _p2 = other._p2;
    }

    Line::Line(Line &&other) noexcept
    {
        _p1 = other._p1;
        _p2 = other._p2;
    }

    Line &Line::operator=(const Line &other)
    {
        _p1 = other._p1;
        _p2 = other._p2;
        return *this;
    }

    Line &Line::operator=(Line &&other) noexcept
    {
        _p1 = other._p1;
        _p2 = other._p2;
        return *this;
    }

    Vector2 Line::getPoint1() const
    {
        return _p1;
    }

    Vector2 Line::getPoint2() const
    {
        return _p2;
    }

    void Line::setPoint1(const Vector2 &p1)
    {
        _p1 = p1;
    }

    void Line::setPoint2(const Vector2 &p2)
    {
        _p2 = p2;
    }

    double Line::getLength() const
    {
        return _p1.distanceTo(_p2);
    }

    double Line::getAngle() const
    {
        return (atan2(_p2.y - _p1.y, _p2.x - _p1.x) * 180 / M_PI) + 180;
    }

    Vector2 Line::getIntersection(const Line& other) const {
        double x1 = _p1.x;
        double y1 = _p1.y;
        double x2 = _p2.x;
        double y2 = _p2.y;
        double x3 = other._p1.x;
        double y3 = other._p1.y;
        double x4 = other._p2.x;
        double y4 = other._p2.y;

        double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
        if (d == 0) {
            return Vector2(0, 0);
        }

        double x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / d;
        double y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / d;

        return Vector2(x, y);
    }

    bool Line::isIntersecting(const Line &other) const
    {
        return counterClockwise(_p1, other._p1, other._p2) != 
               counterClockwise(_p2, other._p1, other._p2) &&
               counterClockwise(_p1, _p2, other._p1) != 
               counterClockwise(_p1, _p2, other._p2);
    }

    bool Line::operator==(const Line &other) const
    {
        return _p1 == other._p1 && _p2 == other._p2;
    }

    bool Line::operator!=(const Line &other) const
    {
        return !(*this == other);
    }

    bool Line::counterClockwise(const Vector2 &a, const Vector2 &b, const Vector2 &c) const
    {
        return (c.y - a.y) * (b.x - a.x) > (b.y - a.y) * (c.x - a.x);
    }
} // namespace finder::math