// #include <iostream>
// #include <cmath>
// #include <vector>
// #include <algorithm>
// #include <complex>
#include <bits/stdc++.h>

using namespace std;
typedef double ld;
typedef long long ll;
typedef  int ui;
// typedef complex<ld> cmx;


const int MEM = (1 << 20) * 10;
ui mem[MEM];
ui *ptr = mem;

ui *get_mem(int k) {
    ptr += k;
    assert(ptr <= mem + MEM);
    return ptr - k;
}

struct MyVector {
    int sz = 0;
    int cap = 0;
    ui *ptr = 0;
    ui operator[](int i) const {
        return ptr[i];
    }
    ui &operator[](int i) {
        return ptr[i];
    }
    void push_back(ui val) {
        if (sz) {
            if (cap > sz) {
                ptr[sz++] = val;
            } else {
                cap *= 3;
                ui *new_ptr = get_mem(cap);
                memcpy(new_ptr, ptr, sizeof(ui) * sz);
                ptr = new_ptr;
                new_ptr = 0;
                ptr[sz++] = val;
            }
        } else {
            ptr = get_mem(1);
            cap = 1;
            ptr[sz++] = val;
        }
    }
    ui back() const {
        return ptr[sz - 1];
    }
    int size() const {
        return sz;
    }
    void reserve(int val) {
        if (cap < val) {
            cap = val;
            ui *new_ptr = get_mem(cap);
            memcpy(new_ptr, ptr, sizeof(ui) * sz);
            ptr = new_ptr;
            new_ptr = 0;
        }
    }
    void resize(int n) {
        reserve(n);
        sz = n;
    }

    void pop_back() {
        sz--;
    }
};
#define MyVector vector<int>

ostream &operator << (ostream &out, const MyVector &v) {
    if (v.size() == 0) {
        out << 0;
        return out;
    }
    for (int i = v.size() - 1; i >= 0; --i) {
        out << v[i];
    }
    return out;
}

struct cmx {
    ld r, i;
    cmx(ld r = 0, ld i = 0) : r(r), i(i) {}
    void operator *= (const cmx &oth) {
        ld cr = r, ci = i;
        r = cr * oth.r - ci * oth.i;
        i = ci * oth.r + cr * oth.i;
    }
};

cmx operator * (const cmx &a, const cmx &b) {
    return {a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r};
}

cmx operator + (const cmx &a, const cmx &b) {
    return {a.r + b.r, a.i + b.i};
}

cmx operator - (const cmx &a, const cmx &b) {
    return {a.r - b.r, a.i - b.i};
}

cmx get_root(int n) {
    return {cos(2L * M_PI / n), sin(2L * M_PI / n)};
}

cmx conjugate(const cmx &a) {
    return {a.r, -a.i};
}

const int LOG = 20;
const int N = 1 << LOG;
void fft(cmx *a, int n, int s, cmx *res, cmx w) {
    if (n == 1) {
        res[0] = a[0];
        return;
    }
    cmx w2 = w * w;
    fft(a,     n >> 1, s << 1, res,            w2);
    fft(a + s, n >> 1, s << 1, res + (n >> 1), w2);
    cmx x = 1;
    for (int i = 0; i < (n >> 1); ++i) {
        cmx b = res[i];
        cmx c = res[i + (n >> 1)];
        cmx tmp = x * c;
        res[i           ] = b + tmp;
        res[i + (n >> 1)] = b - tmp;
        x = x * w;
    }
}

// cmx root[N];
// int rev[N];
// void init() {
//  for (int j = 0; j < N; j++) {
//      rev[j] = rev[j >> 1] + ((j & 1) << (K - 1));
//  }
// }

// f(x) = f(L) * f(base1 ** SZ(R)) + f(R)
cmx ca[N], cb[N], fa[N], fb[N];
cmx ttt[LOG + 1], ttt_[LOG + 1];

ostream &operator << (ostream &out, const pair<int *, int> &p) {
    if (p.second == 0) {
        out << 0;
        return out;
    }
    for (int i = p.second - 1; i >= 0; --i) {
        out << p.first[i];
    }
    return out;
}

void slow_f(int *a, int n, MyVector &res, int b1, int b2) {
    res.reserve(n * 4);
    ll m = 0;
    ll b1_i = 1;
    for (int i = 0; i < n; ++i) {
        m += a[i] * b1_i;
        b1_i *= b1;
    }
    while (m != 0) {
        res.push_back(m % b2);
        m /= b2;
    }
    while (res.size() && res.back() == 0)
        res.pop_back();
    // cout << "slow_f " << "b1=" << b1 << " " << "b2=" << b2  << ' ' << "a=" << make_pair(a, n) << ' '  << "res=" << res << '\n';
}

int _log2(int n) {
    return 31 - __builtin_clz(n);
}

MyVector multiply_slow(const MyVector &a, const MyVector &b, int x) {
    MyVector res;
    res.reserve(a.size() + b.size() + 10);
    res.resize(a.size() + b.size() - 1);
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b.size(); ++j) {
            res[i + j] += a[i] * b[j];
        }
    }
    int z = 0;
    for (int i = 0; i < res.size(); ++i) {
        res[i] += z;
        z = res[i] / x;
        res[i] %= x;
    }
    while (z) {
        res.push_back(z % x);
        z /= x;
    }
    while (res.size() > 0 && res.back() == 0)
        res.pop_back();
    // cout << "multiply slow x=" << x << ' ' << "a=" << a << ' ' << "b=" << b << ' ' << "res=" << res << '\n';
    return res;
}

MyVector multiply(const MyVector &a, const MyVector &b, int x) {
    if (a.size() + b.size() <= 16) {
        return multiply_slow(a, b, x);
    }
    int h = 1 + _log2(a.size() + b.size());
    // cout << "h=" << h << endl;
    // cout << "ttt = " << ttt[h].r << ' ' << ttt[h].i << endl;
    for (int i = 0; i < a.size(); ++i) {
        ca[i] = a[i];
    }
    for (int i = 0; i < b.size(); ++i) {
        cb[i] = b[i];
    }
    fft(ca, (1 << h), 1, fa, ttt[h]);
    fft(cb, (1 << h), 1, fb, ttt[h]);
    for (int i = 0; i < (1 << h); ++i) {
        fa[i] *= fb[i];
    }
    fft(fa, (1 << h), 1, ca, ttt_[h]);
    MyVector res;
    res.reserve(a.size() + b.size() + 10);
    res.resize(a.size() + b.size());
    ll z = 0;
    for (int i = 0; i < a.size() + b.size(); ++i) {
        ll cur = ll(ca[i].r / (1 << h) + 0.5);
        cur += z;
        res[i] = cur % x;
        z = cur / x;
    }
    memset(ca, 0, sizeof(ca[0]) * (1 << h));
    memset(cb, 0, sizeof(ca[0]) * (1 << h));
    memset(fa, 0, sizeof(ca[0]) * (1 << h));
    memset(fb, 0, sizeof(ca[0]) * (1 << h));

    while (z) {
        res.push_back(z % x);
        z /= x;
    }
    while (res.size() && res.back() == 0)
        res.pop_back();
    // cout << "multiply " << "a=" << a << " b=" << b << " x=" << x << " res=" << res << '\n';
    return res;
}

MyVector add(const MyVector &a, const MyVector &b, int x) {
    MyVector res;
    res.reserve(a.size() + b.size() + (a.size() == b.size()));
    ll z = 0;
    for (int i = 0; i < max(a.size(), b.size()) || z; ++i) {
        if (i < a.size())
            z += a[i];
        if (i < b.size())
            z += b[i];
        res.push_back(z % x);
        z /= x;
    }
    while (res.size() && res.back() == 0)
        res.pop_back();
    // cout << "add " << "a=" << a << " b=" << b << " x=" << x << '\n';
    return res;
}

MyVector tr[N];

void f(int *a, int n, MyVector &res, int b1, int b2) {
    if (n <= 18) {
        return slow_f(a, n, res, b1, b2);
    }
    // n = 2^k
    MyVector L, R;
    L.reserve(n);
    R.reserve(n);
    f(a,         n / 2, L, b1, b2);
    f(a + n / 2, n / 2, R, b1, b2);
    MyVector c = multiply(R, tr[n / 2], b2);
    res = add(c, L, b2);
    // cout << "f " << "a=" << make_pair(a, n) << " b1=" << b1 << " b2=" << b2 << '\n';
}

int a[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    for (int i = 0; i <= LOG; ++i) {
        ttt[i] = get_root(1 << i);
        ttt_[i] = conjugate(ttt[i]);
    }

    int bs1, bs2;
    string s;
    cin >> bs1 >> s >> bs2;
    if (s == "0") {
        cout << 0;
        return 0;
    }
    int dg = 1;
    if (s[0] == '-') {
        s = s.substr(1);
        dg *= -1;
    }
    // tr[0] = {1};
    tr[0].push_back(1);
    int kk_lof = bs1;  // ()
    slow_f(&kk_lof, 1, tr[1], 11, bs2);

    for (int i = 2; i <= (1 << _log2(2 * s.size())); ++i) {
        tr[i] = multiply(tr[i - 1], tr[1], bs2);
    }

    for (int i = 0; i < s.size(); ++i) {
        a[i] = s[s.size() - i - 1] - '0';
    }
    MyVector ans;
    f(a, (1 << _log2(2 * s.size())), ans, bs1, bs2);
    if (dg == -1) {
        cout << '-';
    }
    for (int i = ans.size() - 1; i >= 0; --i) {
        cout << ans[i];
    }
    return 0;
}
