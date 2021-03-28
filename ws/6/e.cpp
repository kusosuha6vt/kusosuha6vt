#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define cerr if (false) cerr

const int N = 1e5 + 1;
typedef array<ll, 3> a3;
ll d[N];
ll pd[N];
ll kitty[N];
ll t[N];
ll pnt[N];
ll dp[N];
ll pr[N];
ll s[N];

void rec(int l, int r, int L, int R) {
    if (l > r) {
        return;
    }
    int i = (l + r) / 2;
    dp[i + 1] = LLONG_MAX;
    for (int j = L; j <= min(R, i); ++j) {
        ll sum = s[i + 1] - s[j];
        ll mx = t[i];
        ll f = mx * (i + 1 - j) - sum;
        if (pr[j] < LLONG_MAX && dp[i + 1] > pr[j] + f) {
            dp[i + 1] = pr[j] + f;
            pnt[i + 1] = j;
        }
    }
    // cout << "dp[" << i + 1 << "] = " << dp[i + 1] << endl;
    rec(l, i - 1, L, pnt[i + 1]);
    rec(i + 1, r, pnt[i + 1], R);
}

int main() {
    // freopen("in", "r", stdin);
    int n, m, p;
    cin >> n >> m >> p;
    for (int i = 0; i < n - 1; ++i) {
        cin >> d[i];
        pd[i + 1] = pd[i] + d[i];
    }
    for (int i = 0; i < m; ++i) {
        ll h;
        cin >> h >> t[i];
        h--;
        t[i] -= pd[h];
    }
    sort(t, t + m);
    for (int i = 0; i < m; ++i) {
        // cerr << t[i] << ' ';
        s[i + 1] = s[i] + t[i];
    }
    // cerr << endl;
    fill(dp + 1, dp + m + 1, LLONG_MAX);
    for (int _ = 0; _ < p; ++_) {
        swap(dp, pr);
        rec(0, m - 1, 0, m - 1);
        // for (int i = 0; i < m; ++i) {  // i - последняяя кошечка
        //     cerr << "i=" << i << '\n';
        //     dp[i + 1] = LLONG_MAX;
        //     for (int j = 0; j <= i; ++j) {  // j - сколько не берем
        //         ll sum = s[i + 1] - s[j];
        //         ll mx = t[i];
        //         // mx - t[i]
        //         ll f = mx * (i + 1 - j) - sum;
        //         if (pr[j] < LLONG_MAX && dp[i + 1] > pr[j] + f) {
        //         cerr << "sum = " << sum << endl;
        //         cerr << "mx = " << mx << endl;
        //             dp[i + 1] = pr[j] + f;
        //             pnt[i + 1] = j;
        //         }
        //     }
        //     assert(pnt[i] <= pnt[i + 1]);
        //     cerr << "dp =" << dp[i + 1] << '\n';
        // }
        // cerr << endl;
    }
    cout << dp[m];
    return 0;
}
