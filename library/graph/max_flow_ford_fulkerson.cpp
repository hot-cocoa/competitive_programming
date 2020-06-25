#include <vector>

class edge {
public:
    int to, cap, rev;
    edge(int to, int cap, int rev) :
        to{to}, cap{cap}, rev{rev} {}
};

using edges = std::vector<edge>;
using Graph = std::vector<edges>;
constexpr static int INF = 1e9;

class FordFulkerson {
private:
    Graph g;
    std::vector<bool> used;

    void init(int V)
    {
        g.resize(V);
        used.resize(V);
    }

    int dfs(int v, int t, int f)
    {
        if (v == t)
            return f;

        used[v] = true;
        for (edge& e : g[v]) {
            if (!used[e.to] && e.cap > 0) {
                int d = dfs(e.to, t, std::min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

public:
    FordFulkerson(int V) { init(V); }

    void add_edge(int from, int to, int cap)
    {
        g[from].emplace_back(to, cap, g[to].size());
        g[to].emplace_back(from, 0, g[from].size() - 1);
    }

    int max_flow(int s, int t)
    {
        int flow = 0;
        while (true) {
            std::fill(used.begin(), used.end(), false);

            int f = dfs(s, t, INF);
            if (f == 0)
                return flow;

            flow += f;
        }
    }
};
