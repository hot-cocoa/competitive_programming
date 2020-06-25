#include <vector>

using Graph = std::vector<std::vector<int>>;

class EulerTour {
private:
    Graph g;
    std::vector<int> l, r;

    void dfs(int v, int p, int& k)
    {
        l[v] = k++;
        for (int to : g[v])
            if (to != p)
                dfs(to, v, k);

        r[v] = k;
    }

    void init(int V)
    {
        l.resize(V);
        r.resize(V);
    }

    void build()
    {
        int k = 0;
        dfs(0, -1, k);
    }

public:
    EulerTour(const Graph& g) : g{g} {
        init(g.size());
        build();
    }

    int left(int v)
    {
        return l[v];
    }

    int right(int v)
    {
        return r[v];
    }
};
