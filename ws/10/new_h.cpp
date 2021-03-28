#include <bits/stdc++.h>

using namespace std;

struct Node {
    int l, r, mn;
};

const int MEM = 0.75e7;
Node t[MEM];
int sz = 1;

int min(int v) {
    return (v ? t[v].mn : INT_MAX);
}

void upd(int v) {
    t[v].mn = min(min(t[v].l), min(t[v].r));
}

int set_pos(int v, int n, int i, int val) {
    if (n == 1) {
        assert(i == 0);
        t[sz] = {0, 0, val};
        return sz++;
    }
    if (i < (n >> 1)) {
        int res = set_pos(t[v].l, n >> 1, i, val);
        t[sz] = {res, t[v].r, min(min(res), min(t[v].r))};
        return sz++;
    } else {
        int res = set_pos(t[v].r, n - (n >> 1), i - (n >> 1), val);
        t[sz] = {t[v].l, res, min(min(res), min(t[v].l))};
        return sz++;
    }
}

int query(int v, int n, int val) {
    if (min(v) > val) {
        return -1;
    }
    if (n == 1) {
        return 0;
    }
    if (min(t[v].l) <= val) {
        return query(t[v].l, n >> 1, val);
    } else {
        int res = query(t[v].r, n - (n >> 1), val);
        return (res == -1 ? -1 : res + (n >> 1));
    }
}

int create(int n) {
    if (n == 1) {
        t[sz] = {0, 0, 0};
        return sz++;
    }
    int res1 = create(n >> 1);
    int res2 = create(n - (n >> 1));
    t[sz] = {res1, res2, 0};
    return sz++;
}

const int N = 1e6;
int nodes[N];
typedef array<int, 3> a3;
int active[N];
a3 scan[N];

int main() {
    int n, s, m;
    cin >> n >> s >> m;
    nodes[0] = create(s);
    for (int i = 0; i < m; ++i) {
        int c, a, b;
        cin >> c >> a >> b;
        c--;
        scan[i * 2] = a3{a + 1, -1, c};
        scan[i * 2 + 1] = a3{b, 1, c};
    }
    sort(scan, scan + 2 * m);
    int j = 0;
    for (int i = 1; i <= n; ++i) {
        nodes[i] = nodes[i - 1];
        while (j < 2 * m && scan[j][0] == i) {
            int tp = -scan[j][1];
            int c = scan[j][2];
            j++;
            active[c] += tp;
            if (active[c] == 0 && tp == -1) {
                nodes[i] = set_pos(nodes[i], s, c, i);
            } else if (active[c] == 1 && tp == 1) {
                nodes[i] = set_pos(nodes[i], s, c, INT_MAX);
            }
        }
    }
    int p = 0, q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        x += p;
        y += p;
        assert(x <= y);
        p = query(nodes[y], s, x) + 1;
        cout << p << '\n';
    }
    return 0;
}
