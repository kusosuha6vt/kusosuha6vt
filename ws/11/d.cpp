#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 1 << 20;
const int A = 256 + 10;
int n, tot, c[N], suf[N], new_c[N], new_suf[N], beg[N], s[N], pos;
ll res;

int safe(int x) {
    return x >= n ? x - n : x;
}

void build() {
    memset(beg, 0, sizeof(beg));
    for (int i = 0; i < n; ++i) {
        c[i] = s[i];
        beg[c[i] + 1]++;
        suf[i] = i;
    }
    for (int i = 0; i < A - 1; ++i) {
        beg[i + 1] += beg[i];
    }
    for (int l = 0; l < n; l = (l ? l * 2 : 1)) {
        for (int i = 0; i < n; ++i) {
            pos = safe(suf[i] - l + n);
            new_suf[beg[c[pos]]++] = pos;
        }
        tot = 0;
        for (int i = 0; i < n; ++i) {
            if ((i == 0) || (c[new_suf[i - 1]] != c[new_suf[i]]) ||
                c[safe(new_suf[i - 1] + l)] != c[safe(new_suf[i] + l)]) {
                beg[tot++] = i;
            }
            new_c[new_suf[i]] = tot - 1;
        }
        memcpy(suf, new_suf, n * sizeof(suf[0]));
        memcpy(c, new_c, n * sizeof(c[0]));
    }
}

int lcp[N], rsuf[N];
void build_lcp() {
    for (int i = 0; i < n; ++i) {
        rsuf[suf[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n; ++i) {
        k = max(0, k - 1);
        if (rsuf[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = suf[rsuf[i] + 1];
        while (s[i + k] == s[j + k]) {
            k++;
        }
        lcp[rsuf[i]] = k;
    }
}

int t[2 * N];
int mn[2 * N];

void build_lcp_tree(int v, int l, int r) {
    if (r - l == 1) {
        mn[v] = lcp[l];
        return;
    }
    int m = (l + r) >> 1;
    build_lcp_tree(v * 2, l, m);
    build_lcp_tree(v * 2 + 1, m, r);
}

int get_lcp(int v, int l, int r, int ql, int qr) {
    if (r <= ql || qr <= l) {
        return INT_MAX;
    }
    if (ql <= l && r <= qr) {
        return mn[v];
    }
    int m = (l + r) >> 1;
    return min(get_lcp(v * 2, l, m, ql, qr), get_lcp(v * 2 + 1, m, r, ql, qr));
}

void add(int i, int val) {
    t[i += N] += val;
    for (; i > 1; i >>= 1) {
        t[i >> 1] += val;
    }
}

int find_kth(int v, int l, int r, int i) {
    if (r - l == 1) {
        return l;
    }
    int m = (l + r) >> 1;
    if (i < t[v * 2]) {
        return find_kth(v * 2, l, m, i);
    } else {
        return find_kth(v * 2 + 1, m, r, i - t[v * 2]);
    }
}

int get_id(int v, int l, int r, int i) {
    if (i <= l) {
        return 0;
    }
    if (r <= i) {
        return t[v];
    }
    int m = (l + r) >> 1;
    return get_id(v * 2, l, m, i) + get_id(v * 2 + 1, m, r, i);
}

void f(int *cntr) {
    build();
    build_lcp();
    build_lcp_tree(1, 0, N - 1);
    memset(t, 0, sizeof(t));
    add(rsuf[n - 1], 1);
    for (int i = n - 2; i >= 0; --i) {
        int pos = rsuf[i];
        int pos_set = get_id(1, 0, N, pos);
        add(pos, 1);
        int ans = 0;
        if (pos_set > 0) {
            int posL = find_kth(1, 0, N, pos_set - 1);
            int lcp = get_lcp(1, 0, N - 1, posL, pos);
            ans = max(ans, posL);
        }
        if (pos_set + 1 < t[1]) {
            int posR = find_kth(1, 0, N, pos_set + 1);
            int lcp = get_lcp(1, 0, N - 1, pos, posR);
            ans = max(ans, posR);
        }
        cntr[i] = ans;
    }
}

int fl[N], fr[N];

int main() {
    freopen("in", "r", stdin);
    string ss;
    cin >> ss;
    n = ss.size() + 1;
    for (int i = 0; i < n; ++i) {
        s[i] = ss[i];
    }
    f(fr);

    cout << "fr=";
    for (int i = 0; i < n - 1; i++) {
        cout << fr[i] << ' ';
    }
    cout << endl;

    reverse(s, s + n - 1);
    f(fl);
    reverse(s, s + n - 1);
    reverse(fl, fl + n - 1);
    cout << "fl=";
    for (int i = 0; i < n - 1; ++i) {
        cout << fl[i] << ' ';
    }
    cout << endl;
    ll ans = 0;
    for (int i = 0; i + 1 < n - 1; i++) {
        ans += fl[i] * fr[i + 1];
    }
    cout << ans;
    return 0;
}
