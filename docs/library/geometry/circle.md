# 円ライブラリ群
## 概要
円のライブラリ群。

## 計算量
いろいろ

## コード
```cpp
#include "2d_common.cpp"
#include <set>

class Circle {
public:
    Point p;
    double r;

    Circle() {}
    Circle(Point p, double r) : p{p}, r{r} {}
};

class CircleUtil {
public:
    static bool intersect_cp(const Circle& c, const Point& p)
    {
        return PointOperator::abs(c.p - p) <= c.r + EPS;
    }

    static bool intersect_cc(const Circle& a, const Circle& b)
    {
        double d = PointOperator::abs(a.p - b.p);
        return d <= a.r + b.r && d >= abs(a.r - b.r);
    }

    static std::vector<Point> crosspoint_cc(const Circle& a, const Circle& b)
    {
        double d = PointOperator::abs(a.p - b.p);
        if (!intersect_cc(a, b) || d < EPS)
            return {};

        double rc = (a.r * a.r - b.r * b.r + d * d) / (2.0 * d);
        double rs = sqrt(a.r * a.r - rc * rc);
        Point p = (b.p - a.p) / d;
        return {a.p + p * Point{rc, rs}, a.p + p * Point{rc, -rs}};
    }

    static std::vector<Point> crosspoint_cl(const Circle& c, const Line& l)
    {
        double d = LineUtil::distance_lp(l, c.p);
        if (d > c.r)
            return {};

        Point p = LineUtil::projection(l, c.p);
        Vector v = (l.t - l.s) / PointOperator::abs(l.t - l.s);
        d = sqrt(c.r * c.r - d * d);
        return {p + v * d, p - v * d};
    }

    static std::vector<Point> tangent_cp(const Circle& c, const Point& p)
    {
        double x = PointOperator::norm(p - c.p);
        double d = x - c.r * c.r;

        if (d < -EPS)
            return {};

        d = std::max(d, 0.0);
        Point p1 = (p - c.p) * (c.r * c.r / x);
        Point p2 = Rotation::rotate90((p - c.p) * (-c.r * sqrt(d) / x));

        return {c.p + p1 - p2, c.p + p1 + p2};
    }

    static std::set<Line> tangent_cc(const Circle& a, const Circle& b)
    {
        if (PointOperator::abs(b.p - a.p) < EPS)
            return {};

        std::set<Line> common_lines;
        if (abs(a.r - b.r) < EPS) {
            Point dir = b.p - a.p;
            dir = Rotation::rotate90(dir * a.r / PointOperator::abs(dir));
            common_lines.emplace(a.p + dir, b.p + dir);
            common_lines.emplace(a.p - dir, b.p - dir);
        }
        else {
            Point p = (a.p * -b.r + b.p * a.r) / (a.r - b.r);
            auto ps = tangent_cp(a, p);
            auto qs = tangent_cp(b, p);
            for (int i = 0; i < (int)std::min(ps.size(), qs.size()); i++)
                common_lines.emplace(ps[i], qs[i]);
        }

        Point p = (a.p * b.r + b.p * a.r) / (a.r + b.r);
        auto ps = tangent_cp(a, p);
        auto qs = tangent_cp(b, p);
        for (int i = 0; i < (int)std::min(ps.size(), qs.size()); i++)
            common_lines.emplace(ps[i], qs[i]);

        return common_lines;
    }

    static Circle smallest_enclosing_circle(const std::vector<Point>& ps)
    {
        const auto &abs = PointOperator::abs;
        Point p{0, 0};
        for (Point x : ps)
            p = p + x;

        p = p / ps.size();
        double d = 0.5;
        while (d > EPS) {
            for (int k = 1; k <= 150; k++) {
                for (int i = 0; i < 100; i++) {
                    int s = 0;
                    for (int j = 0; j < (int)ps.size(); j++)
                        if (abs(ps[j] - p) > abs(ps[s] - p))
                            s = j;

                    p = p + (ps[s] - p) * d;
                }
                d *= 0.5;
            }
        }

        double max_dist = 0;
        for (Point x : ps) {
            if (abs(x - p) > max_dist + EPS)
                max_dist = abs(x - p);
        }

        return {p, max_dist};
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all)
- [AtCoder ABC151F](https://atcoder.jp/contests/abc151/tasks/abc151_f) ※最小包含円