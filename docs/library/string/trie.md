# Trie木
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
```

## 検証
- [AOJ Library](https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/14/ALDS1_14_A)
