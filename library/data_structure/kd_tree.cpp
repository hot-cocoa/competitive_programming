#include <vector>
#include <algorithm>

using pii = std::pair<int, int>;

class KdTree2D {
private:
    class Node {
    public:
        int loc;
        int l, r;
        Node() { loc = l = r = -1; }
        Node(int loc, int l, int r) : loc{loc}, l{l}, r{r} {}
    };
    using Tree = std::vector<Node>;

    Tree t;
    std::vector<pii> ps;
    int np;
    int root;

    void init()
    {
        int n = ps.size();
        t.resize(n);
        np = 0;
        root = build(0, n, 0);
    }

    int build(int l, int r, int depth)
    {
        if (l >= r)
            return -1;

        int mid = (l + r) / 2;
        int curr = np++;

        if (depth % 2 == 0) {
            auto cmp_x = [](const pii& a, const pii& b) { return a.first < b.first; };
            std::sort(ps.begin() + l, ps.begin() + r, cmp_x);
        }
        else {
            auto cmp_y = [](const pii& a, const pii& b) { return a.second < b.second; };
            std::sort(ps.begin() + l, ps.begin() + r, cmp_y);
        }
        t[curr] = {mid, build(l, mid, depth + 1), build(mid + 1, r, depth + 1)};
        return curr;
    }

    bool find(int k, int sx, int sy, int tx, int ty, int depth)
    {
        auto [x, y] = ps[t[k].loc];
        if (sx <= x && x <= tx && sy <= y && y <= ty)
            return true;

        bool found = false;
        if (depth % 2 == 0) {
            if (t[k].l != -1 && sx <= x)
                found |= find(t[k].l, sx, sy, tx, ty, depth + 1);

            if (t[k].r != -1 && x <= tx)
                found |= find(t[k].r, sx, sy, tx, ty, depth + 1);
        }
        else {
            if (t[k].l != -1 && sy <= y)
                found |= find(t[k].l, sx, sy, tx, ty, depth + 1);

            if (t[k].r != -1 && y <= ty)
                found |= find(t[k].r, sx, sy, tx, ty, depth + 1);
        }
        return found;
    }

public:
    KdTree2D(const std::vector<pii> &ps) : ps{ps}
    {
        init();
    }

    bool find(int sx, int sy, int tx, int ty)
    {
        return find(root, sx, sy, tx, ty, 0);
    }
};
