# サイコロ
## 概要
6面体サイコロについて回転を実施する。  
また、2つのサイコロの同値チェックを実施する。  
2つのサイコロが同値とは、  
一方のサイコロを固定して、他方のサイコロに対して回転を繰り返しすべての面が一致することを指す。

## 計算量
定数時間

## コード
```cpp
#include <vector>

template<class T>
class Dice {
private:
    std::vector<T> x;

    enum Face : int {
        TOP    = 0,
        FRONT  = 1,
        RIGHT  = 2,
        LEFT   = 3,
        BACK   = 4,
        BOTTOM = 5
    };

    void roll(Face a, Face b, Face c, Face d)
    {
        std::swap(x[a], x[b]);
        std::swap(x[b], x[d]);
        std::swap(x[c], x[d]);
    }

    T at(int idx) const { return x[idx]; }

    bool same_faces(const Dice &d) const
    {
        for (int i = 0; i < size(); i++)
            if (at(i) != d.at(i))
                return false;

        return true;
    }

public:
    Dice(const std::vector<T> &x) : x{x} {}

    void roll_N() { roll(TOP, FRONT, BACK, BOTTOM); }
    void roll_E() { roll(TOP, LEFT, RIGHT, BOTTOM); }
    void roll_W() { roll(TOP, RIGHT, LEFT, BOTTOM); }
    void roll_S() { roll(TOP, BACK, FRONT, BOTTOM); }

    void rotation_left()  { roll(FRONT, RIGHT, LEFT, BACK); }
    void rotation_right() { roll(FRONT, LEFT, RIGHT, BACK); }

    // Constraints: the values of face are all different
    void roll(T top_val, T front_val)
    {
        if (left() == top_val)
            roll_E();

        if (right() == top_val)
            roll_W();

        while (top() != top_val)
            roll_N();

        while (front() != front_val)
            rotation_left();
    }

    T top()    const { return x[TOP]; }
    T front()  const { return x[FRONT]; }
    T right()  const { return x[RIGHT]; }
    T left()   const { return x[LEFT]; }
    T back()   const { return x[BACK]; }
    T bottom() const { return x[BOTTOM]; }

    int size() const { return x.size(); }

    bool operator == (const Dice &d)
    {
        if (size() != d.size())
            return false;

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (same_faces(d))
                    return true;

                rotation_left();
            }
            i % 2 == 0 ? roll_N() : roll_E();
        }
        return false;
    }
};
```

## 検証
- AOJLibrary
    - [上下左右回転](https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/11/ITP1_11_A)
    - [上面と前面が合うように回転](https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/11/ITP1_11_B)
    - [同値判定](https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/11/ITP1_11_C)
