#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 1e5;
const int LOG = 19;
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

a2 mn[LOG][N * 2 - 1];
int sz_e;
int head_euler[N];
void euler_write(int v, int p = -1) {
    mn[0][sz_e++] = {d[v], v};
    head_euler[v] = sz_e - 1;
    for (int u : g[v]) {
        if (u == p)
            continue;
        euler_write(u, v);
        mn[0][sz_e++] = {d[v], v};
    }
}
// a1=2, a2=1, a3=0, a4=1
// q1 = 2, 1, ans=1
// q2 = 1, 1, ans=1

void euler_init() {
    euler_write(0);
    for (int l = 0; l + 1 < LOG; ++l) {
        for (int i = 0; i + (1 << l) < 2 * n - 1; ++i) {
            mn[l + 1][i] = min(mn[l][i], mn[l][i + (1 << l)]);
        }
    }
}

int get_lca_euler(int l, int r) {
    l = head_euler[l];
    r = head_euler[r];
    if (l > r)
        swap(l, r);
    r++;
    int lg = 31 - __builtin_clz(r - l);
    return min(mn[lg][l], mn[lg][r - (1 << lg)])[1];
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
    euler_init();
    int a1, a2;
    cin >> a1 >> a2;
    ll x, y, z;
    cin >> x >> y >> z;
    int ans = 0;
    ll sum = 0;
    for (int i = 0; i < m; ++i) {
        ans = get_lca_euler((ans + a1) % n, a2);
        sum += ans;
        int a3 = (x * a1 + y * a2 + z) % n;
        int a4 = (x * a2 + y * a3 + z) % n;
        a1 = a3;
        a2 = a4;
    }
    cout << sum;
    return 0;
}
