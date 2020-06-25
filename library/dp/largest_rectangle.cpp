#include <vector>
#include <stack>

using Vec = std::vector<int>;
using Mat = std::vector<Vec>;

int largest_rectangle(const Mat& m)
{
    int N = m.size(), M = m[0].size();
    Vec dp(M + 1, 0);
    int max_area = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            dp[j] = (m[i][j] == 0 ? dp[j] + 1 : 0);

        std::stack<std::pair<int, int>> st;
        st.emplace(0, M);
        for (int j = 0; j <= M; j++) {
            int k = j;
            while (dp[j] < st.top().first) {
                k = st.top().second;
                max_area = std::max(max_area, st.top().first * (j - k));
                st.pop();
            }
            if (st.top().first < dp[j])
                st.emplace(dp[j], k);
        }
    }
    return max_area;
}