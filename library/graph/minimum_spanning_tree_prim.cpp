#include <vector>
#include <queue>

template<class T>
struct edge {
    int to;
    T cost;
    edge(int to, T cost) : to{to}, cost{cost} {}
};

template<class T>
using Graph = std::vector<std::vector<edge<T>>>;

template<class T>
class MinimumSpanningTree {
private:
    using State = std::pair<T, int>;

public:
    // prim
    T solve(const Graph<T> &g)
    {
        std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
        pq.emplace(0, 0);

        std::vector<bool> visited(g.size());
        T total_cost = 0;
        while (!pq.empty()) {
            State p = pq.top(); pq.pop();

            int curr = p.second;
            if (visited[curr])
                continue;

            visited[curr] = true;
            total_cost += p.first;

            for (auto e : g[curr])
                pq.emplace(e.cost, e.to);
        }

        return total_cost;
    }
};
