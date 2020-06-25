#include <vector>
#include <queue>
#include <limits>

template<class T>
class edge {
public:
    int to;
    T weight;

    edge(int to, T weight) : to{to}, weight{weight} {}
};

template<class T>
using Graph = std::vector<std::vector<edge<T>>>;

template<class T>
class Dijkstra {
private:
    Graph<T> g;
    constexpr static T INF = std::numeric_limits<T>::max() / 2;

    struct State {
        int v;
        T weight;

        State(int v, T weight) : v{v}, weight{weight} {}

        bool operator < (const State& s) const
        {
            return weight > s.weight;
        }
    };

public:
    Dijkstra(const Graph<T>& g) : g{g} {}

    std::vector<T> shortest_path(int s)
    {
        std::priority_queue<State> pq;
        pq.emplace(s, 0);

        std::vector<T> weight(g.size(), INF);
        weight[s] = 0;

        const auto &update = [&](const edge<T>& e, const State& s) -> bool
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

            for (const edge<T> &e : g[curr.v])
                if (update(e, curr))
                    pq.emplace(e.to, weight[e.to]);
        }

        return weight;
    }
};
