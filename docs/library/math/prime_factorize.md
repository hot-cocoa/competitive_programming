# 素因数分解
## 概要
整数nについて素因数分解を実施する。

## 計算量
O(√n)

## コード
```cpp
#include <map>

std::map<int, int> prime_factorize(int n)
{
    std::map<int, int> res;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            ++res[i];
            n /= i;
        }
    }

    if (n != 1)
        res[n] = 1;

    return res;
}
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_A)