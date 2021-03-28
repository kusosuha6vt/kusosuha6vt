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
ll x[N], c[N], t_[N], dp[N];

const int M = 2e6 + 1;
Line t[M * 4];

// l = 0...M-1
// real_l = l - 1e6
void add(int v, int l, int r, int ql, int qr, Line L) {
    if (max(l, ql) > min(r, qr)) {
        return;
    }
    if (ql <= l && r <= qr) {
        int mid = (l + r) / 2;
        ll x_l = l - int(1e6), x_m = mid - int(1e6), x_r = r - int(1e6);
        bool b_l = L[x_l] > t[v][x_l];
        bool b_mid = L[x_m] > t[v][x_m];
        if (b_mid) {
            swap(L, t[v]);
        }
        if (b_mid != b_l) {
            add(v * 2, l, mid - 1, ql, qr, L);
        } else {
            add(v * 2 + 1, mid + 1, r, ql, qr, L);
        }
        return;
    }
    int mid = (l + r) / 2;
    add(v * 2, l, mid - 1, ql, qr, L);
    add(v * 2 + 1, mid + 1, r, ql, qr, L);
}

ll get(int v, int l, int r, int x) {
    if (l > r) {
        return LLONG_MIN;
    }
    int mid = (l + r) / 2;
    ll ans = t[v][x - int(1e6)];
    if (x < mid) {
        ans = max(ans, get(v * 2, l, mid - 1, x));
    } else if (x > mid) {
        ans = max(ans, get(v * 2 + 1, mid + 1, r, x));
    }
    return ans;
}

int main() {
    // freopen("in", "r", stdin);
    // dp[i] = get(x) + t[i];
    // abs(xj - xi)
    // for all xi > xj
    //      dp[i] = cj * (xi - xj) <=> xi * cj - xj * cj
    // else
    //      dp[i] = cj * (xj - xi) <=> cj * xj - cj * xi <=> ()
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        long long v1, v2, v3;
        cin >> v1 >> v2 >> v3;
        x[i] = v1;
        c[i] = v2;
        t_[i] = v3;
    }
    dp[0] = 0;

    // lc.add(c[0], -x[0] * c[0]);
    // x[j] - x[i]
    add(1, 0, M - 1, 0,     int(1e6) + x[0], Line{-c[0], 0 + c[0] * x[0]});
    add(1, 0, M - 1, int(1e6) + x[0], M - 1, Line{+c[0], 0 - c[0] * x[0]});
        // cout << dp[0] << endl;

    // dp[i] = t[i] + c[j] * (x[i] - x[j]) + dp[j]
    // = ((dp[j] - x[j] * c[j]) + c[j] * x[i]) + t[i]
    for (int i = 1; i < n; ++i) {
        dp[i] = t_[i] + get(1, 0, M - 1, int(1e6) + x[i]);
        // cout << dp[i] << endl;
        add(1, 0, M - 1, 0, int(1e6) + x[i], Line{-c[i], dp[i] + c[i] * x[i]});
        add(1, 0, M - 1, int(1e6) + x[i], M - 1, Line{c[i], dp[i] - c[i] * x[i]});
    }
    cout << (long long)(dp[n - 1]);
    return 0;
}
