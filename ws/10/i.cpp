//#pragma comment(linker, "/STACK:16777216")
//#define _GLIB_CXX_DEBUG
#include <bits/stdc++.h>

#define all(a) (a).begin(), (a).end()
#define mid(l, r) (((r) + (l)) >> 1)

using namespace std;
typedef long long ll;
//#define int ll


void set_file(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

struct Node {
    Node *lt = nullptr, *rt = nullptr;
    int x = 0;
    Node(Node *lt = nullptr, Node *rt = nullptr, int x = 0) :
        lt(lt), rt(rt), x(x) {}
};
Node buf[(int)0.75e7];
int sz = 0;

Node *new_node(Node *lt, Node *rt, int x = -1) {
    buf[sz] = Node{lt, rt, x};
    return &buf[sz++];
}

Node *make_tree(int n, int x = -1) {
    if (n == 1) {
        return new_node(nullptr, nullptr, x);
    }
    auto *lt = make_tree(n / 2, x);
    auto *rt = make_tree(n - n / 2, x);
    return new_node(lt, rt, -1);
}

Node *get(Node *node, int i, int n) {
    while (n > 1) {
        if (i < (n >> 1)) {
            node = node->lt;
            n >>= 1;
        } else {
            i -= (n >> 1);
            node = node->rt;
            n = n - (n >> 1);
        }
    }
    return node;
}

Node *upd(Node *node, int i, int n, int val) {
    if (n == 1) {
        return new_node(nullptr, nullptr, val);
    }
    if (i < (n >> 1)) {
        return new_node(upd(node->lt, i, n >> 1, val), node->rt);
    } else {
        return new_node(node->lt, upd(node->rt, i - (n >> 1), n - (n >> 1), val));
    }
}

const int N = 1e5 + 10;
Node *pars[N + 10];
Node *rks[N + 10];

int head(Node *rk, Node *par, int a, int n) {
    int nxt;
    while ((nxt = get(par, a, n)->x) != -1) {
        a = nxt;
    }
    return a;
}

pair<Node *, Node *> unite(Node *rk, Node *par, int a, int b, int n) {
    a = head(rk, par, a, n);
    b = head(rk, par, b, n);
    if (a == b) {
        return make_pair(rk, par);
    }
    Node *rk_a = get(rk, a, n);
    Node *rk_b = get(rk, b, n);
    if (rk_a->x > rk_b->x) {
        swap(rk_a, rk_b);
        swap(a, b);
    }
    // a -> b
    par = upd(par, a, n, b);
    if (rk_a->x == rk_b->x) {
        rk = upd(rk, b, n, get(rk, b, n)->x + 1);
    }
    return make_pair(rk, par);
}

void solve() {
    int n, k;
    cin >> n >> k;
    pars[0] = make_tree(n, -1);
    rks[0] = make_tree(n, 1);
    for (int _ = 1; _ <= k; ++_) {
        char tp;
        cin >> tp;
        int i, a, b;
        cin >> i >> a >> b;
        a--;
        b--;
        if (tp == '?') {
            cout << (head(rks[i], pars[i], a, n) == head(rks[i], pars[i], b, n) ? "YES" : "NO") << '\n';
        } else {
            auto res = unite(rks[i], pars[i], a, b, n);
            rks[_] = res.first;
            pars[_] = res.second;
        }
    }
}

signed main() {
    // freopen("in", "r", stdin);
    solve();
    return 0;
}
