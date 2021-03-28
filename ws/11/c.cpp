//#pragma comment(linker, "/STACK:16777216")
#include <bits/stdc++.h>

#define all(a) (a).begin(), (a).end()
#define mid(l, r) (((r) + (l)) >> 1)

using namespace std;
typedef long long ll;
// #define int ll

void set_file(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

mt19937 gen;
typedef uniform_int_distribution<int> uid;
int rnd(int l, int r) {
    return uid(l, r - 1)(gen);
}

const int N = 1 << 21;
const int A = 1e6 + 1000 + 10;
int n, tot, c[N], suf[N], new_c[N], new_suf[N], beg[N], where[N], s[N], pos, x, real_n;
ll res;

int safe(int x) {
    return x >= n ? x - n : x;
}

void build() {
    memset(beg, 0, sizeof(beg));
    for (int i = 0; i < n; ++i) {
        c[i] = s[i];
        beg[c[i] + 1]++;
        suf[i] = i;
    }
    for (int i = 0; i < A - 1; ++i) {
        beg[i + 1] += beg[i];
    }
    for (int l = 0; l < n; l = (l ? l * 2 : 1)) {
        for (int i = 0; i < n; ++i) {
            pos = safe(suf[i] - l + n);
            new_suf[beg[c[pos]]++] = pos;
        }
        tot = 0;
        for (int i = 0; i < n; ++i) {
            if ((i == 0) || (c[new_suf[i - 1]] != c[new_suf[i]]) ||
                c[safe(new_suf[i - 1] + l)] != c[safe(new_suf[i] + l)]) {
                beg[tot++] = i;
            }
            new_c[new_suf[i]] = tot - 1;
        }
        memcpy(suf, new_suf, n * sizeof(suf[0]));
        memcpy(c, new_c, n * sizeof(c[0]));
    }
}

int lcp[N], rsuf[N];
void build_lcp() {
    for (int i = 0; i < n; ++i) {
        rsuf[suf[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n; ++i) {
        k = max(0, k - 1);
        if (rsuf[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = suf[rsuf[i] + 1];
        while (s[i + k] == s[j + k]) {
            k++;
        }
        lcp[rsuf[i]] = k;
    }
}

int f[N];
void add_(int i, int val) {
    for (; i < N; i |= (i + 1)) {
        f[i] += val;
    }
    // f[i] += val;
}

int get_() {
    int *t = f - 1;
    int *e = f + N;
    int k = 0;
    for (int i = 21; i >= 0; --i) {
        if (t + k + (1 << i) < e && t[k + (1 << i)] == 0) {
            k += (1 << i);
        }
    }
    return k;
    // int i;
    // for (i = 0; !f[i]; ++i)
    //     {}
    // return i;
}

//         0  1             2   3          4  5
// 2 + 3 = 5, 0, 100 + 3 = 103, 1, 1 + 3 = 4, 2
// 1 3 5 4 0 2

// 3 + 3, 2 + 3, 0, 3 + 3, 1 + 3, 1 + 3, 1, 2 + 3, 2
// 9 5 0 6 4 4 1 5 2
// 0 1 2 3 4 5 6 7 8
// 2 6 8 5 4 1 7 3 0


int tp_s[N];
int vals[N];
void solve() {
    // freopen("in", "r", stdin);
    int m;
    cin >> m;
    n = 0;
    for (int i = 0; i < m; ++i) {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; ++j) {
            tp_s[n] = 1;
            cin >> s[n++];
            s[n - 1] += 1;
            vals[n - 1] = s[n - 1];
        }
        s[n++] = 1e9 + 10 + 2 * m + i;
        vals[n - 1] = s[n - 1];
    }
    s[n++] = 0;
    vals[n - 1] = 0;
    sort(vals, vals + n);
    int sz_vals = unique(vals, vals + n) - vals;
    for (int i = 0; i < n; ++i) {
        s[i] = lower_bound(vals, vals + sz_vals, s[i]) - vals;
    }
    build();
    build_lcp();
    for (int i = 0; i < n; ++i) {
        if (s[i] != 0 && ((i - 1 < 0) || tp_s[i - 1] == 0)) {
            add_(rsuf[i], 1);
        }
    }
    for (int i = 0; i < n - m - 1; ++i) {
        int j = get_();
        cout << vals[s[suf[j]]] - 1 << ' ';
        add_(j, -1);
        if (tp_s[suf[j]] == tp_s[suf[j] + 1]) {
            add_(rsuf[suf[j] + 1], 1);
        }
    }
    // for (int i = 0; i < n; ++i) {
    //     if (s[suf[i]] >= m) {
    //         cout << s[suf[i]] - m << ' ';
    //     }
    // }
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
