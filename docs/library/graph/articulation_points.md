# 関節点
## 概要
グラフGの関節点を列挙する。  
連結な無向グラフGについて、ある頂点uおよびuに隣接する辺を削除した場合にグラフが非連結になるような頂点uを関節点という。

## 計算量
O(V + E)

## コード
```cpp
#include <iostream>
#include <vector>

using vec = std::vector<int>;
using Graph = std::vector<vec>;

constexpr static int INF = 1e9;

class ArticulationPoints {
private:
    Graph g;
    vec ord, low;
    vec ap;

    void init()
    {
        int V = g.size();
        ord.assign(V, -1);
        low.assign(V, INF);
    }

    void dfs(int v, int prev, int &k)
    {
        ord[v] = low[v] = k++;
        int cnt = 0;
        bool is_ap = false;
        for (int to : g[v]) {
            if (to == prev)
                continue;

            if (ord[to] == -1) {
                cnt++;
                dfs(to, v, k);
                low[v] = std::min(low[v], low[to]);
                if (prev >= 0 && ord[v] <= low[to])
                    is_ap = true;
            }
            low[v] = std::min(low[v], ord[to]);
        }

        if (prev == -1 && cnt >= 2)
            is_ap = true;

        if (is_ap)
            ap.emplace_back(v);
    }

public:
    ArticulationPoints(Graph g) : g{g} {
        init();
    }

    void dfs(int v, int &k)
    {
        dfs(v, -1, k);
    }

    vec articulation_points()
    {
        return ap;
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_3_A)