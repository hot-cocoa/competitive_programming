# 3次元幾何の基本要素
## 概要
3次元幾何の基本要素群。

## 計算量
いろいろ

## コード
```cpp
#include <iostream>
#include <cmath>

constexpr static double INF = 1e55;
constexpr static double EPS = 1e-10;

bool equals(double a, double b)
{
    return fabs(a - b) < EPS;
}

class Point {
public:
    double x, y, z;
    Point() {}
    Point(double x, double y, double z) : x{x}, y{y}, z{z} {}

    Point operator + (const Point &p) const
    {
        return {x + p.x, y + p.y, z + p.z};
    }

    Point operator - (const Point &p) const
    {
        return {x - p.x, y - p.y, z - p.z};
    }

    Point operator * (const double k) const
    {
        return {x * k, y * k, z * k};
    }

    Point operator / (const double k) const
    {
        return {x / k, y / k, z / k};
    }

    bool operator == (const Point &p) const
    {
        return equals(x, p.x) && equals(y, p.y) && equals(z, p.z);
    }

    bool operator != (const Point &p) const
    {
        return !(*this == p);
    }
};

class PointOperator {
public:
    static double dot(const Point &a, const Point &b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    static Point cross_vec(const Point &a, const Point &b)
    {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }

    static double cross(const Point &a, const Point &b)
    {
        return abs(cross_vec(a, b));
    }

    static double norm(const Point &p)
    {
        return dot(p, p);
    }

    static double norm(const Point &a, const Point &b)
    {
        return norm(a - b);
    }

    static double abs(const Point &p)
    {
        return sqrt(norm(p));
    }

    static double dist(const Point &a, const Point &b)
    {
        return abs(a - b);
    }
};

using Vector = Point;

std::istream &operator >> (std::istream &is, Point &p)
{
    return is >> p.x >> p.y >> p.z;
}

class Segment {
public:
    Point s, t;
    Segment() {}
    Segment(const Point &s, const Point &t) : s{s}, t{t} {}
};

class SegmentUtil {
public:
    static Point projection(const Segment &s, const Point &p)
    {
        Vector v = s.t - s.s;
        double t =
            PointOperator::dot(p - s.s, v) / PointOperator::norm(v);

        return s.s + v * t;
    }

    static Point reflection(const Segment &s, const Point &p)
    {
        return p + (projection(s, p) - p) * 2.0;
    }

    static double distance_sp(const Segment &s, const Point &p)
    {
        double a = PointOperator::dot(s.t - s.s, s.t - s.s);
        double b = PointOperator::dot(s.t - s.s, s.s - p);
        double c = PointOperator::dot(s.s - p, s.s - p);
        double t = -b / a;
        if (t < 0)
            return PointOperator::abs(s.s - p);
        if (t > 1)
            return PointOperator::abs(s.t - p);

        return a * t * t + 2 * b * t + c;
    }

    double distance_ss(const Segment &s1, const Segment &s2)
    {
        Point v1 = s1.t - s1.s, v2 = s2.t - s2.s, v3 = s1.s - s2.s;
        double a = +PointOperator::dot(v1, v1);
        double b = -PointOperator::dot(v1, v2);
        double c = -PointOperator::dot(v1, v2);
        double d = +PointOperator::dot(v2, v2);
        double e = -PointOperator::dot(v1, v3);
        double f = +PointOperator::dot(v2, v3);

        double min = INF;
        min = std::min(min, distance_sp(s1, s2.s));
        min = std::min(min, distance_sp(s1, s2.t));
        min = std::min(min, distance_sp(s2, s1.s));
        min = std::min(min, distance_sp(s2, s1.t));

        double det = a * d - b * c;
        if (det != 0) {
            double s = (d * e - b * f) / det;
            double t = (-c * e + a * f) / det;
            if (0 <= s && s <= 1 && 0 <= t && t <= 1)
                min = std::min(
                    min, PointOperator::dist(s1.s + v1 * s, s2.s + v2 * t));
        }
        return min;
    }
};

using Line = Segment;

class LineUtil : SegmentUtil {
public:
    static double distance_lp(const Line &l, const Point &p)
    {
        return PointOperator::abs(p - projection(l, p));
    }

    static double distance_ll(const Line &a, const Line &b)
    {
        Vector v = PointOperator::cross_vec(a.t - a.s, b.t - b.s);
        Point p = a.s - b.s;
        if (PointOperator::abs(v) < EPS)
            return distance_lp(a, b.s);

        return abs(PointOperator::dot(v, p)) / PointOperator::abs(v);
    }
};
```

## 検証
※未検証