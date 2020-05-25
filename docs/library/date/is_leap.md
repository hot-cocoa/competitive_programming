# うるう年判定
## 概要
西暦n年がうるう年かどうかを判定する。  
※[うるう年について](https://ja.wikipedia.org/wiki/%E9%96%8F%E5%B9%B4)

## 計算量
O(1)

## コード
```cpp
bool is_leap(int year)
{
    if (year % 400 == 0)
        return true;

    if (year % 100 == 0)
        return false;

    if (year % 4 == 0)
        return true;

    return false;
}
```

## 検証
- [AOJ 0093](https://onlinejudge.u-aizu.ac.jp/challenges/search/titles/0093)