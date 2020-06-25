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
    T cost;
    edge(int to, int cap, T cost, int rev) :
        to{to}, cap{cap}, cost{cost}, rev{rev} {}
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

    void add_edge(int from, int to, int cap, T cost)
    {
        g[from].emplace_back(to, cap, cost, g[to].size());
        g[to].emplace_back(from, 0, -cost, g[from].size() - 1);
    }

    T primal_dual(int s, int t, int f)
    {
        T res = 0;
        while (f > 0) {
            // (weight, node)
            std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
            pq.emplace(0, s);

            std::vector<T> h(g.size());
            std::vector<int> prevv(g.size()), preve(g.size());
            std::vector<T> weight(g.size(), INF);
            weight[s] = 0;

            while (!pq.empty()) {
                State p = pq.top(); pq.pop();
                int v = p.second;

                if (weight[v] < p.first)
                    continue;

                for (int i = 0; i < (int)g[v].size(); i++) {
                    edge<T>& e = g[v][i];
                    T nweight = weight[v] + e.cost + h[v] - h[e.to];
                    if (e.cap > 0 && weight[e.to] > nweight) {
                        weight[e.to] = nweight;
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        pq.emplace(weight[e.to], e.to);
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
            res += d * h[t];
            for (int v = t; v != s; v = prevv[v]) {
                edge<T>& e = g[prevv[v]][preve[v]];
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
        }

        return res;
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_B)