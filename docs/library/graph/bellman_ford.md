# ベルマンフォード法
## 概要
単一始点最短経路を求める。  
辺の重みに負数が含まれていても問題なし。  
負の閉路が存在する場合、空vectorを返却する。

## 計算量
O(VE)

## コード

```cpp
#include <vector>
#include <limits>

template<class T>
struct Edge {
    int from;
    int to;
    T weight;

    Edge(int from, int to, T weight)
        : from{from}, to{to}, weight{weight} {}
};

template<class T>
using Edges = std::vector<Edge<T>>;

template<class T>
class BellmanFord {
private:
    int V;
    int E;
    Edges<T> es;
    std::vector<T> weight;

    constexpr static T INF = std::numeric_limits<T>::max() / 2;
public:
    BellmanFord(int V, int E, const Edges<T>& es)
        : V{V}, E{E}, es{es} {}

    bool find_negative_loop(int s)
    {
        weight.assign(V, INF);
        weight[s] = 0;

        int used_cnt = 0;
        bool updated;
        do {
            updated = false;
            used_cnt++;
            for (const auto& [from, to, w] : es) {
                if (weight[from] != INF &&
                    weight[to] > weight[from] + w) {

                    weight[to] = weight[from] + w;
                    if (used_cnt == V)
                        return true;

                    updated = true;
                }
            }
        } while (updated);

        return false;
    }

    std::vector<T> shortest_path(int s)
    {
        if (find_negative_loop(s))
            return {};

        return weight;
    }

    bool is_updated(T w)
    {
        return w != INF;
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_B)
