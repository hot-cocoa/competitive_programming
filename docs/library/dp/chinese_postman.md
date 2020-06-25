# 無向中国人郵便配達問題
## 概要
無向グラフについて以下の条件を満たす最小の重みを求める。
- ある頂点から開始して、同じ頂点で終了する。
- 各辺を少なくとも1回使用する。

## 計算量
O(2<sup>V</sup> V<sup>2</sup>)

## コード
```cpp
#include <vector>
#include <queue>
#include <limits>

template<class T>
class Edge {
public:
    int src, dst;
    T weight;

    Edge(int src, int dst, T weight) :
        src{src}, dst{dst}, weight{weight} {}

    bool operator < (const Edge<T>& e) const
    {
        if (weight != e.weight)
            return weight > e.weight;
        if (src != e.src)
            return src < e.src;

        return dst < e.dst;
    }
};

template<class T>
using Graph = std::vector<std::vector<Edge<T>>>;

template<class T>
class ChinesePostman {
private:
    constexpr static T INF = std::numeric_limits<T>::max() / 2;
    Graph<T> g;

public:
    ChinesePostman(int V) { g.resize(V); }
    ChinesePostman(const Graph<T>& g) : g{g} {}

    void add_edge(int src, int dst, T weight)
    {
        g[src].emplace_back(src, dst, weight);
        g[dst].emplace_back(dst, src, weight);
    }

    T solve()
    {
        T sum = 0;
        int size = g.size();

        std::vector<int> odds;
        for (int i = 0; i < size; i++) {
            for (const auto &e : g[i])
                sum += e.weight;

            if (g[i].size() & 1)
                odds.emplace_back(i);
        }

        sum /= 2;
        int N = odds.size();
        std::vector<std::vector<T>> w(N, std::vector<T>(N));

        for (int i = 0; i < N; i++) {
            int s = odds[i];
            std::vector<T> weight(size, INF);
            weight[s] = 0;

            std::vector<int> prev(size, -2);
            std::priority_queue<Edge<T>> pq;
            pq.emplace(-1, s, 0);
            while (!pq.empty()) {
                const auto e = pq.top(); pq.pop();
                if (prev[e.dst] != -2)
                    continue;

                prev[e.dst] = e.src;
                for (const auto &x : g[e.dst])
                    if (weight[x.dst] > e.weight + x.weight) {
                        weight[x.dst] = e.weight + x.weight;
                        pq.emplace(x.src, x.dst, weight[x.dst]);
                    }
            }

            for (int j = 0; j < N; j++)
                w[i][j] = weight[odds[j]];
        }

        std::vector<T> dp(1 << N, INF);
        dp[0] = 0;
        for (int S = 0; S < (1 << N); S++)
            for (int i = 0; i < N; i++) {
                if (S >> i & 1)
                    continue;

                for (int j = i + 1; j < N; j++) {
                    if (S >> j & 1)
                        continue;

                    int next = S | (1 << i) | (1 << j);
                    dp[next] = std::min(dp[next], dp[S] + w[i][j]);
                }
            }

        return sum + dp[(1 << N) - 1];
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/2/DPL_2_B)