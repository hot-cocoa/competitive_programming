# トライ木
## 概要
文字列中の文字をノードとして扱い、  
複数の文字列に共通するprefix(接頭部分)を共通のノードとして管理する。

## 計算量
- 追加：O(\|S\|)
- 検索：O(\|S\|)

## コード
```cpp
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
            if (!nodes.at(curr).next.count(c)) {
                int n = nodes.size();
                push();
                nodes.at(curr).next.emplace(c, n);
            }
            nodes.at(curr).exist++;
            curr = nodes.at(curr).next.at(c);
        }
        nodes.at(curr).exist++;
        nodes.at(curr).accepts.emplace_back(id);
    }

public:
    std::vector<Node> nodes;
    Trie() { push(); }

    void insert(const std::string& s)
    {
        insert(s, nodes.at(0).exist);
    }

    int find(const std::string& s, int idx = 0)
    {
        int curr = idx;
        for (const auto& c : s) {
            if (!nodes.at(curr).next.count(c))
                return -1;

            curr = nodes.at(curr).next.at(c);
        }
        return curr;
    }
};
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/14/ALDS1_14_A)
