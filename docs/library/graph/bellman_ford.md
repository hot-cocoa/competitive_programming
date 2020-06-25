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
    T cost;

    Edge(int from, int to, T cost)
        : from{from}, to{to}, cost{cost} {}
};

template<class T>
class BellmanFord {
private:
    int V;
    int E;
    std::vector<Edge<T>> es;
    std::vector<T> d;

    constexpr static T INF = std::numeric_limits<T>::max() / 2;
public:
    BellmanFord(int V, int E, const std::vector<Edge<T>>& es)
        : V{V}, E{E}, es{es} {}

    bool find_negative_loop(int s)
    {
        d.assign(V, INF);
        d[s] = 0;

        int cnt = 0;
        while (true) {
            bool update = false;
            cnt++;
            for (const Edge<T> &e : es) {
                if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = d[e.from] + e.cost;
                    if (cnt == V)
                        return true;

                    update = true;
                }
            }

            if (!update)
                break;
        }

        return false;
    }

    std::vector<T> calc_shortest_path(int s)
    {
        if (find_negative_loop(s))
            return {};

        return d;
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_B)
