using int64 = long long;

bool is_prime(int64 n)
{
    if (n < 2)
        return false;
        
    for (int64 i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;

    return true;
}