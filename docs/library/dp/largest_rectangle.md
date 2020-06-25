# 最大正方形
## 概要
N&times;Mの0と1で表された2次元配列から最大の長方形の面積を求める。  
ただし、  
0は長方形の一部として使用できるが、長方形の一部に1が含まれてはいけない。

## 計算量
O(NM)

## コード
```cpp
#include <vector>
#include <stack>

using Vec = std::vector<int>;
using Mat = std::vector<Vec>;

int largest_rectangle(const Mat& m)
{
    int N = m.size(), M = m[0].size();
    Vec dp(M + 1, 0);
    int max_area = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            dp[j] = (m[i][j] == 0 ? dp[j] + 1 : 0);

        std::stack<std::pair<int, int>> st;
        st.emplace(0, M);
        for (int j = 0; j <= M; j++) {
            int k = j;
            while (dp[j] < st.top().first) {
                k = st.top().second;
                max_area = std::max(max_area, st.top().first * (j - k));
                st.pop();
            }
            if (st.top().first < dp[j])
                st.emplace(dp[j], k);
        }
    }
    return max_area;
}
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/3/DPL_3_B)