#include <vector>
#include <limits>

template<class T>
class Edge {
public:
    int to;
    T weight;

    Edge(int to, T weight) : to{to}, weight{weight} {}
};

template<class T>
using Graph = std::vector<std::vector<Edge<T>>>;

template<class T>
class TravelingSalesman {
private:
    constexpr static T INF = std::numeric_limits<T>::max() / 2;
    int V;
    Graph<T> g;
    std::vector<std::vector<T>> dp;

    T rec(int S, int v)
    {
        if (dp[S][v] != NOT_FOUND)
            return dp[S][v];

        if (S == (1 << V) - 1 && v == 0)
            return dp[S][v] = 0;

        T min = INF;
        for (const auto& [to, weight] : g[v])
            if (!(S >> to & 1))
                min = std::min(
                          min,
                          rec(S | (1 << to), to) + weight
                      );

        return dp[S][v] = min;
    }

public:
    constexpr static T NOT_FOUND = -1;

    TravelingSalesman(int V) : V{V} { g.resize(V); }
    TravelingSalesman(const Graph<T>& g) : g{g} { V = g.size(); }

    void add_edge(int src, int dst, T weight)
    {
        g[src].emplace_back(dst, weight);
    }

    T solve()
    {
        dp.assign(1 << V, std::vector<T>(V, NOT_FOUND));

        T min_weight = rec(0, 0);
        return (min_weight == INF ? NOT_FOUND : min_weight);
    }
};