# オイラーツアー
## 概要
木を根からDFSした際に頂点を訪問順に記録したもの。

## 計算量
O(V)

## コード
```cpp
#include <vector>

using Graph = std::vector<std::vector<int>>;

class EulerTour {
private:
    Graph g;
    std::vector<int> l, r;

    void dfs(int v, int p, int &k)
    {
        l[v] = k++;
        for (int to : g[v])
            if (to != p)
                dfs(to, v, k);

        r[v] = k;
    }

    void init(int V)
    {
        l.resize(V);
        r.resize(V);
    }

    void build()
    {
        int k = 0;
        dfs(0, -1, k);
    }

public:
    EulerTour(Graph g) : g{g} {
        init(g.size());
        build();
    }

    int left(int v)
    {
        return l[v];
    }

    int right(int v)
    {
        return r[v];
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_D)