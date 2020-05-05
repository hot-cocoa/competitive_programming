#include <vector>

class RMQ {
private:
    int N;
    std::vector<int> dat;
    constexpr static int INF = 1<<25;

public:
    RMQ(int N_)
    {
        N = 1;
        while (N < N_)
            N *= 2;

        dat.assign(2 * N - 1, INF);
    }

    void update(int k, int a)
    {
        k += N - 1;
        dat[k] = a;
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = std::min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    int query(int a, int b, int k, int l, int r)
    {
        if (r <= a || b <= l)
            return INF;

        if (a <= l && r <= b)
            return dat[k];

        int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
        int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return std::min(vl, vr);
    }

    /**
     * minimum value [l, r]
     */
    int query(int l, int r)
    {
        return query(l, r + 1, 0, 0, N);
    }
};
