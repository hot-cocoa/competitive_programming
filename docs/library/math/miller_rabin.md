# ミラーラビン素数判定法
## 概要
与えられた数が素数であるかを判定する。

## 計算量
O(k log^3 n)

## コード
```cpp
#include <vector>

template<class T>
class MillerRabin {
private:
    T mod_pow(T x, T n, T mod)
    {
        if (n == 0)
            return 1;

        T res = mod_pow(x * x % mod, n / 2, mod);
        if (n & 1)
            res = res * x % mod;

        return res;
    }

    T mod_mul(T a, T b, T mod)
    {
        if (b == 0)
            return 0;

        T res = mod_mul((a + a) % mod, b / 2, mod);
        if (b & 1)
            res = (res + a) % mod;

        return res;
    }

public:
    bool is_prime(T N)
    {
        if (N == 2)
            return true;

        if (N % 2 == 0 || N <= 1)
            return false;

        const std::vector<int> a = {2, 3, 5, 7, 11, 13, 17, -1};
        T s = 0, d = N - 1;
        while (d % 2 == 0) {
            s++;
            d >>= 1;
        }
        for (int i = 0; a[i] != -1 && a[i] < N; i++) {
            T x = mod_pow(a[i], d, N);
            if (x != 1) {
                T j;
                for (j = 0; j < s; j++) {
                    if (x == N - 1)
                        break;

                    x = mod_mul(x, x, N);
                }
                if (j == s)
                    return false;
            }
        }
        return true;
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/1/ALDS1_1_C)