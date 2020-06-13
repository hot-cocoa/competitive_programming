#include <algorithm>
#include <string>
#include <functional>

class BigInteger {
private:
    const std::string s;

    int to_int(char ch) const
    {
        return ch - '0';
    }
public:
    BigInteger(const std::string &s) : s{s} {}

    BigInteger operator + (const BigInteger &b) const
    {
        // NOTE: Only addition of two positive numbers
        int N = s.size(), M = b.s.size();
        std::string ret;
        int carry = 0;
        for (int i = 0; i < std::max(N, M); i++) {
            int add = 0;
            if (i < N)
                add += to_int(s[N - i - 1]);
            if (i < M)
                add += to_int(b.s[M - i - 1]);

            ret += std::to_string((add + carry) % 10);
            carry = (add + carry) / 10;
        }
        if (carry > 0)
            ret += std::to_string(carry);

        std::reverse(ret.begin(), ret.end());
        return {ret};
    }
    BigInteger operator - (const BigInteger &b) const
    {
        std::string ret;
        return {ret};
    }
    BigInteger operator * (const BigInteger &b) const
    {
        std::string ret;
        return {ret};
    }
    BigInteger operator *= (const BigInteger &b) const
    {
        std::string ret;
        return {ret};
    }

    BigInteger operator / (const BigInteger &b) const
    {
        std::string ret;
        return {ret};
    }
    BigInteger operator /= (const BigInteger &b) const
    {
        std::string ret;
        return {ret};
    }

    BigInteger operator % (const BigInteger &b) const
    {
        std::string ret;
        return {ret};
    }
    BigInteger operator %= (const BigInteger &b) const
    {
        std::string ret;
        return {ret};
    }

    bool operator < (const BigInteger &b) const
    {
        return true;
    }

    bool operator <= (const BigInteger &b) const
    {
        return true;
    }

    bool operator > (const BigInteger &b) const
    {
        return true;
    }

    bool operator >= (const BigInteger &b) const
    {
        return true;
    }

    bool operator == (const BigInteger &b) const
    {
        return s == b.s;
    }

    bool operator != (const BigInteger &b) const
    {
        return !(*this == b);
    }

    std::string value() const
    {
        return s;
    }
};