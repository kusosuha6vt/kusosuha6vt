#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define int ll

const int N = 2.5e5;
typedef array<int, 2> a2;
vector<a2> g[N];
pair<ll, int> dp[2][N];

pair<ll, int> add_(pair<ll, int> a, pair<ll, int> b) {
    return {a.first + b.first, a.second + b.second};
}

pair<ll, int> dec(pair<ll, int> a, pair<ll, int> b) {
    return {a.first - b.first, a.second - b.second};
}

void dfs(int v, int p, ll add) {
    dp[0][v] = {0LL, 0};
    dp[1][v] = {LLONG_MIN, INT_MIN};
    for (auto u : g[v]) {
        if (u[0] == p)
            continue;
        dfs(u[0], v, add);
        dp[0][v] = add_(dp[0][v], max(dp[0][u[0]], dp[1][u[0]]));
    }
    for (auto u : g[v]) {
        if (u[0] == p)
            continue;
        dp[1][v] = max(dp[1][v], 
            add_(dec(dp[0][v], max(dp[0][u[0]], dp[1][u[0]])), 
                add_(make_pair(u[1] + add, 1), dp[0][u[0]])));
    }
}

int m0[N];
int m1[N];
void dfsm(int v, int p) {
    m0[v] = 0;
    m1[v] = INT_MIN;
    for (auto u : g[v]) {
        if (u[0] == p)
            continue;
        dfsm(u[0], v);
        m0[v] += max(m0[u[0]], m1[u[0]]);
    }
    for (auto u : g[v]) {
        if (u[0] == p)
            continue;
        m1[v] = max(m1[v], m0[v] - max(m1[u[0]], m0[u[0]]) + m0[u[0]] + 1);
    }
}

signed main() {
    // freopen("in", "r", stdin);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g[a].push_back(a2{b, c});
        g[b].push_back(a2{a, c});
    }
    dfsm(0, -1);
    if (max(m0[0], m1[0]) < k) {
        cout << "Impossible";
        return 0;
    }
    ll l = -1e9, r = 1e9;
    // (l; r]
    while (r - l > 1) {
        int m = (l + r) / 2;
        dfs(0, -1, m);
        int k1 = max(dp[0][0], dp[1][0]).second;
        if (k1 >= k) {
            r = m;
        } else {
            l = m;
        }
    }
    dfs(0, -1, r);
    cout << max(dp[0][0], dp[1][0]).first - k * r;
    return 0;
}
