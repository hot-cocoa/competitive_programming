# 約数
## 概要
n以下の約数を列挙する。

## 計算量
O(√n)

## コード
```cpp
#include <vector>

// Not Verify!
std::vector<int> divisor(int N)
{
    std::vector<int> divisors;
    for (int i = 1; i * i <= N; i++)
        if (N % i == 0) {
            divisors.emplace_back(i);
            if (i != N / i)
                divisors.emplace_back(N / i);
        }

    return divisors;
}
```

## 検証
※未検証