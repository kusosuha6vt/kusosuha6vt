#define _GLIB_CXX_DEBUG
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 1e5 + 2;
const int LOG = 17;
int n;
vector<int> g[N];
typedef array<int, 2> a2;
int d[N];
int sz[N];
int h[N];
int par[N];
int tin[N], tout[N], tcur;

void dfs_init(int v, int p = -1) {
    tin[v] = tcur++;
    h[v] = 1;
    sz[v] = 1;
    for (int u : g[v]) {
        if (u == p)
            continue;
        par[u] = v;
        d[u] = d[v] + 1;
        dfs_init(u, v);
        sz[v] += sz[u];
        h[v] = max(h[v], h[u] + 1);
    }
    tout[v] = tcur;
}

int up[LOG][N];
void up_init() {
    copy(par, par + n, up[0]);
    for (int l = 0; l + 1 < LOG; ++l) {
        for (int i = 0; i < n; ++i) {
            up[l + 1][i] = up[l][up[l][i]];
        }
    }
}

int head[N];
vector<int> decomp[N];
void ladder(int v) {
    head[v] = v;
    if (g[v].empty()) {
        decomp[v].push_back(v);
        return;
    }
    for (int &u : g[v]) {
        ladder(u);
        if (d[g[v][0]] < d[u]) {
            swap(g[v][0], u);
        }
    }
    head[v] = head[g[v][0]];
    decomp[head[v]].push_back(v);
}

int la(int v, int k) {
    if (d[v] <= k) {
        return 0;
    }
    v = up[31 - __builtin_clz(k)][v];
    k -= (1 << (31 - __builtin_clz(k)));
    return decomp[head[v]][k + d[head[v]] - d[v]];
    // while (k) {
    //     v = up[31 - __builtin_clz(k)][v];
    //     k -= (1 << (31 - __builtin_clz(k)));
    // }
    // return v;
}

int main() {
    // freopen("in", "r", stdin);
    int m;
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        cin >> par[i];
        g[par[i]].push_back(i);
    }
    dfs_init(0);
    up_init();
    ladder(0);
    for (int i = 0; i < n; ++i) {
        if (decomp[i].empty())
            continue;
        int last = decomp[i].back();
        int len = decomp[i].size();
        for (int j = 0; j < len; ++j) {
            last = par[last];
            decomp[i].push_back(last);
        }
    }

    int a1, a2;
    cin >> a1 >> a2;
    ll x, y, z;
    cin >> x >> y >> z;
    int ans = 0;
    ll sum = 0;
    for (int i = 0; i < m; ++i) {
        // cin >> a1 >> a2;
        ans = la((ans + a1) % n, a2);
        // cout << la(a1, a2) << endl;
        sum += ans;
        int a3 = (x * a1 + y * a2 + z) % n;
        int a4 = (x * a2 + y * a3 + z) % n;
        a1 = a3;
        a2 = a4;
    }
    cout << sum;
    return 0;
}
