#include <vector>

using vec = std::vector<int>;
using Graph = std::vector<vec>;

class BipartiteMatching {
private:
    Graph g;
    std::vector<int> match;
    std::vector<bool> used;

    void init(int V)
    {
        g.resize(V);
        match.resize(V);
        used.resize(V);
    }

    bool dfs(int v)
    {
        used[v] = true;
        for (int u : g[v]) {
            int w = match[u];
            if (w < 0 || (!used[w] && dfs(w))) {
                match[v] = u;
                match[u] = v;
                return true;
            }
        }
        return false;
    }

public:
    BipartiteMatching(int V) {
        init(V);
    }

    void add_edge(int u, int v)
    {
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    int bipartite_matching()
    {
        int match_count = 0;
        std::fill(match.begin(), match.end(), -1);
        for (int v = 0; v < (int)g.size(); v++)
            if (match[v] < 0) {
                std::fill(used.begin(), used.end(), false);
                if (dfs(v))
                    match_count++;
            }

        return match_count;
    }
};
