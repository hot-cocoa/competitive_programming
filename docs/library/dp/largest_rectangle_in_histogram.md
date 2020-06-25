# 最大長方形inヒストグラム
## 概要
ヒストグラムの中に含まれる長方形の最大面積を求める。

## 計算量
O(N)

## コード
```cpp
#include <vector>

using int64 = long long;

int64 largest_rectangle_in_histogram(
    const std::vector<int>& h
)
{
    int N = h.size();
    int st_size = 0;
    std::vector<int> st(N);
    std::vector<int> L(N), R(N);
    for (int i = 0; i < N; i++) {
        while (st_size > 0 && h[st[st_size - 1]] >= h[i])
            st_size--;

        L[i] = st_size == 0 ? 0 : (st[st_size - 1] + 1);
        st[st_size++] = i;
    }

    st_size = 0;
    for (int i = N - 1; i >= 0; i--) {
        while (st_size > 0 && h[st[st_size - 1]] >= h[i])
            st_size--;

        R[i] = st_size == 0 ? N : st[st_size - 1];
        st[st_size++] = i;
    }

    int64 max_area = 0;
    for (int i = 0; i < N; i++)
        max_area = std::max(max_area, (int64)h[i] * (R[i] - L[i]));

    return max_area;
}
```

## 検証
- [AOJ library](https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/3/DPL_3_C)