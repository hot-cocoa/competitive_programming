# セグメント木
## 概要
配列Aに対して、以下の操作を高速に行うデータ構造である。
1. iとxが与えられたとき、A<sub>i</sub>の値をxに更新する。
2. lとrが与えられたとき、A<sub>l</sub>, A<sub>l+1</sub>, ..., A<sub>r</sub>の演算を行う。

## 計算量
- 構築：O(n)
- 更新：O(log n)
- クエリ：O(log n)

## コード
```cpp
#include <vector>
#include <functional>

template<class T>
class SegmentTree {
private:
    using F = std::function<T(T, T)>;
    const F f;
    const F g;
    const T e;

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
    SegmentTree(
        int N, const T& e,
        const F& f, const F& g = [](int l, int r){ return r; }) :
        f{f}, g{g}, e{e}
    {
        build(N);
    }

    void update(int k, T x)
    {
        k += N - 1;
        dat[k] = g(dat[k], x);
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
```

## Range Minimum Query
```cpp
const auto f = [](int a, int b){ return std::min(a, b); };
const auto g = [](int a, int b){ return b; };
SegmentTree<int> seg(n, std::numeric_limits<int>::max(), f, g);
```

## Range Sum Query
```cpp
const auto f = [](int a, int b){ return a + b; };
SegmentTree<int> seg(n, 0, f, f);
```

## 検証
- [AOJ Library(RMQ)](https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A)
- [AOJ Library(RSQ)](https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B)