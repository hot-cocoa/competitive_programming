# Binary Indexed Tree
## 概要
配列Aに対して、以下の操作を高速に行うデータ構造である。  
1. iが与えられたとき、A<sub>1</sub>+A<sub>2</sub>+...+A<sub>i</sub>を求める。
2. iとxが与えられたとき、A<sub>i</sub>にxを加算する。

## 計算量
1. O(log n)
2. O(log n)

## コード
```cpp
#include <vector>

class BinaryIndexedTree {
private:
    int N = 1 << 20;
    std::vector<int> b;

public:
    BinaryIndexedTree()
    {
        b.assign(N + 1, 0);
    }

    int sum(int i)
    {
        int s = 0;
        while (i > 0) {
            s += b[i];
            i -= i & -i;
        }
        return s;
    }

    void add(int i, int x)
    {
        while (i <= N) {
            b[i] += x;
            i += i & -i;
        }
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B)