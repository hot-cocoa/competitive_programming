#include <map>

std::map<int, int> prime_factorize(int n)
{
    std::map<int, int> res;
    for (int i = 2; i * i <= n; i++) {
        while (n % i == 0) {
            ++res[i];
            n /= i;
        }
    }

    if (n != 1)
        res[n] = 1;

    return res;
}
