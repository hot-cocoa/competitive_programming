# 多角形ライブラリ群
## 概要
多角形のライブラリ群。

## 計算量
いろいろ

## コード
```cpp
#include "2d_common.cpp"

using Polygon = std::vector<Point>;
using PolygonItr = std::vector<Point>::iterator;

template<class T>
T prev(const std::vector<T> &x, int idx)
{
    return x[(idx - 1 + x.size()) % x.size()];
}

template<class T>
T curr(const std::vector<T> &x, int idx)
{
    return x[idx % x.size()];
}

template<class T>
T next(const std::vector<T> &x, int idx)
{
    return x[(idx + 1) % x.size()];
}

bool sort_x(Point p1, Point p2)
{
    if (p1.x != p2.x)
        return p1.x - p2.x < -EPS;
    else
        return p1.y - p2.y < -EPS;
}

bool sort_y(Point p1, Point p2)
{
    if (p1.y != p2.y)
        return p1.y - p2.y < -EPS;
    else
        return p1.x - p2.x < -EPS;
}

enum class PolygonPointRelation {
    INSIDE,
    BOUNDARY,
    OUTSIDE
};

class PolygonUtil {
private:
    constexpr static double INF = 1e60;

    static double closest_pair(PolygonItr pg, int N)
    {
        if (N <= 1)
            return INF;

        int M = N / 2;
        double x = pg[M].x;
        double min_dist =
            std::min(
                closest_pair(pg, M),
                closest_pair(pg + M, N - M)
            );

        auto compare_y = [](const Point &a, const Point &b) -> bool
        {
            return a.y < b.y;
        };
        std::inplace_merge(pg, pg + M, pg + N, compare_y);

        for (int i = 0; i < N; i++) {
            if (fabs(pg[i].x - x) >= min_dist)
                continue;

            for (int j = 0; j < i; j++) {
                double dx = pg[i].x - pg[i - j - 1].x;
                double dy = pg[i].y - pg[i - j - 1].y;
                if (dy >= min_dist)
                    break;

                min_dist = std::min(min_dist, sqrt(dx * dx + dy * dy));
            }
        }
        return min_dist;
    }

public:
    static double area(const Polygon &p)
    {
        double res = 0;
        for (int i = 0; i < (int)p.size(); i++)
            res += PointOperator::cross(
                curr<Point>(p, i), next<Point>(p, i));

        return res / 2.0;
    }

    static bool is_convex(const Polygon &p)
    {
        auto is_clock_wise = [](const Polygon &p, int idx) -> bool
        {
            const auto &ccw = CounterClockWise::ccw;
            auto pp = prev<Point>(p, idx);
            auto cp = curr<Point>(p, idx);
            auto np = next<Point>(p, idx);
            return ccw(pp, cp, np) == CcwIdentification::CLOCKWISE;
        };

        for (int i = 0; i < (int)p.size(); i++)
            if (is_clock_wise(p, i))
                return false;

        return true;
    }

    static PolygonPointRelation contain_pp(const Polygon &pg, const Point &p)
    {
        const auto &cross = PointOperator::cross;
        const auto &dot   = PointOperator::dot;

        int N = pg.size();
        bool in = false;
        for (int i = 0; i < N; i++) {
            auto cv = curr<Point>(pg, i) - p;
            auto nv = next<Point>(pg, i) - p;
            if (cv.y > nv.y)
                std::swap(cv, nv);

            if (cv.y <= 0 && nv.y > 0 && cross(cv, nv) < 0)
                in = !in;

            if (cross(cv, nv) == 0 && dot(cv, nv) <= 0)
                return PolygonPointRelation::BOUNDARY;
        }

        return (in ? PolygonPointRelation::INSIDE :
                     PolygonPointRelation::OUTSIDE);
    }

    static Polygon convex_hull(const Polygon &base)
    {
        int N = base.size();
        Polygon pg(N * 2);
        Polygon ps = base;
        std::sort(ps.begin(), ps.end(), sort_y);

        int j = 0;
        const auto &cross = PointOperator::cross;
        for (int i = 0; i < N; i++) {
            while (j > 1 && cross(pg[j - 1] - pg[j - 2], ps[i] - pg[j - 1]) < 0)
                j--;

            pg[j++] = ps[i];
        }

        for (int i = N - 2, k = j; i >= 0; i--) {
            while (j > k && cross(pg[j - 1] - pg[j - 2], ps[i] - pg[j - 1]) < 0)
                j--;

            pg[j++] = ps[i];
        }
        pg.resize(j - 1);
        return pg;
    }

    static double polygon_diameter(const Polygon &pg)
    {
        const auto &dist = PointOperator::dist;

        Polygon np = convex_hull(pg);
        int N = np.size();
        if (N == 2)
            return dist(np[0], np[1]);

        int i = 0, j = 0;
        for (int k = 0; k < N; k++) {
            if (!sort_x(np[i], np[k]))
                i = k;

            if (sort_x(np[j], np[k]))
                j = k;
        }

        double diameter = 0;
        int si = i, sj = j;
        while (i != sj || j != si) {
            diameter = std::max(diameter, dist(np[i], np[j]));
            auto pi = next<Point>(np, i) - curr<Point>(np, i);
            auto pj = next<Point>(np, j) - curr<Point>(np, j);

            if (PointOperator::cross(pi, pj) < 0)
                i = (i + 1) % N;
            else
                j = (j + 1) % N;
        }
        return diameter;
    }

    static Polygon convex_cut(const Polygon &pg, const Line &l)
    {
        const auto &ccw = CounterClockWise::ccw;

        Polygon cutted_polygon;
        for (int i = 0; i < (int)pg.size(); i++) {
            Point cp = curr<Point>(pg, i);
            Point np = next<Point>(pg, i);
            if (ccw(l.s, l.t, cp) != CcwIdentification::CLOCKWISE)
                cutted_polygon.emplace_back(cp);

            if (ccw(l.s, l.t, cp) * ccw(l.s, l.t, np) < 0)
                cutted_polygon.emplace_back(
                    LineUtil::crosspoint_ll({cp, np}, l));
        }

        return cutted_polygon;
    }

    static double closest_pair(const Polygon &pg)
    {
        Polygon p = pg;
        std::sort(p.begin(), p.end());
        return closest_pair(p.begin(), p.size());
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all)