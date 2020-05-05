#include <iostream>
#include <vector>

class StronglyConnectedComponents {
private:
    using vec = std::vector<int>;
    using Graph = std::vector<vec>;

    Graph g, rg;
    vec vs;
    vec cmp;
    std::vector<bool> used;

    void dfs(int v)
    {
        used[v] = true;
        for (int u : g[v]) {
            if (!used[u])
                dfs(u);
        }
        vs.emplace_back(v);
    }

    void rdfs(int v, int k)
    {
        used[v] = true;
        cmp[v] = k;
        for (int u : rg[v]) {
            if (!used[u])
                rdfs(u, k);
        }
    }

public:
    StronglyConnectedComponents(int V)
    {
        g.resize(V);
        rg.resize(V);
        cmp.resize(V);
        used.resize(V);
    }

    void add_edge(int from, int to)
    {
        g[from].emplace_back(to);
        rg[to].emplace_back(from);
    }

    int scc()
    {
        std::fill(used.begin(), used.end(), false);
        vs.clear();
        for (int v = 0; v < (int)g.size(); v++) {
            if (!used[v])
                dfs(v);
        }

        std::fill(used.begin(), used.end(), false);
        int k = 0;
        for (int i = (int)vs.size() - 1; i >= 0; i--) {
            if (!used[vs[i]])
                rdfs(vs[i], k++);
        }

        return k;
    }

    bool same(int u, int v)
    {
        return cmp[u] == cmp[v];
    }
};
