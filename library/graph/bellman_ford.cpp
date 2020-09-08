#include <vector>
#include <limits>

template<class T>
struct Edge {
    int from;
    int to;
    T weight;

    Edge(int from, int to, T weight)
        : from{from}, to{to}, weight{weight} {}
};

template<class T>
using Edges = std::vector<Edge<T>>;

template<class T>
class BellmanFord {
private:
    int V;
    int E;
    Edges<T> es;
    std::vector<T> weight;

    constexpr static T INF = std::numeric_limits<T>::max() / 2;
public:
    BellmanFord(int V, int E, const Edges<T>& es)
        : V{V}, E{E}, es{es} {}

    bool find_negative_loop(int s)
    {
        weight.assign(V, INF);
        weight[s] = 0;

        int used_cnt = 0;
        bool updated;
        do {
            updated = false;
            used_cnt++;
            for (const auto& [from, to, w] : es) {
                if (weight[from] != INF &&
                    weight[to] > weight[from] + w) {

                    weight[to] = weight[from] + w;
                    if (used_cnt == V)
                        return true;

                    updated = true;
                }
            }
        } while (updated);

        return false;
    }

    std::vector<T> shortest_path(int s)
    {
        if (find_negative_loop(s))
            return {};

        return weight;
    }

    bool is_updated(T w)
    {
        return w != INF;
    }
};
