#include <bits/stdc++.h>
#define int long long
#define all(a) a.begin(), a.end()
using namespace std;

typedef long long ll;

int n;
string s;
vector<ll> d1, d2;
int l1 = 0, r1 = -1, l2 = 0, r2 = -1;

void extend1(int pos) {
    ll k = 0;
    int j = (r1 - pos) + l1;
    if (pos <= r1) {
        k = min(r1 - pos + 0LL, d1[j]);
    }
    while (pos + k < n && pos - k >= 0 && s[pos + k] == s[pos - k])
        ++k;
    d1[pos] = k;
    if (r1 < pos + k - 1) {
        r1 = pos + k - 1;
        l1 = pos - k + 1;
        /// abcba
    }
}

void extend2(int pos) {
    int j = (r2 - pos) + l2;
    ll k = 0;
    if (pos < r2) {
        k = min(r2 - pos + 0LL, d2[j - 1]);
    }
    while (pos + k + 1 < n && pos - k >= 0 && s[pos + k + 1] == s[pos - k])
        ++k;
    d2[pos] = k;
    if (pos + k > r2) {
        r2 = pos + k;
        l2 = pos - k + 1;
        /// 012345
        /// abccba
    }
}

void solve() {
    for (int i = 0; i < n; ++i) {
        extend1(i);
        extend2(i);
    }
}

signed main() {
    cin >> s;
    n = s.size();
    d1.assign(n, 0);
    d2.assign(n, 0);
    
    solve();
    
//  for (int u : d1)
//      cout << u << ' ';
//      cout << endl;
//  for (int u : d2)
//      cout << u << ' ';
//  cout << endl;
    
    cout << accumulate(all(d1), 0LL) + accumulate(all(d2), 0LL) << endl;
    
    return 0;
}
