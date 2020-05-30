#include <vector>
#include <queue>

struct edge {
    int to, cost;
    edge(int to, int cost) : to{to}, cost{cost} {}
};

using vec = std::vector<edge>;
using Graph = std::vector<vec>;

class MinimumSpanningTree {
private:
    using pii = std::pair<int, int>;

public:
    // prim
    int solve(const Graph &g)
    {
        std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
        pq.emplace(0, 0);

        std::vector<bool> visited(g.size());
        int total_cost = 0;
        while (!pq.empty()) {
            pii p = pq.top(); pq.pop();

            int curr = p.second;
            if (visited[curr])
                continue;

            visited[curr] = true;
            total_cost += p.first;

            for (edge e : g[curr])
                pq.emplace(e.cost, e.to);
        }

        return total_cost;
    }
};
