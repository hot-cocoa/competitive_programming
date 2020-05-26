# 最小全域木(プリム法)
## 概要
グラフの最小全域木を求める。  
最小全域木とは、グラフの全域木のうち含まれる辺の重みの総和が最小となる。

## 計算量
O(m log n)  
n：頂点数、m：辺数

## コード
```cpp
#include <vector>
#include <queue>

struct edge {
    int to, cost;
    edge(int to, int cost) : to{to}, cost{cost} {}
};

using vec = std::vector<edge>;
using Graph = std::vector<vec>;

class MinimumSpanningTree {
private:
    using pii = std::pair<int, int>;

public:
    int prim(const Graph &g)
    {
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
        pq.emplace(0, 0);

        std::vector<bool> visited(g.size());
        int total_cost = 0;
        while (!pq.empty()) {
            pii p = pq.top(); pq.pop();

            int curr = p.second;
            if (visited[curr])
                continue;

            visited[curr] = true;
            total_cost += p.first;

            for (edge e : g[curr])
                pq.emplace(e.cost, e.to);
        }

        return total_cost;
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_2_A)