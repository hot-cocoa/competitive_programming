# 幅優先探索
均一コストの探索を行う。

# 計算量
O(n)

# コード
```cpp
#include <vector>
#include <queue>
#include <limits>

template<class T>
class Edge {
public:
    int to;
    T weight;
    Edge(int to, T weight) : to{to}, weight{weight} {}
};

template<class T>
using Graph = std::vector<std::vector<Edge<T>>>;

template<class T>
class BreadthFirstSearch {
private:
    constexpr static int INF = std::numeric_limits<T>::max() / 2;
    constexpr static T WEIGHT = 1;
    const Graph<T> g;

public:
    BreadthFirstSearch(const Graph<T> &g) : g{g} {}

    std::vector<int> solve(int s)
    {
        std::vector<T> min_weight(g.size(), INF);
        min_weight[s] = 0;

        std::queue<int> q;
        q.push(s);

        const auto update = [&](int from, int to) -> bool {
            if (min_weight[from] + WEIGHT >= min_weight[to])
                return false;

            min_weight[to] = min_weight[from] + WEIGHT;
            return true;
        };

        while (!q.empty()) {
            int curr = q.front(); q.pop();

            for (const auto &e : g[curr])
                if (update(curr, e.to))
                    q.push(e.to);
        }

        return min_weight;
    }
};
```

## 検証
※未検証