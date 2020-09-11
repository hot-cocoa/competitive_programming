#include <vector>
#include <string>
#include <map>

template<typename Type>
class Trie {
private:
    class Node {
    public:
        int exist;
        std::map<Type, int> next;
        std::vector<int> accepts;
        Node() : exist{0} {}
    };

    void push(Node node = Node())
    {
        nodes.emplace_back(node);
    }

    void insert(const std::string& s, int id)
    {
        int curr = 0;
        for (const auto& c : s) {
            if (!nodes[curr].next.count(c)) {
                int n = nodes.size();
                push();
                nodes[curr].next.emplace(c, n);
            }
            nodes[curr].exist++;
            curr = nodes[curr].next[c];
        }
        nodes[curr].exist++;
        nodes[curr].accepts.emplace_back(id);
    }

public:
    std::vector<Node> nodes;
    Trie() { push(); }

    void insert(const std::string& s)
    {
        insert(s, nodes[0].exist);
    }

    int find(const std::string& s, int idx = 0)
    {
        int curr = idx;
        for (const auto& c : s) {
            if (!nodes[curr].next.count(c))
                return -1;

            curr = nodes[curr].next[c];
        }
        return curr;
    }
};