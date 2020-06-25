#include <vector>
#include <cmath>

template<class T>
using vec = std::vector<T>;

template<class T>
using mat = std::vector<vec<T>>;

template<class T>
class GaussJordan {
private:
    constexpr static double EPS = 1e-8;

public:
    vec<T> solve(const mat<T>& A, const vec<T>& b)
    {
        int N = A.size();
        mat<T> B(N, vec<T>(N + 1));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                B[i][j] = A[i][j];

        for (int i = 0; i < N; i++)
            B[i][N] = b[i];

        for (int i = 0; i < N; i++) {
            int pivot = i;
            for (int j = i; j < N; j++)
                if (abs(B[j][i]) > abs(B[pivot][i]))
                    pivot = j;

            std::swap(B[i], B[pivot]);
            if (abs(B[i][i]) < EPS)
                return {};

            for (int j = i + 1; j <= N; j++)
                B[i][j] /= B[i][i];

            for (int j = 0; j < N; j++) {
                if (i == j)
                    continue;

                for (int k = i + 1; k <= N; k++)
                    B[j][k] -= B[j][i] * B[i][k];
            }
        }

        vec<T> x(N);
        for (int i = 0; i < N; i++)
            x[i] = B[i][N];

        return x;
    }
};
