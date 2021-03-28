#include <bits/stdc++.h>
#define db(x) cerr << #x << " = " << x << endl;
// #define endl '\r'

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned int ui;
typedef array<int, 2> pi;

// dp0[i][j][a[i]] (a[i] == b[j]) = 1 + max(dp1[0..i - 1][0..j - 1][a[i]+1..inf])
// dp0[i][j] = max(dp0[i - 1][j], dp[i][j - 1])

namespace Flow {
    const int N = 500 + 2, M = 10000 * 2;
    int S = N - 2, T = N - 1;
    struct Edge {
        int b;
        ll c, f;
        int nxt = -1;
    };

    Edge e[M];
    int m;
    int head[N];
    int cur[N];

    void init() {
        m = 0;
        memset(head, -1, sizeof(head));
    }

    void add_edge(int a, int b, ll c) {
        e[m++] = {b, c, 0LL, head[a]};
        head[a] = m - 1;

        e[m++] = {a, 0LL, 0LL, head[b]};
        head[b] = m - 1;
    }

    int d[N];
    int q[N];
    void bfs(ll sc) {
        memset(d, -1, sizeof(d));
        d[S] = 0;
        int l = 0, r = 1;
        q[0] = S;
        while (r - l) {
            int v = q[l++];
            for (int i = head[v]; i != -1; i = e[i].nxt) {
                if (e[i].c - e[i].f >= sc && d[e[i].b] == -1) {
                    d[e[i].b] = d[v] + 1;
                    q[r++] = e[i].b;
                }
            }
        }
    }

    ll dfs(int v, ll min_val, ll sc) {
        if (v == T) {
            return min_val;
        }
        for (; cur[v] != -1; cur[v] = e[cur[v]].nxt) {
            auto &c = e[cur[v]];
            if (d[c.b] <= d[v] || c.c - c.f < sc) continue;
            if (ll x = dfs(c.b, min(min_val, c.c - c.f), sc)) {
                c.f += x;
                e[cur[v] ^ 1].f -= x;
                return x;
            }
        }
        return 0;
    }

    ll step(ll sc) {
        memcpy(cur, head, sizeof(cur));
        bfs(sc);
        ll ans = 0;
        for (ll x; x = dfs(S, INT_MAX, sc); ans += x)
            {}
        return ans;
    }

    ll dinic() {
        ll ans = 0;
        for (ll x; x = step(1); ans += x)
            {}
        return ans;
    }

    ll scale() {
        ll ans = 0;
        for (int h = 30; h >= 0; --h) {
            for (ll x; x = step(1ll << h); ans += x)
                {}
        }
        return ans;
    }
// namespace Flow    // namespace Flow
};  // namespace Flow
// namespace Flow
// namespace Flow

signed main() {
    Flow::init();
    int n, m;
    cin >> n >> m;
    Flow::S = 0;
    Flow::T = n - 1;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c; --a; --b;
        Flow::add_edge(a, b, c);
    }
    cout << Flow::scale();
    cout << endl;
    return 0;
}
