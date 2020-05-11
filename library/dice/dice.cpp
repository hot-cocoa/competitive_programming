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

public:
    Dice(std::vector<T> x) : x{x} {}

    void roll_N() { roll(TOP, FRONT, BACK, BOTTOM); }
    void roll_E() { roll(TOP, LEFT, RIGHT, BOTTOM); }
    void roll_W() { roll(TOP, RIGHT, LEFT, BOTTOM); }
    void roll_S() { roll(TOP, BACK, FRONT, BOTTOM); }

    void rotation_left()  { roll(FRONT, RIGHT, LEFT, BACK); }
    void rotation_right() { roll(FRONT, LEFT, RIGHT, BACK); }

    T top()    { return x[TOP]; }
    T front()  { return x[FRONT]; }
    T right()  { return x[RIGHT]; }
    T left()   { return x[LEFT]; }
    T back()   { return x[BACK]; }
    T bottom() { return x[BOTTOM]; }
};
