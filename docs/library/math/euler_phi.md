# オイラーのφ関数
## 概要
正の整数nに対して、nと互いに素である1以上n以下の自然数の個数を求める。

## 計算量
O(√n)

## コード
```cpp
int euler_phi(int n)
{
    if (n == 0)
        return 0;

    int count_disjoint = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            count_disjoint -= count_disjoint / i;
            while (n % i == 0)
                n /= i;
        }
    }

    if (n > 1)
        count_disjoint -= count_disjoint / n;

    return count_disjoint;
}

```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/1/NTL_1_D)