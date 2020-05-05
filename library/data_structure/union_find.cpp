#include <vector>

class UnionFind {
private:
    int group_count;
    std::vector<int> par, rank, gsize;
public:
    UnionFind(int N)
    {
        group_count = N;

        par.resize(N);
        rank.resize(N);
        gsize.resize(N);

        for (int i = 0; i < N; i++) {
            par[i] = i;
            rank[i] = 0;
            gsize[i] = 1;
        }
    }

    int find(int x)
    {
        if (par[x] == x)
            return x;

        return par[x] = find(par[x]);
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);

        if (x == y)
            return;

        if (rank[x] < rank[y]) {
            par[x] = y;
            gsize[y] += gsize[x];
        }
        else {
            par[y] = x;
            gsize[x] += gsize[y];
            if (rank[x] == rank[y])
                rank[x]++;
        }
        group_count--;
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }

    int size(int x)
    {
        return gsize[find(x)];
    }

    int groups()
    {
        return group_count;
    }
};
