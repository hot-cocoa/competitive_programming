#include <vector>

template<class T>
using Graph = std::vector<std::vector<T>>;

class edge {
public:
    int to, weight;
    edge(int to, int weight) : to{to}, weight{weight} {}
};

template<class Weight>
class TreeDiameter {
    Graph<edge> g;
    using Result = std::pair<Weight, int>;

    Result dfs(int par, int curr)
    {
        Result ret(0, curr);
        for (const edge &e : g[curr]) {
            if (e.to == par)
                continue;

            Result t = dfs(curr, e.to);
            t.first += e.weight;
            ret = std::max(ret, t);
        }
        return ret;
    }

public:
    TreeDiameter(Graph<edge> g) : g{g} {}

    Weight tree_diameter()
    {
        Result r = dfs(-1, 0);
        Result t = dfs(-1, r.second);
        return t.first;
    }
};
