# 最小公倍数
## 概要
2個の整数の最小公倍数を求める。

## 計算量
O(log n)

## コード
```cpp
using int64 = long long;

int64 gcd(int64 a, int64 b)
{
    if (b == 0)
        return a;

    return gcd(b, a % b);
}

int64 lcm(int64 a, int64 b)
{
    return a / gcd(a, b) * b;
}
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_C)
