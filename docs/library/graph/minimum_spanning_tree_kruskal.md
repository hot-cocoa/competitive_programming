# 最小全域木(クラスカル法)
## 概要
グラフの最小全域木を求める。  
最小全域木とは、グラフの全域木のうち含まれる辺の重みの総和が最小となる。

## 計算量
O(E log V)

## コード
```cpp
#include "../data_structure/union_find.cpp"
#include <algorithm>

template<class T>
class Edge {
public:
    int u, v;
    T weight;
    Edge(int u, int v, T weight) : u{u}, v{v}, weight{weight} {}

    bool operator < (const Edge<T>& e)
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
        for (const auto& [u, v, weight] : es)
            if (!uf.same(u, v)) {
                uf.unite(u, v);
                total_weight += weight;
            }

        return total_weight;
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/2/GRL_2_A)