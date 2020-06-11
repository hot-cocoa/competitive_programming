#include <vector>
#include <string>

using Vec = std::vector<int>;
using Mat = std::vector<Vec>;

int largest_square(const Mat &m)
{
    int N = m.size(), M = m[0].size();
    Mat dp(N, Vec(M));
    int max = 0;
    for (int i = 0; i < N; i++) {
        dp[i][0] = (m[i][0] == 0);
        max = std::max(max, dp[i][0]);
    }
    for (int i = 0; i < M; i++) {
        dp[0][i] = (m[0][i] == 0);
        max = std::max(max, dp[0][i]);
    }

    for (int i = 1; i < N; i++)
        for (int j = 1; j < M; j++)
            if (m[i][j] == 1)
                dp[i][j] = 0;
            else {
                dp[i][j] =
                    std::min(dp[i - 1][j - 1],
                             std::min(dp[i - 1][j], dp[i][j - 1])) + 1;

                max = std::max(max, dp[i][j]);
            }

    return max * max;
}