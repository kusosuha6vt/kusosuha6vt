#include<bits/stdc++.h>
#define db(a) cout << #a << "=" << a << endl;
// #include <complex>

using namespace std;
typedef long double ld;
typedef long long ll;
// typedef complex<ld> cmx;

struct cmx {
    ld r, i;
    cmx(ld r = 0, ld i = 0) : r(r), i(i) {}
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

int t[N];
int to_int(char c) {
    return (c >= 'A' && c <= 'F' ? c - 'A' + 10 : c - '0');
}

cmx t_is_one[N], p_is_one[N];
cmx r2[N], r4[N];

//  10110010 11010110
// 1
// 0
// 1
// 1
// ?
// 0
// 1
// 0 = 7

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string st;
    string sp;
    cin >> st >> sp;
    int c_q = count(sp.begin(), sp.end(), '?');
    int n = st.size() * 4;
    int m = sp.size();
    for (int i = 0; i < st.size(); ++i) {
        for (int j = 0; j < 4; ++j) {
            t[i * 4 + j] = ((to_int(st[i]) >> (3 - j)) & 1);
        }
    }
    vector<int> ans((n - m + 8) / 8, c_q);
    for (int i = 0; i < n; ++i) {
        t_is_one[i] = int(t[i] == 1);
    }
    for (int i = 0; i < m; ++i) {
        p_is_one[i] = int(sp[m - i - 1] == '1');
    }
    cmx w = get_root(N);
    cmx wr = conjugate(w);
    fft(t_is_one, N, 1, r2, w);
    fft(p_is_one, N, 1, r4, w);
    for (int i = 0; i < N; ++i) {
        r2[i] = r2[i] * r4[i];
    }
    fft(r2, N, 1, r4, wr);
    for (int i = m - 1; i < n; i += 8) {
        int c2 = int(r4[i].r / N + 0.5);
        ans[(i - (m - 1)) / 8] += c2;
    }
    for (int i = 0; i < n; ++i) {
        t_is_one[i] = int(t[i] == 0);
    }
    for (int i = 0; i < m; ++i) {
        p_is_one[i] = int(sp[m - i - 1] == '0');
    }
    fft(t_is_one, N, 1, r2, w);
    fft(p_is_one, N, 1, r4, w);
    for (int i = 0; i < N; ++i) {
        r2[i] = r2[i] * r4[i];
    }
    fft(r2, N, 1, r4, wr);
    for (int i = m - 1; i < n; i += 8) {
        int c2 = int(r4[i].r / N + 0.5);
        ans[(i - (m - 1)) / 8] += c2;
    }
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << ' ';
    }
    return 0;
}
