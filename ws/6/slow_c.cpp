#include <bits/stdc++.h>

using namespace std;
typedef long ll;

struct Line {
    ll k, m;
    ll operator[](ll x) {
        return k * x + m;
    }
    Line(ll k = 0, ll m = LLONG_MIN) : k(k), m(m) {}
};

const int N = 1e5;
int n;
ll x[N], c[N], t_[N], dp[N];

const int M = 2e6 + 1;
const int SH = 1e6;
Line t[M * 4];

// l = 0...M-1
// real_l = l - 1e6

void add(int v, int l, int r, int ql, int qr, Line L) {
    if (r <= ql || qr <= l) {
        return;
    }
    int mid = (l + r) / 2;
    if (ql <= l && r <= qr) {
        bool MID = L[mid - SH] > t[v][mid - SH];
        bool LEFT = L[l - SH] > t[v][l - SH];
        if (MID) {
            swap(t[v], L);
        }
        if (r - l == 1) {
            return;
        }
        if (MID != LEFT) {
            add(v * 2, l, mid, ql, qr, L);
        } else {
            add(v * 2 + 1, mid, r, ql, qr, L);
        }
        return;
    }
    add(v * 2, l, mid, ql, qr, L);
    add(v * 2 + 1, mid, r, ql, qr, L);
}

ll get(int v, int l, int r, int x) {
    if (r - l == 1) {
        return t[v][x - SH];
    }
    int mid = (l + r) / 2;
    ll ans = t[v][x - SH];
    if (x < mid) {
        ans = max(ans, get(v * 2, l, mid, x));
    } else {
        ans = max(ans, get(v * 2 + 1, mid, r, x));
    }
    return ans;
}

ll solve_fast() {
    fill(t, t + M * 4, Line());
    // int n;
    // cin >> n;
    // for (int i = 0; i < n; ++i) {
    //     long long v1, v2, v3;
    //     cin >> v1 >> v2 >> v3;
    //     x[i] = v1;
    //     c[i] = v2;
    //     t_[i] = v3;
    // }
    dp[0] = 0;
    // lc.add(c[0], -x[0] * c[0]);
    // x[j] - x[i]
    add(1, 0, M, 0, SH + x[0], Line{-c[0], 0 + c[0] * x[0]});
    add(1, 0, M, SH + x[0], M, Line{+c[0], 0 - c[0] * x[0]});
        // cout << dp[0] << endl;

    // dp[i] = t[i] + c[j] * (x[i] - x[j]) + dp[j]
    // = ((dp[j] - x[j] * c[j]) + c[j] * x[i]) + t[i]
    for (int i = 1; i < n; ++i) {
        dp[i] = t_[i] + get(1, 0, M, SH + x[i]);
        // cout << dp[i] << endl;
        add(1, 0, M, 0, SH + x[i], Line{-c[i], dp[i] + c[i] * x[i]});
        add(1, 0, M, SH + x[i], M, Line{+c[i], dp[i] - c[i] * x[i]});
    }
    return (long long)(dp[n - 1]);
}

ll solve_slow() {
    // int n;
    // cin >> n;
    // for (int i = 0; i < n; ++i) {
    //     long long v1, v2, v3;
    //     ss >> v1 >> v2 >> v3;
    //     x[i] = v1;
    //     c[i] = v2;
    //     t_[i] = v3;
    // }
    dp[0] = 0;

    for (int i = 1; i < n; ++i) {
        dp[i] = LLONG_MIN;
        for (int j = 0; j < i; ++j) {
            dp[i] = max(dp[i], dp[j] + t_[i] + c[j] * abs(x[j] - x[i]));
        }
    }
    return (long long)(dp[n - 1]);
}

void stress() {
    mt19937 gen;
    int iters = 100;
    for (int i = 0; i < iters; ++i) {
        cout << "Test " << i << endl;
        gen.seed(i);
        n = uniform_int_distribution<int>(1, 5)(gen);
        for (int j = 0; j < n; ++j) {
            x[j] = uniform_int_distribution<int>(-15, 15)(gen);
            c[j] = uniform_int_distribution<int>(-15, 15)(gen);
            t_[j] = uniform_int_distribution<int>(-15, 15)(gen);
        }
        if (solve_fast() != solve_slow()) {
            cout << "WA!\n";
            cout << "slow: " << solve_slow() << ", fast: " << solve_fast() << '\n';
            cout << n << endl;
            for (int j = 0; j < n; ++j) {
                cout << x[j] << ' ' << c[j] << ' ' << t_[j] << '\n';
            }
            return;
        } else {
            cout << "[Ok]\n";
        }
    }
}

int main() {
    // freopen("in", "r", stdin);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> c[i] >> t_[i];
    }
    // cout << n << endl << n << endl << n << endl;
    cout << solve_fast();
    // stress();
    return 0;
}
