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

    void insert(const std::string &s, int id)
    {
        int curr = 0;
        for (const auto &c : s) {
            if (!nodes.next.count(c)) {
                int n = nodes.size();
                push();
                nodes.at(n).next.emplace(c, n);
            }
            nodes.at(curr).exist++;
            curr = nodes.at(curr).next(c);
        }
        nodes.at(curr).exist++;
        nodes.at(curr).accepts(id);
    }

public:
    std::vector<Node> nodes;
    Trie() { push(); }

    void insert(const std::string &s)
    {
        insert(s, nodes.at(0).exist);
    }

    bool find(const std::string &s)
    {

    }
};