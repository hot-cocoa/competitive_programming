#include <vector>
#include <string>

// Manacher's algorithm
std::vector<int> longest_palindrome(const std::string &s)
{
    int N = s.size();
    std::vector<int> radius(N);
    for (int i = 0, j = 0, k = 0; i < N; i += k, j -= k) {
        for (; i - j >= 0 && i + j < N && s[i - j] == s[i + j]; j++);

        radius[i] = j;
        for (k = 1; i - k >= 0 && i + k < N && k + radius[i - k] < j; k++)
            radius[i + k] = radius[i - k];
    }
    return radius;
}