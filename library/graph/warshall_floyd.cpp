#include <vector>
#include <climits>

using Graph = std::vector<std::vector<int>>;
constexpr static int INF = INT_MAX;

class WarshallFloyd {
    Graph g;

    void init(int V)
    {
        for (int i = 0; i < V; i++)
            g[i][i] = 0;
    }

public:
    WarshallFloyd(const Graph& g) : g{g} { init(g.size()); }

    Graph shortest_path_all()
    {
        Graph d = g;
        int V = g.size();
        for (int k = 0; k < V; k++)
            for (int i = 0; i < V; i++)
                for (int j = 0; j < V; j++) {
                    if (d[i][k] == INF || d[k][j] == INF)
                        continue;

                    d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
                }

        return d;
    }

    bool find_negative_cycle()
    {
        Graph d = shortest_path_all();
        for (int i = 0; i < (int)d.size(); i++)
            if (d[i][i] < 0)
                return true;

        return false;
    }
};
