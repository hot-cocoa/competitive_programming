#include <vector>
#include <queue>

template<class T>
struct edge {
    int to;
    T weight;
    edge(int to, T weight) : to{to}, weight{weight} {}
};

template<class T>
using Graph = std::vector<std::vector<edge<T>>>;

template<class T>
class MinimumSpanningTree {
private:
    using State = std::pair<T, int>;

public:
    T solve(const Graph<T>& g)
    {
        std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
        pq.emplace(0, 0);

        std::vector<bool> visited(g.size());
        T total_weight = 0;
        while (!pq.empty()) {
            auto [weight, curr] = pq.top(); pq.pop();
            if (visited[curr])
                continue;

            visited[curr] = true;
            total_weight += weight;

            for (const auto& e : g[curr])
                pq.emplace(e.weight, e.to);
        }

        return total_weight;
    }
};
