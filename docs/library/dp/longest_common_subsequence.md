# 最長共通部分列
## 概要
2つの文字列について、最長の共通部分列を求める。

## 計算量
O(NM)

## コード
```cpp
#include <vector>
#include <string>
#include <algorithm>

std::string restore(
    const std::vector<std::vector<int>> &route,
    const std::string &s,
    int len1, int len2
)
{
    std::string com_sub;
    for (int i = len1, j = len2; i > 0 && j > 0; )
        if (route[i][j] == 0) {
            com_sub += s[i - 1];
            i--; j--;
        }
        else if (route[i][j] == 1)
            i--;
        else
            j--;

    std::reverse(com_sub.begin(), com_sub.end());
    return com_sub;
}

std::pair<int, std::string> longest_common_subsequence(
    const std::string s1,
    const std::string s2
)
{
    int N = s1.size();
    int M = s2.size();
    std::vector<std::vector<int>> dp(N + 1, std::vector<int>(M + 1));
    std::vector<std::vector<int>> route(N + 1, std::vector<int>(M + 1));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (s1[i] == s2[j]) {
                dp[i + 1][j + 1] = dp[i][j] + 1;
                route[i + 1][j + 1] = 0;
            }
            else {
                if (dp[i][j + 1] < dp[i + 1][j]) {
                    dp[i + 1][j + 1] = dp[i + 1][j];
                    route[i + 1][j + 1] = -1;
                }
                else {
                    dp[i + 1][j + 1] = dp[i][j + 1];
                    route[i + 1][j + 1] = 1;
                }
            }

    auto com_sub = restore(route, s1, N, M);
    return {dp[N][M], com_sub};
}
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/10/ALDS1_10_C)