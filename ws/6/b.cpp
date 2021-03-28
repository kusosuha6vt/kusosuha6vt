#include <bits/stdc++.h>

using namespace std;

const int N = 4000;
int a[N + 1][N + 1];
int dp[N + 1][N + 1];
int p[N + 1][N + 1];

inline int f(int l, int r) {
    return (a[r][r] - (a[l][r] << 1) + a[l][l]) >> 1;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i + 1][j + 1];
            a[i + 1][j + 1] += a[i][j + 1] + a[i + 1][j] - a[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        p[i + 1][k] = n;
    }

    for (int i = 0; i <= k; ++i) {
        dp[0][i] = INT_MAX;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = k - 1; j >= 0; --j) {
            dp[i][j] = INT_MAX;
            if (j == 0) {
                dp[i][j] = f(0, i);
                // cout << "cool beg " << i << " " << j << '\n';
                // cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << '\n';
                continue;
            }
            // cout << "beg " << i << " " << j << '\n';
            for (int m = (dp[i - 1][j] == INT_MAX ? 0 : p[i - 1][j]);
                m <= min((dp[i][j + 1] == INT_MAX ? n - 1 : p[i][j + 1]), i - 1); m++) {
                // cout << "- " << m << " " << dp[m][j - 1] << " " << f(m, i) << '\n';
                if (dp[m][j - 1] != INT_MAX && dp[i][j] > dp[m][j - 1] + f(m, i)) {
                    dp[i][j] = dp[m][j - 1] + f(m, i);
                    p[i][j] = m;
                }
            }
            // cout << "dp[" << i << "][" << j << "] = " << dp[i][j] << '\n';
        }
    }
    cout << dp[n][k - 1] << '\n';

    return 0;
}
