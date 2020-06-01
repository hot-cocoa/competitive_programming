#include <vector>
#include <functional>

template<class T>
class SegmentTree {
private:
    using F = std::function<T(T, T)>;
    const F f; // Binary operation
    const T e; // Identity element

    int N;
    std::vector<T> dat;

    void build(int N_)
    {
        N = 1;
        while (N < N_)
            N *= 2;

        dat.assign(2 * N - 1, e);
    }
public:
    SegmentTree(int N, const F &f, const T &e) : f{f}, e{e}
    {
        build(N);
    }

    void update(int k, T x)
    {
        k += N - 1;
        dat[k] = x;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = f(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    T query(int a, int b, int k, int l, int r)
    {
        if (r <= a || b <= l)
            return e;

        if (a <= l && r <= b)
            return dat[k];

        T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
        T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return f(vl, vr);
    }

    T query(int l, int r)
    {
        return query(l, r + 1, 0, 0, N);
    }
};