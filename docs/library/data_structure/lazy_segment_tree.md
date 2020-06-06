# 遅延評価セグメント木
## 概要
セグメント木の遅延評価ver。

## 計算量
- 構築：O(n)
- 更新：O(log n)
- クエリ：O(log n)

## コード
```cpp
#include <vector>
#include <functional>

template<class T, class U>
class LazySegmentTree {
private:
    using FT = std::function<T(T, T)>;
    using FX = std::function<T(T, U)>;
    using FU = std::function<U(U, U)>;
    using FS = std::function<U(U, int)>;

    const FT ft;
    const FX fx;
    const FU fu;
    const FS fs;
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

    void eval(int k, int len)
    {
        if (lazy[k] == eu)
            return;

        if (k < N - 1) {
            lazy[k * 2 + 1] = fu(lazy[k * 2 + 1], lazy[k]);
            lazy[k * 2 + 2] = fu(lazy[k * 2 + 2], lazy[k]);
        }
        dat[k] = fx(dat[k], fs(lazy[k], len));
        lazy[k] = eu;
    }

    void update(int a, int b, U x, int k, int l, int r)
    {
        eval(k, r - l);
        if (a <= l && r <= b) {
            lazy[k] = fu(lazy[k], x);
            eval(k, r - l);
        }
        else if (a < r && l < b) {
            update(a, b, x, k * 2 + 1, l, (l + r) / 2);
            update(a, b, x, k * 2 + 2, (l + r) / 2, r);
            dat[k] = ft(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    T query(int a, int b, int k, int l, int r)
    {
        eval(k, r - l);
        if (r <= a || b <= l)
            return et;

        if (a <= l && r <= b)
            return dat[k];

        T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
        T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return ft(vl, vr);
    }
public:
    LazySegmentTree(
        int N, const FT &ft, const FX &fx, const FU &fu, const FS &fs,
        const T &et, const U &eu) : ft{ft}, fx{fx}, fu{fu}, fs{fs}, et{et}, eu{eu}
    {
        build(N);
    }

    void assign(int n, int x)
    {
        for (int i = 0; i < n; i++)
            dat[i + N - 1] = x;

        for (int i = N - 2; i >= 0; i--)
            dat[i] = ft(dat[i * 2 + 1], dat[i * 2 + 2]);
    }

    void update(int l, int r, U x)
    {
        update(l, r + 1, x, 0, 0, N);
    }

    T query(int l, int r)
    {
        return query(l, r + 1, 0, 0, N);
    }
};
```

## RSQ and RAQ
```cpp
const auto ft = [](int64 a, int64 b) { return a + b; };
const auto fx = [](int64 a, int64 b) { return a + b; };
const auto fu = [](int64 a, int64 b) { return a + b; };
const auto fs = [](int64 a, int64 b) { return a * b; };
const auto et = 0;
const auto eu = 0;
LazySegmentTree<int64, int64> seg(2 * n, ft, fx, fu, fs, et, eu);
```

## RMQ and RAQ
```cpp
const auto ft = [](int64 a, int64 b) { return std::min(a, b); };
const auto fx = [](int64 a, int64 b) { return a + b; };
const auto fu = [](int64 a, int64 b) { return a + b; };
const auto fs = [](int64 a, int64 b) { return a; };
const auto et = std::numeric_limits<int>::max();
const auto eu = 0;
LazySegmentTree<int64, int64> seg(n, ft, fx, fu, fs, et, eu);
seg.assign(n, 0);
```

## 検証
- [AOJ Library(RSQ and RAQ)](https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_G)
- [AOJ Library(RMQ and RAQ)](https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H)