#include <vector>
#include <queue>

class edge {
public:
    int to, cap, rev;
    edge(int to, int cap, int rev) :
        to{to}, cap{cap}, rev{rev} {}
};

using edges = std::vector<edge>;
using Graph = std::vector<edges>;
constexpr static int INF = 1e9;

class Dinic {
private:
    Graph g;
    std::vector<int> level;
    std::vector<int> iter;

    void init(int V)
    {
        g.resize(V);
        level.resize(V);
        iter.resize(V);
    }

    void bfs(int s)
    {
        std::fill(level.begin(), level.end(), -1);
        level[s] = 0;

        std::queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (edge &e : g[v])
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
        }
    }

    int dfs(int v, int t, int f)
    {
        if (v == t)
            return f;

        for (int &i = iter[v]; i < (int)g[v].size(); i++) {
            edge &e = g[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
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
    Dinic(int V) { init(V); }

    void add_edge(int from, int to, int cap)
    {
        g[from].emplace_back(to, cap, g[to].size());
        g[to].emplace_back(from, 0, g[from].size() - 1);
    }

    int max_flow(int s, int t)
    {
        int flow = 0;
        while (true) {
            bfs(s);
            if (level[t] < 0)
                return flow;

            std::fill(iter.begin(), iter.end(), 0);
            int f;
            while ((f = dfs(s, t, INF)) > 0)
                flow += f;
        }
    }
};
