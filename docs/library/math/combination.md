# 組み合わせ
## 概要
組み合わせ<sub>n</sub>C<sub>r</sub>を求める。  
MOD版もあり。

## 計算量
O(n)

## コード
```cpp
#include <vector>

using int64 = long long;

class Combination {
private:
    constexpr static int64 DEFAULT = -1;
    std::vector<std::vector<int64>> c;
public:
    Combination(int max)
    {
        c.assign(max + 1, std::vector<int64>(max + 1, DEFAULT));
    }

    // calc nCr
    int64 calc(int n, int r)
    {
        if (n < r)
            return 0LL;

        if (n == r || r == 0)
            return 1LL;

        if (c[n][r] != DEFAULT)
            return c[n][r];

        return c[n][r] = calc(n - 1, r - 1) + calc(n - 1, r);
    }
};

template<int64 MOD>
class ModCombination {
private:
    std::vector<int64> fact;

    void init(int max)
    {
        fact.resize(max + 1);
        fact[0] = 1;
        for (int i = 0; i < max; i++)
            fact[i + 1] = fact[i] * (i + 1) % MOD;
     }

    int64 extgcd(int64 a, int64 b, int64 &x, int64 &y)
    {
        int d = a;
        if (b != 0) {
            d = extgcd(b, a % b, y, x);
            y -= (a / b) * x;
        }
        else
            x = 1, y = 0;

        return d;
    }

    int64 mod_inverse(int64 a, int64 m)
    {
        int64 x, y;
        extgcd(a, m, x, y);
        return (m + x % m) % m;
    }

    int64 mod_fact(int n, int64 p, int64 &e)
    {
        e = 0;
        if (n == 0)
            return 1;

        int res = mod_fact(n / p, p, e);
        e += n / p;
        if (n / p % 2 != 0)
            return res * (p - fact[n % p]) % p;

        return res * fact[n % p] % p;
    }

public:
    ModCombination(int max)
    {
        init(max);
    }

    int64 mod_comb(int n, int k, int64 p)
    {
        if (n < 0 || k < 0 || n < k)
            return 0;

        int64 e1, e2, e3;
        int64 a1 = mod_fact(n, p, e1);
        int64 a2 = mod_fact(k, p, e2);
        int64 a3 = mod_fact(n - k, p, e3);
        if (e1 > e2 + e3)
            return 0;

        return a1 * mod_inverse(a2 * a3 % p, p) % p;
    }
};
```

## 検証
- [Atcoder ABC057D](https://atcoder.jp/contests/abc057/tasks/abc057_d)：通常版
- [AtCoder ABC151E](https://atcoder.jp/contests/abc151/tasks/abc151_e)：MOD版
