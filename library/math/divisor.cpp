#include <vector>

// Not Verify!
std::vector<int> divisor(int N)
{
    std::vector<int> divisors;
    for (int i = 1; i * i <= N; i++)
        if (N % i == 0) {
            divisors.emplace_back(i);
            if (i != N / i)
                divisors.emplace_back(N / i);
        }

    return divisors;
}
