#include <vector>

class EratosthenesSieve {
private:
    std::vector<bool> prime;

    void build(int N)
    {
        prime.assign(N, true);
        for (int i = 2; i * i < N; i++)
            if (prime[i])
                for (int j = i * 2; j < N; j += i)
                    prime[j] = false;
    }

public:
    EratosthenesSieve(int N)
    {
        build(N);
    }

    bool is_prime(int x)
    {
        return prime.at(x);
    }
};
