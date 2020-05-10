#include <vector>
#include <queue>

class edge {
public:
    int to, weight;

    edge(int to, int weight) : to{to}, weight{weight} {}
};

using Graph = std::vector<std::vector<edge>>;
constexpr static int INF = 1e9;

class Dijkstra {
private:
    Graph g;

    struct State {
        int v;
        int weight;

        State(int v, int weight) : v{v}, weight{weight} {}

        bool operator < (const State &s) const
        {
            return weight > s.weight;
        }
    };

public:
    Dijkstra(Graph g) : g{g} {}

    std::vector<int> shortest_path(int s)
    {
        std::priority_queue<State> pq;
        pq.emplace(s, 0);

        std::vector<int> weight(g.size(), INF);
        weight[s] = 0;

        const auto &update = [&](const edge &e, const State &s) -> bool
        {
            if (weight[s.v] + e.weight >= weight[e.to])
                return false;

            weight[e.to] = weight[s.v] + e.weight;
            return true;
        };

        while (!pq.empty()) {
            State curr = pq.top(); pq.pop();
            if (weight[curr.v] < curr.weight)
                continue;

            for (const edge &e : g[curr.v])
                if (update(e, curr))
                    pq.emplace(e.to, weight[e.to]);
        }

        return weight;
    }
};
