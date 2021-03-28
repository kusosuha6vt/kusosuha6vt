//#pragma comment(linker, "/STACK:16777216")
#include <bits/stdc++.h>
 
#define all(a) (a).begin(), (a).end()
 
using namespace std;
typedef long long ll;
//#define int ll
 
void set_file(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}
 
const int N = 2e5;
struct Node {
    int prv;
    int val;
} prv[N];
 
void solve() {
    set_file("stack");
    prv[0] = {-1, -1};
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int t, m;
        cin >> t >> m;
        if (m) {
            prv[i] = {t, m};
        } else {
            prv[i] = prv[prv[t].prv];
            cout << prv[t].val << '\n';
        }
    }
}
 
signed main() {
#ifdef LOCAL_DEFINE
    freopen("input.txt", "r", stdin);
#else
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cout.tie(nullptr);
#endif
    solve();
    return 0;
}
