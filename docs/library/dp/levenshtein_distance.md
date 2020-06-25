# レーベンシュタイン距離(編集距離)
## 概要
2つの文字列のレーベンシュタイン距離を求める。  
レーベンシュタイン距離とは、ある文字列に対して以下の3つの操作を繰り返し別の文字列に変形するための最小操作回数である。
- 挿入：文字列に1文字挿入する
- 削除：文字列から1文字削除する
- 置換：文字列の1文字を別の文字に置換する

## 計算量
O(NM)

## コード
```cpp
#include <vector>
#include <string>

template<class T>
T levenshtein_distance(
    const std::string& s, const std::string& t,
    T ins_cost = 1, T rm_cost = 1, T repl_cost = 1
)
{
    int N = s.size();
    int M = t.size();

    std::vector<std::vector<T>> dp(N + 1, std::vector<T>(M + 1));
    for (int i = 0; i <= N; i++)
        dp[i][0] = i * ins_cost;

    for (int i = 0; i <= M; i++)
        dp[0][i] = i * rm_cost;

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= M; j++)
            dp[i][j] =
                std::min(
                    std::min(
                        dp[i - 1][j] + ins_cost,
                        dp[i][j - 1] + rm_cost
                    ),
                    dp[i - 1][j - 1] + repl_cost * !(s[i - 1] == t[j - 1])
                );

    return dp[N][M];
}
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/1/DPL_1_E)