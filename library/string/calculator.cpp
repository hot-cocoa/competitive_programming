#include <string>

template<class T>
class Calculator {
private:
    std::string::const_iterator it;

    T fact()
    {
        T ret;
        if (*it == '(') {
            ++it;
            ret = exp();
            ++it;
        }
        else {
            ret = 0;
            while (isdigit(*it)) {
                ret *= 10;
                ret += *it - '0';
                ++it;
            }
        }
        return ret;
    }

    T term()
    {
        T ret = fact();
        while (*it == '*' || *it == '/') {
            auto ch = *it;
            ++it;
            if (ch == '*')
                ret *= fact();
            else if (ch == '/')
                ret /= fact();
        }
        return ret;
    }
public:
    Calculator(const std::string &s) : it{s.begin()} {}

    T exp()
    {
        T ret = term();
        while (*it == '+' || *it == '-') {
            auto ch = *it;
            ++it;
            if (ch == '+')
                ret += term();
            else if (ch == '-')
                ret -= term();
        }
        return ret;
    }
};