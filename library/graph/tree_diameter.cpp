#include <vector>

template<class T>
using Graph = std::vector<std::vector<T>>;

template<class T>
class Edge {
public:
    int to;
    T weight;
    Edge(int to, T weight) : to{to}, weight{weight} {}
};

template<class Weight>
class TreeDiameter {
    Graph<Edge<Weight>> g;
    using Result = std::pair<Weight, int>;

    Result dfs(int par, int curr)
    {
        Result ret(0, curr);
        for (const auto& [to, weight] : g[curr]) {
            if (to == par)
                continue;

            Result t = dfs(curr, to);
            t.first += weight;
            ret = std::max(ret, t);
        }
        return ret;
    }

public:
    TreeDiameter(const Graph<Edge<Weight>>& g) : g{g} {}

    Weight solve()
    {
        Result r = dfs(-1, 0);
        Result t = dfs(-1, r.second);
        return t.first;
    }
};
