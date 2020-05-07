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

    static auto contain_pp(const Polygon &pg, const Point &p)
    {
        const auto &cross = PointOperator::cross;
        const auto &dot   = PointOperator::dot;

        int N = pg.size();
        bool in = false;
        for (int i = 0; i < N; i++) {
            auto cv = curr<Point>(p, idx) - p;
            auto nv = next<Point>(p, idx) - p;
            if (cv.y > nv.y)
                std::swap(cv, nv);

            if (cv.y <= 0 && nv.y > 0 && cross(cv, nv) < 0)
                in = !in;

            if (cross(cv, np) == 0 && dot(cv, nv) <= 0)
                PolygonPointRelation::BOUNDARY;
        }

        return (in ? PolygonPointRelation::INSIDE :
                     PolygonPointRelation::OUTSIDE);
    }
};
