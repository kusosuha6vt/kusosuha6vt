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
 
const int N = 200000 * 2, A = 'z' - 'a' + 1 + 200000;
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
 
int t[N];
void add(int i, int v, int n) {
    for (; i < n; i = i | (i + 1)) {
        t[i] += v;
    }
}
 
int sum(int i, int n) {
    int ans = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1) {
        ans += t[i];
    }
    return ans;
}
 
int sum(int l, int r, int n) {
    return sum(r, n) - sum(l - 1, n);
}
 
int st[N];
void f(int *a, int n) {
    int m = 0;
    st[m++] = -1;
    for (int i = 0; i < n; ++i) {
        while (m > 1 && lcp[st[m - 1]] >= lcp[i])
            m--;
        a[i] = i - st[m - 1];
        st[m++] = i;
    }
}
 
int l[N], r[N], tp[N];
typedef tuple<int, int, int> ti;
ti y[N];
int last[N];
int ans[N];
void solve() {
    int k;
    cin >> k;
    int n = 0;
    for (int i = 0; i < k; ++i) {
        string s_;
        cin >> s_;
        for (char it : s_) {
            s[n++] = int(it) - 'a' + k;
            tp[n - 1] = i;
        }
        s[n++] = i;
    }
    build(n);
    build_lcp(n);
    f(l, n - 1);
    reverse(lcp, lcp + n);
    f(r, n - 1);
    reverse(lcp, lcp + n);
    reverse(r, r + n);
    int it = 0;
    for (int i = k; i < n - 1; ++i) {
        y[it++] = {i + r[i], i - l[i] + 1, lcp[i]};
    }
    sort(y, y + it);
    fill(last, last + k, -1);
    int ___ = it;
    it = 0;
    for (int i = k; i < n; ++i) {
        int j = p[i];
        if (last[tp[j]] != -1) {
            add(last[tp[j]], -1, n);
        }
        last[tp[j]] = i;
        add(i, 1, n);
        while (it < ___ && get<0>(y[it]) == i) {
            int lb = get<1>(y[it]);
            int val = get<2>(y[it]);
            it++;
            int cnt = sum(lb, i, n);
            ans[cnt] = max(ans[cnt], val);
        }
    }
    for (int i = k; i >= 3; i --) {
        ans[i - 1] = max(ans[i], ans[i - 1]);
    }
    for (int i = 2; i <= k; ++i) {
        cout << ans[i] << '\n';
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
