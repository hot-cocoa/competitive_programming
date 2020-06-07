# 素数判定
## 概要
与えられた整数が素数であるかを判定する。

## 計算量
O(√n)

## コード
```cpp
using int64 = long long;

bool is_prime(int64 n)
{
    if (n < 2)
        return false;

    for (int64 i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;

    return true;
}
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/1/ALDS1_1_C)