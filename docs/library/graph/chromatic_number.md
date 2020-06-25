# 彩色数
## 概要
グラフの彩色数を求める。  
彩色数とは、隣接する頂点同士が同じ色にならないように全頂点に色を付けるときに必要な最小色数である。

## 計算量
O(n 2^n)

## コード
```cpp
#include <vector>

// Adjacency matrix
using Matrix = std::vector<std::vector<bool>>;

class ChromaticNumber {
private:
    Matrix con; // 1:connected, 0:unconnected
    std::vector<int> I; // # of independence subset

    void build()
    {
        int N = con.size();
        std::vector<int> es(N, 0);
        for (int i = 0; i < N; i++) {
            int bit = 0;
            for (int j = 0; j < N; j++)
                if (con[i][j])
                    bit |= 1 << j;

            es[i] = bit;
        }

        I.assign(1 << N, 0);
        I[0] = 1;
        for (int S = 1; S < (1 << N); S++) {
            int v = 0;
            while (!(S >> v & 1))
                v++;

            I[S] = I[S - (1 << v)] + I[S & ~es[v]];
        }
    }

    int mod_pow(int x, int n, int mod)
    {
        if (n == 0)
            return 1;

        int res = mod_pow(x * x % mod, n / 2, mod);
        if (n & 1)
            res = res * x % mod;

        return res;
    }

    bool c(int N, int K)
    {
        int g = 0;
        constexpr static int MOD = 10009;
        for (int i = 0; i < (1 << N); i++)
            if (__builtin_popcount(i) % 2 == 0)
                g += mod_pow(I[i], K, MOD);
            else
                g -= mod_pow(I[i], K, MOD);

        return (g % MOD + MOD) % MOD != 0;
    }

public:
    ChromaticNumber(const Matrix& con) : con{con} {
        build();
    }

    int solve()
    {
        int N = con.size();
        int l = 0, r = N;
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (c(N, mid))
                r = mid;
            else
                l = mid;
        }
        return r;
    }
};
```

## 検証
※未検証