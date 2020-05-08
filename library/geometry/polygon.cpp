#include "2d_common.cpp"

using Polygon = std::vector<Point>;

template<class T>
T prev(std::vector<T> x, int idx)
{
    return x[(idx - 1 + x.size()) % x.size()];
}

template<class T>
T curr(std::vector<T> x, int idx)
{
    return x[idx % x.size()];
}

template<class T>
T next(std::vector<T> x, int idx)
{
    return x[(idx + 1) % x.size()];
}

bool sort_y(Point p1, Point p2)
{
    if (p1.y != p2.y)
        return p1.y - p2.y < -EPS;
    else
        return p1.x - p2.x < -EPS;
}

enum class PolygonPointRelation : int {
    INSIDE   = 2,
    BOUNDARY = 1,
    OUTSIDE  = 0
};

/*
 * [Verified]
 * ・area
 * 　http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A
 *
 * ・is_convex
 * 　http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B
 *
 * ・contain_pp
 * 　http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C
 *
 * ・convex_hull
 * 　http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A
 */
class PolygonUtil {
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
};
