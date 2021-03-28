//#pragma comment(linker, "/STACK:16777216")
#include <bits/stdc++.h>
 
#define all(a) (a).begin(), (a).end()
#define mid(l, r) (((r) + (l)) >> 1)
 
using namespace std;
typedef long long ll;
//#define int ll
 
void set_file(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}
 
mt19937 gen;
typedef uniform_int_distribution<int> uid;
int rnd(int l, int r) {
    return uid(l, r - 1)(gen);
}
 
const int N = 400005, A = 11;
int s[N], p[N], pn[N], c[N], cn[N], b[N], lcp[N], rp[N];
 
int safe(int x, int n) {
    return x >= n ? x - n : x;
}
 
void build(int n) {
    memset(b, 0, n * sizeof(b[0]));
    for (int i = 0; i < n; ++i) {
        c[i] = s[i];
        p[i] = i;
        b[1 + s[i]]++;
    }
    partial_sum(b, b + A + 1, b);
    for (int l = 0; l < n; l = (l ? l << 1 : 1)) {
        for (int i = 0; i < n; ++i) {
            int j = safe(p[i] - l + n, n);
            pn[b[c[j]]++] = j;
        }
        int t = 0;
        for (int i = 0; i < n; ++i) {
            if (i == 0 || c[pn[i]] != c[pn[i - 1]] || c[safe(pn[i] + l, n)] != c[safe(pn[i - 1] + l, n)])
                b[t++] = i;
            cn[pn[i]] = t - 1;
        }
        memcpy(c, cn, n * sizeof(c[0]));
        memcpy(p, pn, n * sizeof(p[0]));
    }
}
 
void build_lcp(int n) {
    for (int i = 0; i < n; ++i) {
        rp[p[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (rp[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rp[i] + 1];
        while (max(i, j) + k < n && s[i + k] == s[j + k])
            k++;
        lcp[rp[i]] = k;
        k = max(0, k - 1);
    }
}
 
int st[N];
 
void f(int n, int *l) {
    int k = 0;
    st[k++] = -1;
    for (int i = 0; i < n; ++i) {
        while (k > 1 && lcp[st[k - 1]] >= lcp[i])
            k--;
        l[i] = i - st[k - 1];
        st[k++] = i;
    }
}
 
int l[N], r[N];
void solve() {
    freope("in", "r", stdin);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    build(n + 1);
    build_lcp(n + 1);
 
    f(n, l);
    reverse(lcp, lcp + n);
    f(n, r);
    reverse(lcp, lcp + n);
    reverse(r, r + n);
 
    ll ans = 1;
    for (int i = 1; i < n; ++i) {
        if (ll(l[ans] + r[ans]) * lcp[ans] < ll(l[i] + r[i]) * lcp[i]) {
            ans = i;
        }
    }
    if (lcp[ans] * ll(l[ans] + r[ans]) < n) {
        cout << n << '\n' << n << '\n';
        for (int i = 0; i < n; ++i) {
            cout << s[i] << ' ';
        }
        return;
    }
    cout << lcp[ans] * ll(l[ans] + r[ans]) << '\n' << lcp[ans] << '\n';
    for (int i = 0; i < lcp[ans]; ++i) {
        cout << s[p[ans] + i] << ' ';
    }
}
 
signed main() {
#ifdef LOCAL_DEFINE
    freopen("input.txt", "r", stdin);
#else
//    set_file("game");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
//    set_file("memory");
#endif
    solve();
    return 0;
}
