#define _GLIB_CXX_DEBUG
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 2e5 + 10;
const int LOG = 18;
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

bool is_par(int p, int v) {
    return tin[p] <= tin[v] && tout[v] <= tout[p];
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

int lca(int u, int v) {
    if (is_par(u, v)) {
        return u;
    }
    if (is_par(v, u)) {
        return v;
    }
    for (int i = LOG - 1; i >= 0; --i) {
        if (!is_par(up[i][u], v)) {
            u = up[i][u];
        }
    }
    return up[0][u];
}

int dsu[N];
// typedef array<int, 3> a3;

int main() {
    // freopen("in", "r", stdin);
    int m;
    cin >> m;
    vector<a2> v;
    n = 1;
    for (int i = 0; i < m; ++i) {
        char tp;
        cin >> tp;
        if (tp == '+') {
            int u;
            cin >> u;
            --u;
            par[n] = u;
            g[u].push_back(n);
            dsu[n] = n;
            n++;
        } else {
            if (tp == '-') {
                int u;
                cin >> u;
                v.push_back(a2{-u, -1});
            } else {
                int a, b;
                cin >> a >> b;
                --a;
                --b;
                v.push_back(a2{a, b});
            }
        }
    }
    dfs_init(0);
    up_init();
    for (int i = 0; i < v.size(); ++i) {
        int a = v[i][0];
        int b = v[i][1];
        if (a < 0) {
            dsu[-a - 1] = dsu[par[-a - 1]];
        } else {
            int u = lca(a, b);
            int u0 = u;
            while (dsu[u] != u) {
                u = dsu[u];
            }
            while (u0 != u) {
                int tmp = dsu[u0];
                dsu[u0] = u;
                u0 = tmp;
            }
            cout << u + 1 << '\n';
        }
    }
    return 0;
}
