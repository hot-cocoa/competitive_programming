#include <vector>

using int64 = long long;

class Combination {
private:
    constexpr static int64 DEFAULT = -1;
    std::vector<std::vector<int64>> c;
public:
    Combination(int max)
    {
        c.assign(max + 1, std::vector<int64>(max + 1, DEFAULT));
    }

    // calc nCr
    int64 calc(int n, int r)
    {
        if (n < r)
            return 0LL;

        if (n == r || r == 0)
            return 1LL;

        if (c[n][r] != DEFAULT)
            return c[n][r];

        return c[n][r] = calc(n - 1, r - 1) + calc(n - 1, r);
    }
};
