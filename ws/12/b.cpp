#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 1e6;
const int LOG = 1;
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

// int up[LOG][N];
// void up_init() {
//     copy(par, par + n, up[0]);
//     for (int l = 0; l + 1 < LOG; ++l) {
//         for (int i = 0; i < n; ++i) {
//             up[l + 1][i] = up[l][up[l][i]];
//         }
//     }
// }

a2 mn[LOG][N * 2 - 1];
int sz_e;
int head_euler[N];
int tail_euler[N];
void euler_write(int v, int p = -1) {
    mn[0][sz_e++] = {d[v], v};
    head_euler[v] = sz_e - 1;
    tail_euler[v] = sz_e - 1;
    for (int u : g[v]) {
        if (u == p)
            continue;
        euler_write(u, v);
        mn[0][sz_e++] = {d[v], v};
        tail_euler[v] = sz_e - 1;
    }
}

// void euler_init() {
//     euler_write(0);
//     for (int l = 0; l + 1 < LOG; ++l) {
//         for (int i = 0; i + (1 << l) < 2 * n - 1; ++i) {
//             mn[l + 1][i] = min(mn[l][i], mn[l][i + (1 << l)]);
//         }
//     }
// }

// int get_lca_euler(int l, int r) {
//     l = head_euler[l];
//     r = head_euler[r];
//     if (l > r)
//         swap(l, r);
//     r++;
//     int lg = 31 - __builtin_clz(r - l);
//     return min(mn[lg][l], mn[lg][r - (1 << lg)])[1];
// }


int c[N];
int ans[N];
typedef array<int, 3> a3;
a3 q[N];
int cs[N];
int t[N];
int cnt_set;

void insrt(int k) {
    cs[k]++;
    if (cs[k] == 1) {
        cnt_set++;
    }
}

void ers(int k) {
    cs[k]--;
    if (cs[k] == 0)
        cnt_set--;
}

int main() {
    // freopen("in", "r", stdin);
    cin >> n;
    int root = -1;
    for (int i = 0; i < n; ++i) {
        cin >> par[i] >> c[i];
        par[i]--;
        c[i]--;
        if (par[i] == -1) {
            root = i;
        }
        g[par[i]].push_back(i);
    }
    dfs_init(root);
    euler_write(root);
    for (int i = 0; i < n; ++i) {
        q[i] = {head_euler[i], tail_euler[i] + 1, i};
    }
    const int B = 1000;
    stable_sort(q, q + n, [](a3 a, a3 b) {
        int fs = a[0] / B;
        int sc = b[0] / B;
        return make_pair(fs, ((fs & 1) ? -a[1] : a[1])) < make_pair(sc, ((sc & 1) ? -b[1] : b[1]));
    });

    int l = 0, r = 0;
    for (int i = 0; i < n; ++i) {
        int l0 = q[i][0], r0 = q[i][1];
        while (l0 < l) {
            l--;
            insrt(c[mn[0][l][1]]);
        }
        while (r < r0) {
            insrt(c[mn[0][r][1]]);
            r++;
        }
        while (l < l0) {
            ers(c[mn[0][l][1]]);
            l++;
        }
        while (r0 < r) {
            --r;
            ers(c[mn[0][r][1]]);
        }
        ans[q[i][2]] = cnt_set;
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << ' ';
    }
    return 0;
}
