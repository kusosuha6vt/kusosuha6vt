#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <immintrin.h>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 4000;
const int M = N / 128 + 1;
bitset<N> hor[N];
__uint128_t a[N][M];
__uint128_t res[N][M];

int main() {
    // a <=> hor <=> ver
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    string t;
    for (int i = 0; i < n; ++i) {
        cin >> t;
        for (int j = 0; j < n; ++j) {
            if (t[j] - '0') {
                hor[i][j] = 1;
                a[i][j / 128] = (a[i][j / 128] | (__uint128_t(1) << (127 - j % 128)));
            }
        }
        // ll *f = (ll *) &a[i][0];
        // cout << *f << '\n';
    }

    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            if (hor[i][k]) {
                for (int j = 0; j < M; ++j) {
                    res[i][j] = res[i][j] ^ a[k][j];
                }
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ll *res_ll = (ll *) &res[i];
        for (int j = 0; j < M * 2; ++j) {
            ans += __builtin_popcountll(res_ll[j]);
        }
    }
    cout << ans;

    return 0;
}
    
