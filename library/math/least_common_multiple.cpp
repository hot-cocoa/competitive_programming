using int64 = long long;

int64 gcd(int64 a, int64 b)
{
    if (b == 0)
        return a;

    return gcd(b, a % b);
}

int64 lcm(int64 a, int64 b)
{
    return a / gcd(a, b) * b;
}
