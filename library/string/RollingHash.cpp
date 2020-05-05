#include <string>
#include <vector>

using ull = unsigned long long;
constexpr ull B = 1000000007UL;

class RollingHash {
public:
    /*
     * 文字列sの部分文字列s[L, R]のハッシュ値は以下の通り.
     * h[L, R] := h[R + 1] - h[L] * p[R - L + 1]
     */
    std::vector<ull> create(
        const std::string &s,
        int size,
        std::vector<ull> &p
    ) {
        std::vector<ull> h(size + 1);
        p.resize(size + 1);
        p[0] = 1;

        for (int i = 0; i < size; i++) {
            h[i + 1] = h[i] * B + s[i];
            p[i + 1] = p[i] * B;
        }

        return h;
    }
};
