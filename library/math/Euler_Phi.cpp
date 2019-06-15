int euler_phi(int n)
{
    if (n == 0)
        return 0;

    int count_disjoint = n;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            count_disjoint -= count_disjoint / i;
            while (n % i == 0)
                n /= i;
        }
    }

    if (n > 1)
        count_disjoint -= count_disjoint / n;
        
    return count_disjoint;
}
