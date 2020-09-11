# 最小費用流
## 概要
[最小費用流](https://en.wikipedia.org/wiki/Minimum-cost_flow_problem)を求める。

## 計算量
O(FElogV)

## コード
```cpp
#include <vector>
#include <queue>
#include <limits>

template<class T>
struct edge {
    int to, cap, rev;
    T weight;
    edge(int to, int cap, T weight, int rev) :
        to{to}, cap{cap}, weight{weight}, rev{rev} {}
};

template<class T>
class MinimumCostFlow {
private:
    using Graph = std::vector<std::vector<edge<T>>>;
    using State = std::pair<T, int>;
    const T INF = std::numeric_limits<T>::max() / 2;
    Graph g;

public:
    MinimumCostFlow(int V)
    {
        g.resize(V);
    }

    void add_edge(int from, int to, int cap, T weight)
    {
        g[from].emplace_back(to, cap, weight, g[to].size());
        g[to].emplace_back(from, 0, -weight, g[from].size() - 1);
    }

    T primal_dual(int s, int t, int f)
    {
        T min_cost = 0;
        while (f > 0) {
            // (weight, node)
            std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
            pq.emplace(0, s);

            std::vector<T> h(g.size());
            std::vector<int> prevv(g.size()), preve(g.size());
            std::vector<T> weight(g.size(), INF);
            weight[s] = 0;

            while (!pq.empty()) {
                auto [tw, v] = pq.top(); pq.pop();
                if (weight[v] < tw)
                    continue;

                for (int i = 0; i < (int)g[v].size(); i++) {
                    auto& [to, cap, rev, w] = g[v][i];
                    T nweight = weight[v] + w + h[v] - h[to];
                    if (cap > 0 && weight[to] > nweight) {
                        weight[to] = nweight;
                        prevv[to] = v;
                        preve[to] = i;
                        pq.emplace(weight[to], to);
                    }
                }
            }

            if (weight[t] == INF)
                return -1;

            for (int v = 0; v < (int)g.size(); v++)
                h[v] += weight[v];

            int d = f;
            for (int v = t; v != s; v = prevv[v])
                d = std::min(d, g[prevv[v]][preve[v]].cap);

            f -= d;
            min_cost += d * h[t];
            for (int v = t; v != s; v = prevv[v]) {
                auto& [to, cap, rev, w] = g[prevv[v]][preve[v]];
                cap -= d;
                g[v][rev].cap += d;
            }
        }

        return min_cost;
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_B)