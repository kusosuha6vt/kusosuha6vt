#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e5 + 1;
 
ll h[N], cost[N];
ll dp[N];
ll pref[N];
 
struct Line {
    ll k, m, p;
};
 
Line st[N + 10];
int sz = 0;
 
ll divf(ll a, ll b) {
    return a / b - ((a ^ b) < 0 && a % b);
}
 
/// k1 x + m1 = k2 x + m2
/// (k1 - k2) x = (m2 - m1)
void add(ll k, ll m) {
    while (sz >= 2 && divf(m - st[sz - 1].m, st[sz - 1].k - k) <= st[sz - 2].p) {
        sz--;
    }
    if (sz) {
        st[sz - 1].p = divf(m - st[sz - 1].m, st[sz - 1].k - k);
    }
    st[sz++] = Line{k, m, LLONG_MAX};
}
 
ll get(ll x) {
    static int i = 0;
    while (st[i].p < x) {
        i++;
    }
    return st[i].k * x + st[i].m;
}
 
int main() {
    freopen("lumber.in", "r", stdin);
    freopen("lumber.out", "w", stdout);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> h[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }
 
    partial_sum(h, h + n, pref + 1);
    add(cost[0], dp[0]);
    for (int i = 1; i < n; ++i) {
        dp[i] = LLONG_MAX;
//        for (int j = 0; j < i; ++j) {
//            dp[i] = min(dp[i], h[i] * cost[j] + dp[j]);
//        }
        dp[i] = get(h[i]);
        add(cost[i], dp[i]);
    }
    cout << dp[n - 1];
}
