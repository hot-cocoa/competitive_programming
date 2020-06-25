#include <vector>

template<class T>
using Graph = std::vector<std::vector<T>>;

class edge {
public:
    int to, weight;
    edge(int to, int weight) : to{to}, weight{weight} {}
};

template<class Weight>
class TreeHeight {
    Graph<edge> g;

    int dfs(const Graph<edge>& t, int u, int v)
    {
        if (t[u][v].weight >= 0)
            return t[u][v].weight;

        t[u][v].weight = g[u][v].weight;
        int w = t[u][v].to;
        for (int i = 0; i < (int)t[w].size(); i++) {
            if (t[w][i].to == u)
                continue;

            t[u][v].weight =
                std::max(t[u][v].weight, dfs(t, w, i) + g[u][v].weight);
        }
        return t[u][v].weight;
    }

public:
    TreeHeight(const Graph<edge>& g) : g{g} {}

    std::vector<Weight> heights()
    {
        const int N = g.size();
        Graph<edge> t(g);
        for (int i = 0; i < N; i++)
            for (edge& e : t[i])
                e.weight = -1;

        for (int i = 0; i < N; i++)
            for (int j = 0; j < (int)t[i].size(); j++)
                if (t[i][j].weight < 0)
                    t[i][j].weight = dfs(t, i, j);

        std::vector<Weight> heights(N);
        for (int i = 0; i < N; i++) {
            int max_weight = 0;
            for (const edge& e : t[i])
                max_weight = std::max(max_weight, e.weight);

            heights[i] = max_weight;
        }
        return heights;
    }
};
