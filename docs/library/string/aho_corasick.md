# エイホーコラシック
## 概要
パターンマッチオートマトンを用いて、文字列検索を行うアルゴリズム。

## 計算量
構築：O(Σ|S|)  
検索：O(|S|)

## コード
```cpp
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

class AhoCorasick {
private:
    constexpr static int SIZE = 256;

    class PMA {
    public:
        std::vector<PMA*> next;
        std::vector<int> matched;
        PMA() {
            next.assign(SIZE, nullptr);
        }
    };

    PMA* root;

    void build(const std::vector<std::string>& patterns)
    {
        root = new PMA;
        for (int i = 0; i < (int)patterns.size(); i++) {
            const std::string& pattern = patterns[i];
            PMA* t = root;
            for (const char& c : pattern) {
                if (!t->next[c])
                    t->next[c] = new PMA;

                t = t->next[c];
            }
            t->matched.emplace_back(i);
        }

        std::queue<PMA*> que;
        for (auto c = 'a'; c <= 'z'; c++) {
            if (root->next[c]) {
                root->next[c]->next[0] = root;
                que.emplace(root->next[c]);
            }
            else
                root->next[c] = root;
        }

        while (!que.empty()) {
            PMA* t = que.front(); que.pop();

            for (char c = 'a'; c <= 'z'; c++) {
                if (!t->next[c])
                    continue;

                PMA* next = t->next[0];
                while (!next->next[c])
                    next = next->next[0];

                t->next[c]->next[0] = next->next[c];

                const auto& m1 = t->next[c]->matched;
                const auto& m2 = next->next[c]->matched;
                std::set_union(
                    m1.begin(), m1.end(),
                    m2.begin(), m2.end(),
                    t->next[c]->matched.begin());

                que.emplace(t->next[c]);
            }
        }
    }

public:
    AhoCorasick() {}
    AhoCorasick(const std::vector<std::string>& patterns)
    {
        build(patterns);
    }

    void set(const std::vector<std::string>& patterns)
    {
        build(patterns);
    }

    std::vector<int> match(const std::string& s)
    {
        std::vector<int> result(SIZE);
        PMA* pma = root;
        for (const auto& c : s) {
            while (!pma->next[c])
               pma = pma->next[0];

            pma = pma->next[c];
            for (const auto m : pma->matched)
                result[m] = true;
        }
        return result;
    }
};
```

## 検証
※未検証