# Mod Int
## 概要
MODの下で演算を行う。

## 計算量
いろいろ

## コード
```cpp
using int64 = long long;

template <int64 MOD>
class ModInt {
private:
    int64 v;

    int64 mod_of(int64 x)
    {
        if (x < 0)
            x += MOD;

        return x % MOD;
    }

    int64 mod_pow(int64 x, int64 n)
    {
        if (n == 0)
            return 1;

        int64 res = mod_pow(x * x % MOD, n / 2);
        if (n & 1)
            res = res * x % MOD;

        return res;
    }

public:
    ModInt(int64 x = 0) : v(mod_of(x)) {}

    ModInt operator + (const ModInt &rhs) const
    {
        return ModInt(v + rhs.v);
    }
    ModInt operator - (const ModInt &rhs) const
    {
        return ModInt(v - rhs.v);
    }
    ModInt operator * (const ModInt &rhs) const
    {
        return ModInt(v * rhs.v);
    }
    ModInt operator / (const ModInt &rhs) const
    {
        return ModInt(v * mod_pow(rhs.v, MOD - 2));
    }
    ModInt operator += (const ModInt &rhs)
    {
        v = mod_of(v + rhs.v);
        return *this;
    }
    ModInt operator -= (const ModInt &rhs)
    {
        v = mod_of(v - rhs.v);
        return *this;
    }
    ModInt operator *= (const ModInt &rhs)
    {
        v = mod_of(v * rhs.v);
        return *this;
    }
    ModInt operator /= (const ModInt &rhs)
    {
        v = mod_of(v * mod_pow(rhs.v, MOD - 2));
        return *this;
    }
    ModInt operator - () const
    {
        return ModInt(-v);
    }
    bool operator == (const ModInt &rhs) const
    {
        return v == rhs.v;
    }
    bool operator != (const ModInt &rhs) const
    {
        return v != rhs.v;
    }
    int64 value()
    {
        return v;
    }
};
```

## 検証
※すべてを検証できていない。
- [AtCoder ABC151E](https://atcoder.jp/contests/abc151/tasks/abc151_e)