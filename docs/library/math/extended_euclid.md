# 拡張ユークリッドの互除法
## 概要
ax + by = gcd(a, b)を満たすx, yを求める。

## 計算量
O(log n)

## コード
```cpp
/**
 * Find (x, y) that satisfieds the following formula.
 * ax + by = gcd(a, b)
 */
int extgcd(int a, int b, int &x, int &y)
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
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_E)
