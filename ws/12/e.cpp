#include <vector>
#include <cmath>
#include <iostream>
#include <climits>
#include <cstring>
#include <algorithm>
#include <array>
#include <complex>
#include <cassert>
#include <set>
#include <unordered_set>
#include <queue>
#include <vector>
#include <map>

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
typedef array<int, 2> a2;
typedef long double ld;
typedef array<int, 3> a3;
typedef array<int, 4> a4;
typedef array<ll, 2> l2;
typedef array<l2, 2> mtrx;

const ll mod = 1e9 + 7;

const int LOG = 19;
const int N = 1 << LOG;
int p[N];
int rk[N];
pair<int *, int> pers[N * LOG];
int pers_sz; // !!!
vector<a2> t[N * 2];
int iq_sz;
int n, k;

void add(int l, int r, a2 e) {
    // cout << l << ' ' << r << '\n';
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
            // cout << l << ' ';
            t[l++].push_back(e);
        }
        if (r & 1) {
            // cout << r - 1 << ' ';
            t[--r].push_back(e);
        }
    }
    // cout << endl;
}

int get_par(int a) {
    while (p[a] >= 0) {
        a = p[a];
    }
    return a;
}

bool unite(int a, int b) {
    a = get_par(a), b = get_par(b);
    if (a == b)
        return 0;
    if (rk[a] > rk[b])
        swap(a, b);
    pers[pers_sz++] = {&p[a], p[a]};
    p[a] = b;
    if (rk[a] == rk[b]) {
        pers[pers_sz++] = {&rk[b], rk[b]};
        rk[b]++;
    }
    return 1;
}

int ans[N];
pair<int, int> query[N];
void f(int v, int l, int r, int comp) {
    int st_sz = pers_sz;
    int comp1 = comp;
    for (auto uv : t[v]) {
        comp1 -= unite(uv[0], uv[1]);
    }
    if (l + 1 == r) {
        ans[l] = (get_par(query[l].first) == get_par(query[l].second));
    } else {
        int mid = (l + r) / 2;
        f(v * 2, l, mid, comp1);
        f(v * 2 + 1, mid, r, comp1);
    }
    while (st_sz < pers_sz) {
        *(pers[pers_sz - 1].first) = pers[pers_sz - 1].second;
        pers_sz--;
    }
}

signed main() {
    // freopen("in", "r", stdin);
    cin >> n >> k;
    memset(p, -1, sizeof(p));
    map<a2, int> mp;
    for (int i = 0; i < k; ++i) {
        string tp;
        cin >> tp;
        if (tp == "get") {
            cin >> query[iq_sz].first >> query[iq_sz].second;
            --query[iq_sz].first;
            --query[iq_sz].second;
            iq_sz++;
        } else {
            a2 uv;
            cin >> uv[0] >> uv[1];
            --uv[0];
            --uv[1];
            if (uv[0] > uv[1])
                swap(uv[0], uv[1]);
            if (tp == "link") {
                mp[uv] = iq_sz;
            } else {
                add(mp[uv], iq_sz, uv);
                mp[uv] = -1;
            }
        }
    }
    for (auto [uv, l] : mp) {
        if (l != -1) {
            add(l, iq_sz, uv);
        }
    }

    f(1, 0, N, n);

    for (int i = 0; i < iq_sz; ++i) {
        cout << ans[i];
    }
    return 0;
}
