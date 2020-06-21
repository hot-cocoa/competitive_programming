#include <vector>
#include <string>
#include <functional>

using F = std::function<int(char)>;

template<int size>
class Trie {
private:
    class Node {
    public:
        int exist;
        std::vector<int> next;
        std::vector<int> accepts;

        Node()
        {
            exist = 0;
            next.assign(size, -1);
        }
    };

public:
    std::vector<Node> nodes;

    Trie()
    {
        nodes.emplace_back(Node());
    }

    void insert(const std::string &s, const F &to_int)
    {

    }

    bool find(const std::string &s)
    {

    }
};