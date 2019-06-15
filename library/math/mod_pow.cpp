using int64 = long long;

int64 mod_pow(int64 x, int64 n, int64 mod)
{
    if (n == 0)
        return 1;

    int64 res = mod_pow(x * x % mod, n / 2, mod);
    if (n & 1)
        res = res * x % mod;

    return res;
}
