# トポロジカルソート
## 概要
DAGに対して[トポロジカルソート](https://en.wikipedia.org/wiki/Topological_sorting)を行う。

## 計算量
O(V + E)

## コード
```cpp
#include <vector>
#include <algorithm>

using vec = std::vector<int>;
using Graph = std::vector<vec>;

class TopologicalSort {
private:
    enum class State {
        UNCHECK,
        CHECKING,
        CHECKED
    };

    Graph g;
    std::vector<State> color;
    vec order;

    void init(int V)
    {
        color.resize(V);
    }

    bool visit(int v)
    {
        color[v] = State::CHECKING;
        for (int to : g[v]) {
            if (color[to] == State::CHECKED)
                continue;

            if (color[to] == State::CHECKING)
                return false;

            if (!visit(to))
                return false;
        }
        order.emplace_back(v);
        color[v] = State::CHECKED;
        return true;
    }

    bool is_sorted()
    {
        order.clear();
        std::fill(color.begin(), color.end(), State::UNCHECK);
        for (int i = 0; i < (int)g.size(); i++)
            if (color[i] == State::UNCHECK && !visit(i))
                return false;

        std::reverse(order.begin(), order.end());
        return true;
    }

public:
    TopologicalSort(const Graph& g) : g{g} {
        init(g.size());
    }

    /*
     * Constraints
     * ・DAG
     * ・no parallel edges
     * ・no self loops
     */
    vec sort()
    {
        return is_sorted() ? order : vec{};
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/4/GRL_4_B)