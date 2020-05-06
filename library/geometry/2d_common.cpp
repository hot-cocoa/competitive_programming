#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

constexpr static double EPS = 1e-10;
template<class T>
bool equals(T a, T b)
{
    return fabs(a - b) < EPS;
}

class Point {
public:
    double x, y;
    Point() {}
    Point(double x, double y) : x{x}, y{y} {}

    Point operator + (const Point &p) const
    {
        return {x + p.x, y + p.y};
    }

    Point operator - (const Point &p) const
    {
        return {x - p.x, y - p.y};
    }

    Point operator * (const double k) const
    {
        return {x * k, y * k};
    }

    Point operator / (const double k) const
    {
        return {x / k, y / k};
    }

    bool operator < (const Point &p) const
    {
        return x != p.x ? x < p.x : y < p.y;
    }
};

std::istream &operator >> (std::istream &is, Point &p)
{
    return is >> p.x >> p.y;
}

std::ostream &operator << (std::ostream os, Point &p)
{
    return os << "(" << p.x << " " << p.y << ")";
}

using Vector = Point;

class PointOperator {
public:
    static double dot(const Point &a, const Point &b)
    {
        return a.x * b.x + a.y * b.y;
    }

    static double cross(const Point &a, const Point &b)
    {
        return a.x * b.y - a.y * b.x;
    }

    static double norm(const Point &p)
    {
        return dot(p, p);
    }

    static double abs(const Point &p)
    {
        return sqrt(norm(p));
    }

    static double dist(const Point &a, const Point &b)
    {
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    }
};

class Angle {
private:
    constexpr static double PI = acos(-1);
public:
    static double to_rad(double angle)
    {
        return angle * PI / 180.0;
    }

    static double to_angle(double rad)
    {
        return rad * 180.0 / PI;
    }

    static double angle_between_vectors(
        const Point &a, const Point &b, const Point &c)
    {
        Vector v1 = b - a;
        Vector v2 = c - a;

        double aat = atan2(v1.y, v1.x);
        double bat = atan2(v2.y, v2.x);
        if (aat > bat)
            std::swap(aat, bat);

        double angle = to_angle(bat - aat);
        return std::min(angle, 360.0 - angle);
    }
};

class Rotation {
public:
    /*
     * 角度はラジアン単位
     */
    Point rotate(const Point &p, double th)
    {
        return {
            cos(th) * p.x - sin(th) * p.y,
            sin(th) * p.x + cos(th) * p.y
        };
    }

    /*
     * (cx, cy)を中心に回転する
     */
    Point rotate(const Point &p, double th, double cx, double cy)
    {
        return rotate({p.x - cx, p.y - cy}, th);
    }

    Point rotate90(const Point &p)
    {
        return {-p.y, p.x};
    }
};

enum class CcwIdentification : int {
    COUNTER_CLOCKWISE = +1,
    CLOCKWISE         = -1,
    ONLINE_BACK       = +2,
    ONLINE_FRONT      = -2,
    ON_SEGMENT        = +0
};

constexpr int operator * (
    CcwIdentification l, CcwIdentification r)
{
    return static_cast<int>(l) * static_cast<int>(r);
}

class CounterClockWise {
public:
    static CcwIdentification ccw(
        const Point &p0, const Point &p1, const Point &p2)
    {
        Vector a = p1 - p0;
        Vector b = p2 - p0;

        if (PointOperator::cross(a, b) > EPS)
            return CcwIdentification::COUNTER_CLOCKWISE;

        if (PointOperator::cross(a, b) < -EPS)
            return CcwIdentification::CLOCKWISE;

        if (PointOperator::dot(a, b) < -EPS)
            // ONLINE_BACK -> p2-p0-p1
            return CcwIdentification::ONLINE_BACK;

        if (PointOperator::norm(a) < PointOperator::norm(b))
            // ONLINE_FRONT -> p0-p1-p2
            return CcwIdentification::ONLINE_FRONT;

        // ON_SEGMENT -> p0-p2-p1
        return CcwIdentification::ON_SEGMENT;
    }
};

class Segment {
public:
    Point s;
    Point t;

    Segment(const Point &s, const Point &t) : s{s}, t{t} {}
};

class SegmentUtil {
public:
    /*
     * 線分上の点を取得する。
     * N分割した際の点を取得する。
     */
    static std::vector<Point> get_points_on_segment(const Segment &s, int N)
    {
        Point p1 = s.s, p2 = s.t;
        std::vector<Point> points_on_segment;
        for (int i = 0; i < N; i++) {
            double x = p1.x + i * (p2.x - p1.x) / N;
            double y = p1.y + i * (p2.y - p1.y) / N;
            points_on_segment.emplace_back(x, y);
        }
        return points_on_segment;
    }

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

    static bool intersect_ss(const Segment &a, const Segment &b)
    {
        std::vector<Point> s{a.s, a.t}, t{b.s, b.t};
        const auto &ccw = CounterClockWise::ccw;
        return (
            ccw(s[0], s[1], t[0]) * ccw(s[0], s[1], t[1]) <= 0 &&
            ccw(t[0], t[1], s[0]) * ccw(t[0], t[1], s[1]) <= 0
        );
    }

    static bool intersect_sp(const Segment &s, const Point &p)
    {
        const auto &ccw = CounterClockWise::ccw;
        return ccw(s.s, s.t, p) == CcwIdentification::ON_SEGMENT;
    }

    static Point crosspoint_ss(const Segment &a, const Segment &b)
    {
        Vector va = a.t - a.s, vb = b.t - b.s;
        const auto &cross = PointOperator::cross;
        return a.s + va * cross(vb, b.t - a.s) * (1.0 / cross(vb, va));
    }

    double distance_sp(const Segment &s, const Point &p)
    {
        const auto &abs = PointOperator::abs;
        Point r = projection(s, p);
        if (intersect_sp(s, r))
            return abs(r - p);

        return std::min(abs(s.s - p), abs(s.t - p));
    }

    double distance_ss(const Segment &a, const Segment &b)
    {
        if (intersect_ss(a, b))
            return 0;

        return std::min(
            std::min(distance_sp(a, b.s), distance_sp(a, b.t)),
            std::min(distance_sp(b, a.s), distance_sp(b, a.t))
        );
    }

    /*
     * 線分の垂直判定
     */
    bool orthogonal_ss(const Segment &a, const Segment &b)
    {
        Vector va = a.t - a.s;
        Vector vb = b.t - b.s;
        return equals<double>(PointOperator::dot(va, vb), 0);
    }

    /*
     * 線分の平行判定
     */
    bool parallel_ss(const Segment &a, const Segment &b)
    {
        Vector va = a.t - a.s;
        Vector vb = b.t - b.s;
        return equals<double>(PointOperator::cross(va, vb), 0);
    }
};

// -- 線分アレンジメント用
struct Edge {
    int to;
    double cost;
    Edge(int to, double cost) : to{to}, cost{cost} {}

    bool operator < (const Edge &e) const
    {
        return cost < e.cost;
    }
};
using Edges = std::vector<Edge>;
using Graph = std::vector<Edges>;
// --
class SegmentArrangement {
public:
    Graph make_graph(
        const std::vector<Segment> &segs, std::vector<Point> &ps)
    {
        Graph g;
        int N = segs.size();
        for (int i = 0; i < N; i++) {
            ps.emplace_back(segs[i].s);
            ps.emplace_back(segs[i].t);
            for (int j = i + 1; j < N; j++) {
                Vector a = segs[i].t - segs[i].s;
                Vector b = segs[j].t - segs[j].s;
                if (equals<double>(PointOperator::cross(a, b), 0))
                    continue;

                if (SegmentUtil::intersect_ss(segs[i], segs[j]))
                    ps.emplace_back(
                        SegmentUtil::crosspoint_ss(segs[i], segs[j]));
            }
        }

        std::sort(ps.begin(), ps.end());
        ps.erase(std::unique(ps.begin(), ps.end()), ps.end());

        int psN = ps.size();
        g.resize(psN);

        const auto &dist = PointOperator::dist;
        for (int i = 0; i < N; i++) {
            std::vector<std::pair<double, int>> vec;
            for (int j = 0; j < psN; j++) {
                if (SegmentUtil::intersect_sp(segs[i], ps[j]))
                    vec.emplace_back(dist(segs[i].s, ps[j]), j);
            }

            std::sort(vec.begin(), vec.end());
            for (int j = 0; j < (int)vec.size() - 1; j++) {
                int u = vec[j].second, v = vec[j + 1].second;
                double d = dist(ps[u], ps[v]);
                g[u].emplace_back(v, d);
                g[v].emplace_back(u, d);
            }
        }
        return g;
    }
};

using Line = Segment;

class LineUtil : SegmentUtil {
private:
    /*
     * 垂直二等分線を求める
     */
    static Line get_perpendicular_bisector(const Point &a, const Point &b)
    {
        double cx = (a.x + b.x) / 2.0;
        double cy = (a.y + b.y) / 2.0;
        return {
            {cx, cy},
            {cx + (a.y - b.y), cy + (b.x - a.x)}
        };
    }

public:
    /*
     * 法線ベクトルを求める
     */
    static std::vector<Vector> normal_line_vector(const Line &l)
    {
        Vector v = l.t - l.s;
        Point p = v / PointOperator::abs(v);

        return {
            {-p.y, p.x},
            {p.y, p.x}
        };
    }

    /*
     * 直線を距離dだけ平行移動させる
     */
    static std::vector<Line> translation(const Line &l, double d)
    {
        std::vector<Vector> nlv = normal_line_vector(l);
        return {
            {l.s + nlv[0] * d, l.t + nlv[0] * d},
            {l.s + nlv[1] * d, l.t + nlv[1] * d}
        };
    }

    /*
     * 垂直二等分線を求める
     */
    static Line get_perpendicular_bisector(const Line &l)
    {
        return get_perpendicular_bisector(l.s, l.t);
    }

    static bool intersect_ll(const Line &a, const Line &b)
    {
        const auto &cross = PointOperator::cross;

        bool diff_slope = abs(cross(a.t - a.s, b.t - b.s)) > EPS;
        bool same_lines = abs(cross(a.t - a.s, b.t - b.s)) < EPS;

        return diff_slope || same_lines;
    }

    static bool intersect_lp(const Line &l, const Point &p)
    {
        const auto &res = CounterClockWise::ccw(l.s, l.t, p);
        bool is_counter_clock_wise =
            (res == CcwIdentification::COUNTER_CLOCKWISE);
        bool is_clock_wise =
            (res == CcwIdentification::CLOCKWISE);

        return !is_counter_clock_wise && !is_clock_wise;
    }

    static bool intersect_ls(const Line &l, const Segment &s)
    {
        const auto &cross = PointOperator::cross;
        return cross(l.t - l.s, s.s - l.s) * cross(l.t - l.s, s.t - l.s) < EPS;
    }

    static Point crosspoint_ll(const Line &a, const Line &b)
    {
        Vector va = a.t - a.s, vb = b.t - b.s;
        const auto &cross = PointOperator::cross;

        double d = cross(vb, va);
        if (abs(d) < EPS)
            return b.s;

        return a.s + va * cross(vb, b.t - a.s) * (1.0 / d);
    }

    static double distance_lp(const Line &l, const Point &p)
    {
        return PointOperator::abs(p - projection(l, p));
    }

    static double distance_ll(const Line &a, const Line &b)
    {
        if (intersect_ll(a, b))
            return 0.0;

        return distance_lp(a, b.s);
    }

    double distance_ls(const Line &l, const Segment &s)
    {
        if (intersect_ls(l, s))
            return 0.0;

        return std::min(distance_lp(l, s.s), distance_lp(l, s.t));
    }
};

class Triangle {
public:
    double area(const Point &a, const Point &b, const Point &c)
    {
        // ヘロンの公式
        const auto dist = PointOperator::dist;
        double p = dist(a, b), q = dist(a, c), r = dist(b, c);
        double s = (p + q + r) / 2;
        return sqrt(s * (s - p) * (s - q) * (s - r));
    }
};
