# 最長増加部分列
## 概要
数列aの最大増加部分列を求める。  
増加部分列とは、0&le;i<sub>0</sub>&lt;i<sub>1</sub>&lt;...&lt;i<sub>k</sub>&lt;nかつa<sub>i<sub>0</sub></sub>&lt;a<sub>i<sub>1</sub></sub>&lt;...&lt;a<sub>i<sub>k</sub></sub>を満たす部分列a<sub>i<sub>0</sub></sub>,a<sub>i<sub>1</sub></sub>,...,a<sub>i<sub>k</sub></sub>である。

## 計算量
O(N log N)

## コード
```cpp
#include <vector>

using int64 = long long;
constexpr static int64 INF = 1LL << 55;

int longest_increasing_subsequence(
    const std::vector<int>& a
)
{
    int N = a.size();
    std::vector<int64> dp(N, INF);
    for (int i = 0; i < N; i++)
        *lower_bound(dp.begin(), dp.end(), a[i]) = a[i];

    return lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
}
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/1/DPL_1_D)