#include <bits/stdc++.h>
#define int long long

using namespace std;

struct Palindrome_tree {
    struct Node {
        int len, link, num;
        map<char, int> next;

        Node(int len, int link, int num = 0) : len(len), link(link), num(num) {}
    };
    int n, i, last = 1;
    long long& ans;
    const string& s;
    vector<Node> trie;
    Palindrome_tree(const string& s, long long& ans) : s(s), n(s.size()), ans(ans) {
        trie.reserve(n + 5);
        trie.emplace_back(-1, 0);
        trie.emplace_back(0, 0);
        ans = 0;

        for (i = 0; i < n; ++i) {
            expend();
        }
    }

    void expend() {
        int v = last;
        while (trie[v].len >= i || s[i - trie[v].len - 1] != s[i])
            v = trie[v].link;

        if (trie[v].next.count(s[i])) {
            last = trie[v].next[s[i]];
            ans += trie[last].num;
            return;
        }

        last = trie.size();
        trie.emplace_back(trie[v].len + 2, -1, -1);
        trie[v].next[s[i]] = last;

        /// link search
        if (trie[last].len == 1) {
            trie[last].link = 1; /// ""
            trie[last].num = 1;
            ans += trie[last].num;
            return;
        }
        v = trie[v].link;
        while (trie[v].len >= i || s[i - trie[v].len - 1] != s[i])
            v = trie[v].link;
        v = trie[v].next[s[i]];
        trie[last].link = v;
        trie[last].num = trie[v].num + 1;
        ans += trie[last].num;
        return;
    }
};

signed main() {
    string s;
    cin >> s;
    long long ans = 0;
    Palindrome_tree(s, ans);
    cout << ans;
    return 0;
}
