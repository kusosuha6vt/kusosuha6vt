#include <vector>
#include <cmath>
#include <iostream>
#include <climits>
#include <algorithm>
#include <array>
#include <complex>
#include <cassert>
#define complex complex<double>

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
#define double ld
// struct complex {
//     double a, b;
//     complex operator + (const complex &o) const {
//         return {a + o.a, b + o.b};
//     }
//     complex operator - (const complex &o) const {
//         return {a + o.a, b + o.b};
//     }
//     complex operator * (const complex &o) const {
//         return {a * o.a - b * o.b, a * o.b + b * o.a};
//     }
//     complex operator * (double x) const {
//         return {a * x, b * x};
//     }
//     complex operator / (double x) const {
//         return {a / x, b / x};
//     }
// };

void fft(complex *a, int st, complex *res, int n, complex x) {
    if (n == 1) {
        res[0] = a[0];
        return;
    }
    fft(a, st << 1, res, n >> 1, x * x);
    fft(a + st, st << 1, res + (n >> 1), n >> 1, x * x);
    complex m = {1., 0.};
    for (int i = 0; i < (n >> 1); ++i) {
        auto fs = res[i];
        auto sc = res[i + (n >> 1)];
        res[i] = fs + sc * m;
        res[i + (n >> 1)] = fs - sc * m;
        m = m * x;
    }
}

complex root_(int n) {
    return {cos(M_PI * 2 / n), sin(M_PI * 2 / n)};
}

complex rev(complex c) {
    return {c.real(), -c.imag()};
}

const int N = 1 << 20;
complex a[N], b[N], ya[N], yb[N], yc[N], c[N];

signed main() {
    string s1, s2;
    cin >> s1 >> s2;
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    int sg = 1;
    if (s1.back() == '-') {
        s1.pop_back();
        sg *= -1;
    }
    if (s2.back() == '-') {
        s2.pop_back();
        sg = -sg;
    }
    for (int i = 0; i < s1.size(); ++i) {
        a[i] = {s1[i] - '0', 0};
    }
    for (int i = 0; i < s2.size(); ++i) {
        b[i] = {s2[i] - '0', 0};
    }

    fft(a, 1, ya, N, root_(N));
    fft(b, 1, yb, N, root_(N));
    for (int i = 0; i < N; ++i) {
        yc[i] = ya[i] * yb[i];
    }
    fft(yc, 1, c, N, rev(root_(N)));
    ll add = 0;
    string ans;
    for (int i = 0; i < N; ++i) {
        ll x = ll((c[i] / (double)N).real() + add + 0.5);
        add = x / 10;
        assert(x >= 0);
        ans.push_back(x % 10 + '0');
    }
    while (ans.size() > 1 && ans.back() == '0') ans.pop_back();
    reverse(ans.begin(), ans.end());
    if (sg < 0 && ans != "0") cout << '-';
    cout << ans;

    cout << endl;
    return 0;
}
