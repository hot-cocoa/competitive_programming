# スターンブロコット木
## 概要
分母分子がnより小さい既約分数を列挙する。

## 計算量
未調査。
n <= 1000くらいなら動く

## コード
```cpp
#include <vector>
#include <algorithm>

class SternBrocotTree {
private:
    std::vector<std::pair<int, int>> lists;

    void build(
        int N, int pl = 0, int ql = 1, int pr = 1, int qr = 0)
    {
        int pm = pl + pr, qm = ql + qr;
        if (pm + qm > N)
            return;

        lists.emplace_back(pm, qm);
        build(N, pl, ql, pm, qm);
        build(N, pm, qm, pr, qr);
    }
public:
    SternBrocotTree(int N)
    {
        build(N);
        std::sort(lists.begin(), lists.end());
    }

    void clear()
    {
        lists.clear();
    }

    auto get()
    {
        return lists;
    }
};
```

## 検証
※未検証