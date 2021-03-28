#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 1 << 20;
const int A = 256 + 10;
int n, tot, c[N], suf[N], new_c[N], new_suf[N], beg[N], where[N], s[N], pos, x, real_n;
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

int main() {
    string ss;
    cin >> ss;
    n = ss.size() + 1;
    for (int i = 0; i < n; ++i) {
        s[i] = ss[i];  
    }
    build();
    for (int i = 1; i < n; ++i) {
        cout << suf[i] + 1 << ' ';
    }
    return 0;
}
