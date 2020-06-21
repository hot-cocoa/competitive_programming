# 最小全域木(プリム法)
## 概要
グラフの最小全域木を求める。  
最小全域木とは、グラフの全域木のうち含まれる辺の重みの総和が最小となる。

## 計算量
O(E log V)

## コード
```cpp
#include <vector>
#include <queue>

template<class T>
struct edge {
    int to;
    T weight;
    edge(int to, T weight) : to{to}, weight{weight} {}
};

template<class T>
using Graph = std::vector<std::vector<edge<T>>>;

template<class T>
class MinimumSpanningTree {
private:
    using State = std::pair<T, int>;

public:
    T solve(const Graph<T> &g)
    {
        std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
        pq.emplace(0, 0);

        std::vector<bool> visited(g.size());
        T total_weight = 0;
        while (!pq.empty()) {
            State p = pq.top(); pq.pop();

            int curr = p.second;
            if (visited[curr])
                continue;

            visited[curr] = true;
            total_weight += p.first;

            for (auto e : g[curr])
                pq.emplace(e.weight, e.to);
        }

        return total_weight;
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/2/GRL_2_A)