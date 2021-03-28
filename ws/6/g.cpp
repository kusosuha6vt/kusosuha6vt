#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

typedef array<ll, 2> p2;

const int N = 2000;
ll a[N];
ll dp[N][N];  // [l][r]
ll p[N][N];
ll s[N + 1];

void calc(int l, int r, int L, int R, int len) {
    if (l > r) {
        return;
    }
    // [l; m]
    int m = (l + r) / 2;
    dp[m][m + len - 1] = LLONG_MAX;
    for (int i = max(L, m); i <= min(R, m + len - 2); ++i) {
        if (dp[m][m + len - 1] > dp[m][i] + dp[i + 1][m + len - 1] + s[m + len] - s[m]) {
            dp[m][m + len - 1] = dp[m][i] + dp[i + 1][m + len - 1] + s[m + len] - s[m];
            p[m][m + len - 1] = i;
        }
    }
    // cout << "dp[" << m << "][" << m + len - 1 << "] = " << dp[m][m + len -  1] << '\n';
    // cout << "p = " << p[m][m + len - 1] << '\n';
    calc(l, m - 1, L, p[m][m + len - 1], len);
    calc(m + 1, r, p[m][m + len - 1], R, len);
}

void print_ans(int l, int r, string &s) {
    if (l > r) return;
    if (l == r) {
        cout << s << '\n';
        return;
    }
    s.push_back('0');
    print_ans(l, p[l][r], s);
    s.back() = '1';
    print_ans(p[l][r] + 1, r, s);
    s.pop_back();
}

int main() {
    freopen("codes.in", "r", stdin);
    freopen("codes.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        s[i + 1] = s[i] + a[i];
        dp[i][i] = 0;
        p[i][i] = i;
    }

    for (int len = 2; len <= n; ++len) {
        calc(0, n - len, 0, n - 1, len);
    }
    string s;
    print_ans(0, n - 1, s);

    return 0;
}
