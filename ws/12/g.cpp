#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#include <immintrin.h>
#include <bits/stdc++.h>

using namespace std;

const int N = 4000;
const int M = N / 256 + 1;
__m256i a[N][M];
__m256i at[N][M];
bitset<N> ab[N];
unsigned int f[N + 600];

int main() {
    freopen("in", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    string t;
    for (int i = 0; i < n; ++i) {
        cin >> t;
        cin >> t;
        for (int j = 0; j < n; ++j)
            ab[i][j] = t[j] - '0';
        memset(f, 0, sizeof(f));
        for (int j = 0; j < n; ++j) {
            if (ab[i][j]) {
                f[j / 32] = f[j / 32] | (1u << (31 - j % 32));
            }
        }
        for (int j = 0; j < M; ++j) {
            a[i][j] = _mm256_lddqu_si256(reinterpret_cast<const __m256i *>(f + 8 * j));
        }
    }

    for (int j = 0; j < n; ++j) {
        memset(f, 0, sizeof(f));
        for (int i = 0; i < n; ++i) {
            if (ab[i][j]) {
                f[i / 32] = f[i / 32] | (1u << (31 - i % 32));
            }
        }
        for (int i = 0; i < M; ++i) {
            at[j][i] = _mm256_lddqu_si256(reinterpret_cast<const __m256i *>(f + 8 * i));
        }
    }

    __m256i ans = _mm256_setzero_si256();
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < M; ++k) {
            ans = _mm256_and_si256(ans, _mm256_and_si256(a[i][k], at[i][k]));
        }
    }

    int popcnt = 0;
    ll *it = (ll *)&ans;
    for (int i = 0; i < 4; ++i) {
        popcnt += __builtin_popcnt(it[i]);  
    }
    cout << popcnt;

    return 0;
}
