#include <vector>
#include <cmath>
#include <iostream>
#include <climits>
#include <algorithm>
#include <array>
#include <complex>
#include <cassert>

// #include <immintrin.h>
#define db(x) cerr << #x << " = " << x << endl;
// #define endl '\r'

using namespace std;
// #pragma GCC target("abm,mmx,sse,sse2,sse3,ssse3,sse4,avx,popcnt,avx2,tune=native")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

template<typename T>
ostream &operator << (ostream &out, const vector<T> &v) {
    for (const T &u : v) {
        out << u << ' ';
    }
    out << endl;
    return out;
}

typedef long long ll;
typedef unsigned int ui;
typedef array<int, 2> p;
typedef long double ld;

const int N = 1 << 19;
const int M = 998244353;  // 2^23 * 7 * 17 + 1

int pw(ll t, int p) {
    int ans = 1;
    for (; p; p >>= 1) {
        if (p & 1) {
            ans = (ll(ans) * t) % M;
        }
        t = t * t % M;
    }
    return ans;
}

void fft(int n, int *a, int step, int *y, int x) {
    if (n == 1) {
        y[0] = a[0];
        return;
    }
    fft(n >> 1, a, step << 1, y, (ll)x * x % M);
    fft(n >> 1, a + step, step << 1, y + (n >> 1), (ll)x * x % M);
    ll t = 1;
    for (int i = 0; i < (n >> 1); ++i) {
        int fs = y[i];
        int sc = y[i + (n >> 1)];
        y[i] = (fs + t * sc) % M;
        y[i + (n >> 1)] = (fs - t * sc % M + M) % M;
        t = t * x % M;
    }
}

int a[N], b[N], ay[N], by[N], cy[N], c[N];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    n = 1 << n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    n <<= 1;
    int r = pw(3, (M - 1) / n);
    int r3 = pw(r, M - 2);
    fft(n, a, 1, ay, r);
    fft(n, b, 1, by, r);
    for (int i = 0; i < n; ++i) {
        cy[i] = (ll)ay[i] * by[i] % M;
    }
    fft(n, cy, 1, c, r3);
    int rn = pw(n, M - 2);
    for (int i = 0; i < n; ++i) {
        c[i] = (ll)c[i] * rn % M;
    }
    for (int i = 0; i < n; ++i) {
        cout << c[i] << ' ';
    }
    cout << endl;
    return 0;
}
