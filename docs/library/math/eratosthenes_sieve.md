# エラトステネスの篩
## 概要
素数判定表を高速に作成する。

## 計算量
O(n loglogn)

## コード
```cpp
#include <vector>

class EratosthenesSieve {
private:
    std::vector<bool> prime;

    void build(int N)
    {
        prime.assign(N, true);
        for (int i = 2; i * i < N; i++)
            if (prime[i])
                for (int j = i * 2; j < N; j += i)
                    prime[j] = false;
    }

public:
    EratosthenesSieve(int N)
    {
        build(N);
    }

    bool is_prime(int x)
    {
        return prime.at(x);
    }
};
```

## 検証
- [AOJ 1276](https://onlinejudge.u-aizu.ac.jp/challenges/search/titles/1276)