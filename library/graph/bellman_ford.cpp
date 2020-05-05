#include <vector>

constexpr static int INF = 1e9;

struct Edge {
    int from;
    int to;
    int cost;

    Edge(int from, int to, int cost)
        : from{from}, to{to}, cost{cost} {}
};

class BellmanFord {
private:
    int V;
    int E;
    std::vector<Edge> es;
    std::vector<int> d;

public:
    BellmanFord(int V, int E, std::vector<Edge> es)
        : V{V}, E{E}, es{es} {}

    bool find_negative_loop(int s)
    {
        d.assign(V, INF);
        d[s] = 0;

        int cnt = 0;
        while (true) {
            bool update = false;
            cnt++;
            for (const Edge &e : es) {
                if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost) {
                    d[e.to] = d[e.from] + e.cost;
                    if (cnt == V)
                        return true;

                    update = true;
                }
            }

            if (!update)
                break;
        }

        return false;
    }

    std::vector<int> calc_shortest_path(int s)
    {
        if (find_negative_loop(s))
            return {};

        return d;
    }
};
