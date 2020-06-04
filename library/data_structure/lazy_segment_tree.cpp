#include <vector>
#include <functional>

template<class T, class U>
class LazySegmentTree {
private:
    using FT = std::function<T(T, T)>;
    using FX = std::function<T(T, U)>;
    using FU = std::function<U(U, U)>;

    const FT ft;
    const FX fx;
    const FU fu;
    const T et;
    const U eu;

    int N;
    std::vector<T> dat;
    std::vector<U> lazy;

    void build(int N_)
    {
        N = 1;
        while (N < N_)
            N *= 2;

        dat.assign(2 * N - 1, et);
        lazy.assign(2 * N - 1, eu);
    }

    void eval(int k)
    {
        if (lazy[k] == eu)
            return;

        if (k < N - 1) {
            lazy[k * 2 + 1] = fu(lazy[k * 2 + 1], lazy[k]);
            lazy[k * 2 + 2] = fu(lazy[k * 2 + 2], lazy[k]);
        }
        dat[k] = fx(dat[k], lazy[k]);
        lazy[k] = eu;
    }

public:
    LazySegmentTree(int N, const FT &ft, const FX &fx, const FU &fu, const T &et, const U &eu) :
        ft{ft}, fx{fx}, fu{fu}, et{et}, eu{eu}
    {
        build(N);
    }

    void update(int a, int b, U x, int k, int l, int r)
    {
        eval(k);
        if (a <= l && r <= b) {
            lazy[k] = fu(lazy[k], x);
            eval(k);
        }
        else if (a < r && l < b) {
            update(a, b, x, k * 2 + 1, l, (l + r) / 2);
            update(a, b, x, k * 2 + 2, (l + r) / 2, r);
            dat[k] = ft(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    void update(int l, int r, U x)
    {
        update(l, r + 1, x, 0, 0, N);
    }

    T query(int a, int b, int k, int l, int r)
    {
        eval(k);
        if (r <= a || b <= l)
            return et;

        if (a <= l && r <= b)
            return dat[k];

        T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
        T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return ft(vl, vr);
    }

    T query(int l, int r)
    {
        return query(l, r + 1, 0, 0, N);
    }
};