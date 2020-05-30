#include "../data_structure/union_find.cpp"
#include <algorithm>

template<class T>
class Edge {
public:
    int u, v;
    T weight;
    Edge(int u, int v, T weight) : u{u}, v{v}, weight{weight} {}

    bool operator < (const Edge<T> &e)
    {
        return weight < e.weight;
    }
};

template<class T>
class MinimumSpanningTree {
private:
    std::vector<Edge<T>> es;
public:
    void add_edge(int u, int v, T weight)
    {
        es.emplace_back(u, v, weight);
    }

    T solve(int V) {
        UnionFind uf(V);
        std::sort(es.begin(), es.end());
        T total_weight = 0;
        for (const Edge<T> &e : es)
            if (!uf.same(e.u, e.v)) {
                uf.unite(e.u, e.v);
                total_weight += e.weight;
            }

        return total_weight;
    }
};