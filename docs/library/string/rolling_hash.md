# ローリングハッシュ
## 概要
ハッシュ値を使用することで文字列の一致判定を高速に行う。

## 計算量
- 構築：O(n)
- ハッシュ値の参照：O(1)

## コード
```cpp
#include <string>
#include <vector>

using ull = unsigned long long;
constexpr ull B = 1000000007UL;

class RollingHash {
private:
    std::vector<ull> h;
    std::vector<ull> p;

    void build(const std::string &s)
    {
        int size = s.size();
        h.resize(size + 1);
        p.resize(size + 1);
        p[0] = 1;

        for (int i = 0; i < size; i++) {
            h[i + 1] = h[i] * B + s[i];
            p[i + 1] = p[i] * B;
        }
    }

public:
    RollingHash(const std::string &s)
    {
        build(s);
    }

    // calculate hash(closed section[l, r])
    ull hash(int l, int r)
    {
        return h[r + 1] - h[l] * p[r - l + 1];
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/14/ALDS1_14_B)