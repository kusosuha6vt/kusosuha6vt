#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int A = 26;
struct nd {
    int m[A];
    int l, p;
    nd(int l = -1, int p = -1) : l(l), p(p) {
    }
};

const int MEM = 4e5 + 1;
ll dp[MEM];
nd t[MEM];
int sz = 1;
int add(int a, int c) {
    int b = sz++;
    t[b].p = a;
    t[b].l = 0;
    for (; a != -1; a = t[a].l) {
        if (!t[a].m[c]) {
            t[a].m[c] = b;
            dp[b] += dp[a];
            continue;
        }
        int v = t[a].m[c];
        if (t[v].p == a) {
            t[b].l = v;
            break;
        }
        int u = sz++;
        t[u] = t[v];
        t[v].l = u;
        t[b].l = u;
        t[u].p = a;
        for (; a != -1 && t[a].m[c] == v; a = t[a].l) {
            t[a].m[c] = u;
            dp[u] += dp[a];
        }
        dp[v] -= dp[u];
        break;
    }
    return b;
}

int main() {
    // count of different strings on prefix
    dp[0] = 1;
    string s;
    cin >> s;
    int v = 0;
    ll ans = 0;
    for (int i = 0; i < s.size(); ++i) {
        v = add(v, s[i] - 'a');
        ans += dp[v];
        cout << ans << '\n';
    }
    return 0;
}
