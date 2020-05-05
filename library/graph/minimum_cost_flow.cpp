#include <vector>
#include <queue>

struct edge {
    int to, cap, cost, rev;
    edge(int to, int cap, int cost, int rev) :
        to{to}, cap{cap}, cost{cost}, rev{rev} {}
};

class MinimumCostFlow {
private:
    using vec = std::vector<edge>;
    using Graph = std::vector<vec>;
    using pii = std::pair<int, int>;
    const int INF = (1 << 29);
    Graph g;

public:
    MinimumCostFlow(int V)
    {
        g.resize(V);
    }

    void add_edge(int from, int to, int cap, int cost)
    {
        g[from].emplace_back(to, cap, cost, g[to].size());
        g[to].emplace_back(from, 0, -cost, g[from].size() - 1);
    }

    int primal_dual(int s, int t, int f)
    {
        int res = 0;
        while (f > 0) {
            // (dist, node)
            std::priority_queue<pii, std::vector<pii>, std::greater<pii>> que;
            que.emplace(0, s);

            std::vector<int> h(g.size());
            std::vector<int> prevv(g.size()), preve(g.size());
            std::vector<int> dist(g.size(), INF);
            dist[s] = 0;

            while (!que.empty()) {
                pii p = que.top(); que.pop();
                int v = p.second;

                if (dist[v] < p.first)
                    continue;

                for (int i = 0; i < (int)g[v].size(); i++) {
                    edge &e = g[v][i];
                    int ndist = dist[v] + e.cost + h[v] - h[e.to];
                    if (e.cap > 0 && dist[e.to] > ndist) {
                        dist[e.to] = ndist;
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        que.emplace(dist[e.to], e.to);
                    }
                }
            }

            if (dist[t] == INF)
                return -1;

            for (int v = 0; v < (int)g.size(); v++)
                h[v] += dist[v];

            int d = f;
            for (int v = t; v != s; v = prevv[v])
                d = std::min(d, g[prevv[v]][preve[v]].cap);

            f -= d;
            res += d * h[t];
            for (int v = t; v != s; v = prevv[v]) {
                edge &e = g[prevv[v]][preve[v]];
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
        }

        return res;
    }
};
