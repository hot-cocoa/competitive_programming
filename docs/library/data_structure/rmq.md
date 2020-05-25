# Range Minimum Query
## 概要
配列Aに対して、以下の操作を高速に行うデータ構造である。
1. iとxが与えられたとき、A<sub>i</sub>の値をxに更新する。
2. lとrが与えられたとき、A<sub>l</sub>, A<sub>l+1</sub>, ..., A<sub>r</sub>の最小値を求める。

## 計算量
1. O(log n)
2. O(log n)

## コード
```cpp
#include <vector>

class RMQ {
private:
    int N;
    std::vector<int> dat;
    constexpr static int INF = 1<<25;

public:
    RMQ(int N_)
    {
        N = 1;
        while (N < N_)
            N *= 2;

        dat.assign(2 * N - 1, INF);
    }

    void update(int k, int a)
    {
        k += N - 1;
        dat[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = std::min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    int query(int a, int b, int k, int l, int r)
    {
        if (r <= a || b <= l)
            return INF;

        if (a <= l && r <= b)
            return dat[k];

        int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
        int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return std::min(vl, vr);
    }

    /**
     * minimum value [l, r]
     */
    int query(int l, int r)
    {
        return query(l, r + 1, 0, 0, N);
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A)