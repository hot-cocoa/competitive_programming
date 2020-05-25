# Union Find
## 概要
以下の操作を高速に行うデータ構造である。
1. xとyが与えられたとき、xを含む集合とyを含む集合をマージする。
2. xとyが与えられたとき、xとyが同じ集合に属しているかを判定する。

## 計算量
O(α(n))
※α(n)はアッカーマン関数A(n, n)の逆関数であり、ほぼ時間はかからない。

## コード
```cpp
#include <vector>

class UnionFind {
private:
    int group_count;
    std::vector<int> par, rank, gsize;
public:
    UnionFind(int N)
    {
        group_count = N;

        par.resize(N);
        rank.resize(N);
        gsize.resize(N);

        for (int i = 0; i < N; i++) {
            par[i] = i;
            rank[i] = 0;
            gsize[i] = 1;
        }
    }

    int find(int x)
    {
        if (par[x] == x)
            return x;

        return par[x] = find(par[x]);
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);

        if (x == y)
            return;

        if (rank[x] < rank[y]) {
            par[x] = y;
            gsize[y] += gsize[x];
        }
        else {
            par[y] = x;
            gsize[x] += gsize[y];
            if (rank[x] == rank[y])
                rank[x]++;
        }
        group_count--;
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }

    int size(int x)
    {
        return gsize[find(x)];
    }

    int groups()
    {
        return group_count;
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_A)