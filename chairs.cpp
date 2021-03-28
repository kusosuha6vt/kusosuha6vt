#include <bits/stdc++.h>
#define all(a) (a).begin(), (a).end()
//#define int long long

using namespace std;

template <typename T>
istream &operator >> (istream &in, vector<T> &a) {
    for (auto &u : a) {
        in >> u;
    }
    return in;
}

typedef tuple<int, int, int> t3;
typedef tuple<int, int, int, int> t4;
typedef long long ll;
typedef pair<int, int> pi;
typedef long double ld;

struct rng {
    int l, r;
};

const int N = 4e5 + 10;
int n, m, k;
int h[N];
int l[N / 2], r[N / 2];
rng p[N / 2];
ll f[N]; /// f[0...n) c [0...k)
int g[N];
ll pref[N];

inline int getDist(int lb, int rb, int val) {
    if (val < lb) {
        return lb - val;
    } else if (val > rb) {
        return val - rb;
    } else {
        return 0;
    }
}

inline ll check(ll *arr, int pos, int add) {
    if (pos < 0) {
        return 0;
    } else if (pos >= 2 * m) {
        return arr[add + 2 * m - 1];
    } else {
        return arr[add + pos];
    }
}

void rec(int fl, int fr, int kl, int kr) {
    int mid = (fl + fr) / 2;
    f[mid] = numeric_limits<ll>::max();
    int ind = -1;
    for (int i = kl; i <= kr; ++i) {
        ll cur = 0;
//        for (int j = 0, cur_h = 2 * mid; j < m; ++j, cur_h += (n << 1)) {
//            cur += getDist(l[i], r[i], h[cur_h]);
//            cur += getDist(l[i], r[i], h[cur_h + 1]);
//        }

        int i0 = lower_bound(g + mid * 2 * m, g + (mid + 1) * 2 * m, l[i]) - g - 2 * m * mid;
        int i1 = upper_bound(g + mid * 2 * m, g + (mid + 1) * 2 * m, r[i]) - g - 2 * m * mid;

        int sz1 = (2 * m - i1);
        cur += (ll) l[i] * i0 - check(pref, i0 - 1, 2 * m * mid);
        cur += pref[2 * m * (mid + 1) - 1] - check(pref, i1 - 1, 2 * m * mid)
                - sz1 * ll(r[i]);

        if (cur < f[mid]) {
            f[mid] = cur;
            ind = i;
        }
    }
    if (fl < mid)
        rec(fl, mid, kl, ind);
    if (mid + 1 < fr)
        rec(mid + 1, fr, ind, kr);
}

void solve() {
    cin >> m >> n >> k;
    for (int i = 0; i < k; ++i) {
        cin >> p[i].l >> p[i].r;
    }
    sort(p, p + k, [](rng fs, rng sc) {
        return tie(fs.l, sc.r) < tie(sc.l, fs.r);
    });
    vector<rng> tmp;
    for (int i = 0; i < k; ++i) {
        if (tmp.empty() || p[i].r > tmp.back().r) {
            tmp.push_back(p[i]);
        }
    }
    k = tmp.size();
    for (int i = 0; i < k; ++i) {
        l[i] = tmp[i].l;
        r[i] = tmp[i].r;
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 2 * n; ++j) {
            cin >> h[i * 2 * n + j];
        }
        sort(h + i * 2 * n, h + (i + 1) * 2 * n);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2 * m; ++j) {
            g[i * 2 * m + j] = h[j / 2 * 2 * n + j % 2 + i * 2];
        }
    }

    for (int i = 0; i < n; ++i) {
        sort(g + i * 2 * m, g + (i + 1) * 2 * m);
    }

    for (int i = 0; i < n; ++i) {
        pref[i * 2 * m] = g[i * 2 * m];
        for (int j = 1; j < 2 * m; ++j) {
            pref[i * 2 * m + j] = pref[i * 2 * m + j - 1] + g[i * 2 * m + j];
        }
    }

    rec(0, n, 0, k - 1);
    ll ans = accumulate(f, f + n, 0LL);
    cout << ans;
}

signed main() {
#ifdef DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    solve();
}
