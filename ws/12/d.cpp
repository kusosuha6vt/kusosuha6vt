#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int LOG = 17;
const int N = 1 << LOG;
vector<int> g[N];
ll s[N], anc[N], tin[N], tout[N], tcur, c[N];
ll t[N * 2];
ll head[N], d[N];

void set_pos(int i, int v) {
    for (t[i += N] = v; i > 1; i >>= 1) {
        t[i >> 1] = t[i] + t[i ^ 1];
    }
}

ll get(int l, int r) {
    ll ans = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            ans = ans + t[l++];
        }
        if (r & 1) {
            ans = ans + t[--r];
        }
    }
    return ans;
}

void sizes(int v, int p) {
    for (int i = 0; i < g[v].size(); ++i) {
        if (g[v][i] == p) {
            swap(g[v].back(), g[v][i]);
            g[v].pop_back();
            break;
        }
    }
    anc[v] = p;
    s[v] = 1;
    for (int &u : g[v]) {
        d[u] = d[v] + 1;
        sizes(u, v);
        s[v] += s[u];
        if (s[u] > s[g[v][0]]) {
            swap(g[v][0], u);
        }
    }
}

void hld(int v) {
    tin[v] = tcur++;
    set_pos(tin[v], c[v]);
    for (int u : g[v]) {
        head[u] = (u == g[v][0] ? head[v] : u);
        hld(u);
    }
    tout[v] = tcur;
}

bool is_parent(int p, int v) {
    return tin[p] <= tin[v] && tout[v] <= tout[p];
}

void up(int &a, int &b, ll &ans) {
    while (!is_parent(head[a], b)) {
        ans = ans + get(tin[head[a]], tin[a] + 1);
        a = anc[head[a]];
    }
}

ll get_hld(int a, int b) {
    ll ans = 0;
    up(a, b, ans);
    up(b, a, ans);
    if (!is_parent(a, b)) {
        swap(a, b);
    }
    ans = ans + get(tin[a], tin[b] + 1);
    return ans;
}

int main() {
    // freopen("in", "r", stdin);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    sizes(0, 0);
    hld(0);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        char tp;
        cin >> tp;
        if (tp == '?') {
            int a, b;
            cin >> a >> b;
            --a;
            --b;
            cout << get_hld(a, b) << '\n';
        } else {
            int a, b;
            cin >> a >> b;
            --a;
            set_pos(tin[a], b);
        }
    }
    return 0;
}
