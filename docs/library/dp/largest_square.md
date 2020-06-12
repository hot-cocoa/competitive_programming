# 最大正方形
## 概要
N&times;Mの0と1で表された2次元配列から最大の正方形の面積を求める。  
ただし、  
0は正方形の一部として使用できるが、  正方形の一部に1が含まれてはいけない。

## 計算量
O(NM)

## コード
```cpp
#include <vector>

using Vec = std::vector<int>;
using Mat = std::vector<Vec>;

int largest_square(const Mat &m)
{
    int N = m.size(), M = m[0].size();
    Mat dp(N, Vec(M));
    int max = 0;
    for (int i = 0; i < N; i++) {
        dp[i][0] = (m[i][0] == 0);
        max = std::max(max, dp[i][0]);
    }
    for (int i = 0; i < M; i++) {
        dp[0][i] = (m[0][i] == 0);
        max = std::max(max, dp[0][i]);
    }

    for (int i = 1; i < N; i++)
        for (int j = 1; j < M; j++)
            if (m[i][j] == 1)
                dp[i][j] = 0;
            else {
                dp[i][j] =
                    std::min(dp[i - 1][j - 1],
                             std::min(dp[i - 1][j], dp[i][j - 1])) + 1;

                max = std::max(max, dp[i][j]);
            }

    return max * max;
}
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/3/DPL_3_A)