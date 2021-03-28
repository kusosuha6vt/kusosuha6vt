#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

typedef array<ll, 2> p2;

const int N = 2e5;
p2 a[N];
p2 b[N];

struct Line {
    ll k, b;
    ll operator ()(ll x) {
        return k * x + b;
    }
};
ll inter(Line l1, Line l2) {
    return (l1.b - l2.b) / (l2.k - l1.k);
}
Line c[N];
int sz;

void add(Line l) {
    while (sz >= 2 && inter(c[sz - 2], c[sz - 1]) >= inter(c[sz - 2], l))
        sz--;
    c[sz++] = l;
}

ll get(ll x) {
    int l = -1, r = sz - 1;
    while (l + 1 < r) {
        int m = (l + r) >> 1;
        if (inter(c[m], c[m + 1]) <= x) {
            l = m;
        } else {
            r = m;
        }
    }
    return c[r](x);
}

ll dp[N];

int main() {
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1];
    }
    sort(a, a + n);
    int m = 0;
    for (int i = 0; i < n; ++i) {
        while (m && b[m - 1][0] <= a[i][0] && b[m - 1][1] <= a[i][1])
            m--;
        b[m++] = a[i];
    }

    add(Line{b[0][1], 0});
    dp[0] = get(b[0][0]);
    // cout << dp[0] << ' ';
    for (int i = 1; i < m; ++i) {
        add(Line{b[i][1], dp[i - 1]});
        dp[i] = get(b[i][0]);
        // cout << dp[i] << ' ';
    }
    cout << dp[m - 1];

    return 0;
}
