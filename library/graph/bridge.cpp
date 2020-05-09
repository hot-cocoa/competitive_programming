#include <iostream>
#include <vector>

using vec = std::vector<int>;
using Graph = std::vector<vec>;

constexpr static int INF = 1e9;

class Bridge {
private:
    Graph g;
    vec ord, low;
    std::vector<std::pair<int, int>> bridge;

    void init()
    {
        int V = g.size();
        ord.assign(V, -1);
        low.assign(V, INF);
    }

    void dfs(int v, int prev, int &k)
    {
        ord[v] = low[v] = k++;
        for (int to : g[v]) {
            if (to == prev)
                continue;

            if (ord[to] == -1) {
                dfs(to, v, k);
                low[v] = std::min(low[v], low[to]);
                if (ord[v] < low[to]) {
                    bridge.emplace_back(
                        std::min(v, to),
                        std::max(v, to)
                    );
                }
            }
            low[v] = std::min(low[v], ord[to]);
        }
    }

public:
    Bridge(Graph g) : g{g} {
        init();
    }

    void dfs(int v, int &k)
    {
        dfs(v, -1, k);
    }

    std::vector<std::pair<int, int>> bridges()
    {
        return bridge;
    }
};
