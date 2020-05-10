#include <vector>

using vec = std::vector<int>;
using Graph = std::vector<vec>;

class CycleDetector {
private:
    enum class State : int {
        UNCHECK  = -1,
        CHECKING = 0,
        CHECKED  = 1
    };

    Graph g;
    std::vector<State> visit;

    void init(int V)
    {
        visit.resize(V);
    }

    bool dfs(int v)
    {
        visit[v] = State::CHECKING;

        bool found = false;
        for (int to : g[v]) {
            if (visit[to] == State::UNCHECK)
                found |= dfs(to);
            else if (visit[to] == State::CHECKING)
                return true;
        }
        visit[v] = State::CHECKED;
        return found;
    }

public:
    CycleDetector(Graph g) : g{g} { init(g.size()); }

    bool exists_cycle()
    {
        std::fill(visit.begin(), visit.end(), State::UNCHECK);
        bool found = false;
        for (int i = 0; i < (int)g.size(); i++)
            if (visit[i] == State::UNCHECK)
                found |= dfs(i);

        return found;
    }
};
