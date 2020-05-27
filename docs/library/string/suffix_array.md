# 接尾辞配列
## 概要
接尾辞配列を用いることで文字列の検索を高速に行う。  
接尾辞配列は、ある文字列に対してすべての接尾辞を辞書順ソートしたものである。

## 計算量
O(n log<sup>2</sup>n)

## コード
```cpp
#include <string>
#include <vector>
#include <algorithm>

class SuffixArray {
private:
    int N;
    std::string s;
    std::vector<int> sa;

    void build(const std::string &s)
    {
        N = s.size();
        sa.resize(N + 1);

        std::vector<int> rank(N + 1);
        for (int i = 0; i <= N; i++) {
            sa[i] = i;
            rank[i] = (i < N ? s[i] : -1);
        }

        for (int k = 1; k <= N; k *= 2) {
            const auto comp = [&](int i, int j) -> bool {
                if (rank[i] != rank[j])
                    return rank[i] < rank[j];

                int ri = (i + k <= N ? rank[i + k] : -1);
                int rj = (j + k <= N ? rank[j + k] : -1);
                return ri < rj;
            };

            std::sort(sa.begin(), sa.end(), comp);

            std::vector<int> tmp(N + 1);
            tmp[sa[0]] = 0;
            for (int i = 1; i <= N; i++)
                tmp[sa[i]] = tmp[sa[i - 1]] + comp(sa[i - 1], sa[i]);

            for (int i = 0; i <= N; i++)
                rank[i] = tmp[i];
        }
    }

public:
    SuffixArray(const std::string &s) : s{s} {
        build(s);
    }

    bool contain(const std::string &t)
    {
        int l = 0, r = N;
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (s.compare(sa[mid], t.size(), t) < 0)
                l = mid;
            else
                r = mid;
        }
        return s.compare(sa[r], t.size(), t) == 0;
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_D)