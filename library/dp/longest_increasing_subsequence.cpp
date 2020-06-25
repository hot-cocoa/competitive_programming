#include <vector>

using int64 = long long;
constexpr static int64 INF = 1LL << 55;

int longest_increasing_subsequence(
    const std::vector<int>& a
)
{
    int N = a.size();
    std::vector<int64> dp(N, INF);
    for (int i = 0; i < N; i++)
        *lower_bound(dp.begin(), dp.end(), a[i]) = a[i];

    return lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
}