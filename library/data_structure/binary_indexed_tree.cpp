class BinaryIndexedTree {
private:
    int N = 1 << 20;
    std::vector<int> b;

public:
    BinaryIndexedTree()
    {
        b.assign(N + 1, 0);
    }

    int sum(int i)
    {
        int s = 0;
        while (i > 0) {
            s += b[i];
            i -= i & -i;
        }
        return s;
    }

    void add(int i, int x)
    {
        while (i <= N) {
            b[i] += x;
            i += i & -i;
        }
    }
};
