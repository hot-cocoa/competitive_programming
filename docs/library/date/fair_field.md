# 日付差分
## 概要
2つの日付の差分を求める。  
フェアフィールドの公式を使用する。

## 計算量
O(1)

## コード
```cpp
int fair_field(int y, int m, int d)
{
    if (m <= 2)
        y--, m += 12;

    return 365 * y + y / 4 - y / 100 + y / 400 + 153 * (m + 1) / 5 + d - 428;
}

int diff_date(
    int y1, int m1, int d1,
    int y2, int m2, int d2)
{
    return fair_field(y2, m2, d2) - fair_field(y1, m1, d1);
}
```

## 検証
※未検証