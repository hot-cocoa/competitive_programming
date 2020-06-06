# 幅優先探索
均一コストの探索を行う。

# 計算量
O(n)

# コード
```cpp
#include <vector>
#include <queue>
#include <limits>

class Edge {
public:
    int to, weight;
    Edge(int to, int weight) : to{to}, weight{weight} {}
};

using Edges = std::vector<Edge>;
using Graph = std::vector<Edges>;

class BreadthFirstSearch {
private:
    constexpr static int INF = std::numeric_limits<int>::max() / 2;
    const Graph g;

public:
    BreadthFirstSearch(const Graph &g) : g{g} {}

    std::vector<int> solve(int s)
    {
        std::vector<int> min_weight(g.size(), INF);
        min_weight[s] = 0;

        std::queue<int> q;
        q.push(s);

        const auto update = [&](int from, int to) -> bool {
            if (min_weight[from] + 1 >= min_weight[to])
                return false;

            min_weight[to] = min_weight[from] + 1;
            return true;
        };

        while (!q.empty()) {
            int curr = q.front(); q.pop();

            for (const Edge &e : g[curr])
                if (update(curr, e.to))
                    q.push(e.to);
        }

        return min_weight;
    }
};
```

## 検証
※未検証