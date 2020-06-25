#include <vector>

using Graph = std::vector<std::vector<int>>;

class CycleOperator {
private:
    Graph g;
    std::vector<int> num;
    std::vector<int> visited;

    int dfs(int v, int c)
    {
        visited[v] = 0;
        num[v] = c;

        int largest = 0;
        for (int to : g[v])
            if (visited[to] == -1)
                largest = std::max(largest, dfs(to, c + 1));
            else if (visited[to] == 0)
                largest = std::max(largest, num[v] - num[to] + 1);

        visited[v] = 1;
        return largest;
    }

public:
    CycleOperator(const Graph& g) : g{g} {}

    int largest_cycle()
    {
        int N = g.size();
        num.assign(N, -1);
        visited.assign(N, -1);

        int largest = 0;
        for (int i = 0; i < N; i++)
            if (visited[i] == -1)
                largest = std::max(largest, dfs(i, 1));

        return (largest >= 3 ? largest : 0);
    }
};
