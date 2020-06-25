# 行列累乗
## 概要
行列Aに対して、A<sup>k</sup>を求める。

## 計算量
O(n<sup>3</sup> log k)

## コード
```cpp
#include <vector>

using int64 = long long;
using vec = std::vector<int64>;
using mat = std::vector<vec>;
constexpr static int64 MOD = 1e9 + 9;

class MatrixOperator {
private:
    MatrixOperator() {}

public:
    static mat mul(const mat& A, const mat& B)
    {
        mat C(A.size(), vec(B[0].size()));
        for (int i = 0; i < (int)A.size(); i++)
            for (int k = 0; k < (int)B.size(); k++)
                for (int j = 0; j < (int)B[0].size(); j++)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;

        return C;
    }

    static mat pow(mat A, int64 n)
    {
        int N = A.size();
        mat B(N, vec(N));
        for (int i = 0; i < N; i++)
            B[i][i] = 1;

        while (n > 0) {
            if (n & 1)
                B = mul(B, A);

            A = mul(A, A);
            n >>= 1;
        }
        return B;
    }
};
```

## 検証
- [AOJ 2397](https://onlinejudge.u-aizu.ac.jp/challenges/search/titles/2397)
