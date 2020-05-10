#include <vector>
#include <cmath>

using vec = std::vector<int>;
using Graph = std::vector<vec>;

class LowestCommonAncestor {
private:
    Graph g;
    int root;
    std::vector<int> deg;
    std::vector<int> depth;
    std::vector<std::vector<int>> parent;

    int search_root(int V)
    {
        for (int i = 0; i < V; i++)
            if (deg[i] == 0)
                return i;

        return -1;
    }

    void init(int V)
    {
        deg.assign(V, 0);
        depth.assign(V, 0);
        parent.assign(this->log(V), std::vector<int>(V, 0));
    }

    void build(int V)
    {
        root = search_root(V);
        dfs(root, -1, 0);
        for (int k = 0; k + 1 < this->log(V); k++)
            for (int v = 0; v < V; v++)
                if (parent[k][v] < 0)
                    parent[k + 1][v] = -1;
                else
                    parent[k + 1][v] = parent[k][parent[k][v]];
    }

    void dfs(int v, int par, int d)
    {
        parent[0][v] = par;
        depth[v] = d;
        for (int to : g[v])
            if (to != par)
                dfs(to, v, d + 1);
    }

    int log(int V)
    {
        return log2(V * 2);
    }

public:
    LowestCommonAncestor(Graph g) : g{g} {
        init(g.size());
        build(g.size());
    }

    LowestCommonAncestor(Graph g, std::vector<int> deg) : g{g} {
        init(g.size());
        this->deg = deg;
        build(g.size());
    }

    int lca(int u, int v)
    {
        if (depth[u] > depth[v])
            std::swap(u, v);

        for (int k = 0; k < this->log(g.size()); k++)
            if ((depth[v] - depth[u]) >> k & 1)
                v = parent[k][v];

        if (u == v)
            return u;

        for (int k = this->log(g.size()) - 1; k >= 0; k--)
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }

        return parent[0][u];
    }
};
