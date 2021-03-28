//#pragma comment(linker, "/STACK:16777216")
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
 
const int N = 1e6;
const int LOG = 20;
struct Node {
    Node *lt, *rt;
    int val;
    ll sum;
    int sz;
};
const int MEM_SZ = N * LOG / 1.75;
Node buf[MEM_SZ];
int sz = 0;
 
int size(Node *t) {
    return (t ? t->sz : 0);
}
 
ll sum(Node *t) {
    return (t ? t->sum : 0);
}
 
Node *new_node(Node *lt, Node *rt, int val) {
    // while (sz >= MEM_SZ)
    //     {}
    assert(sz < MEM_SZ);
    buf[sz] = {lt, rt, val, val + sum(lt) + sum(rt), 1 + size(lt) + size(rt)};
    return &buf[sz++];
}
 
Node *new_node(Node *t) {
    // while (sz >= MEM_SZ)
    //     {}
    assert(sz < MEM_SZ);
    buf[sz] = {t->lt, t->rt, t->val, t->sum, t->sz};
    return &buf[sz++];
}
 
ll _a, _b, _m, _x1;
 
Node *make_tree(int n) {
    if (n == 0) {
        return nullptr;
    }
    auto *lt = make_tree((n - 1) / 2);
    int x;
    x = _x1;
    _x1 = (_a * _x1 + _b) % _m;
    auto *rt = make_tree(n - 1 - (n - 1) / 2);
    return new_node(lt, rt, x);
}
 
void upd(Node *t) {
    assert(t);
    t->sum = sum(t->lt) + sum(t->rt) + t->val;
    t->sz = size(t->lt) + size(t->rt) + 1;
}
 
mt19937 gen;
typedef unsigned long long ull;
typedef uniform_int_distribution<ull> uidull;
typedef unsigned int ui;
bool if_random(int a, int b) {
    return uniform_int_distribution<int>(1, a + b)(gen) >= a;
}
 
typedef pair<Node *, Node *> pnn;
pnn split_kth(Node *t, int k) {
    if (!t) {
        return {nullptr, nullptr};
    }
    if (size(t->lt) >= k) {
        auto res = split_kth(t->lt, k);
        // upd(res);
        return {res.first, new_node(res.second, t->rt, t->val)};
    } else {
        auto res = split_kth(t->rt, k - size(t->lt) - 1);
        // upd(res);
        return {new_node(t->lt, res.first, t->val), res.second};
    }
}
 
Node *merge(Node *l, Node *r) {
    if (!l) return r;
    if (!r) return l;
    if (if_random(size(l), size(r))) {
        return new_node(l->lt, merge(l->rt, r), l->val);
    } else {
        return new_node(merge(l, r->lt), r->rt, r->val);
    }
}
 
Node *tree = nullptr;
 
void print(Node *t) {
    if (!t) return;
    print(t->lt);
    cout << t->val << ' ';
    print(t->rt);
}
 
void copy(int l1, int l2, int len) {
    auto resAB_C = split_kth(tree, l1 + len);
    auto resA_B = split_kth(resAB_C.first, l1);
    auto *B = resA_B.second;
    resAB_C = split_kth(tree, l2 + len);
    resA_B = split_kth(resAB_C.first, l2);
    tree = merge(merge(resA_B.first, B), resAB_C.second);
}

ll clever_sum(Node *node, int l, int r) {
    if (!node || r <= 0 || l >= size(node)) {
        return 0;
    }
    if (l <= 0 && size(node) <= r) {
        return sum(node);
    }
    int L = (size(node) - 1) >> 1;
    return clever_sum(node->lt, l, r) + clever_sum(node->rt, l - L - 1, r - L - 1);
}

ll sum(int l, int r) {
    // auto resAB_C = split_kth(tree, r);
    // auto resA_B = split_kth(resAB_C.first, l);
    // return sum(resA_B.second);
    return clever_sum(tree, l, r);
}

void clever_out(Node *node, int l, int r) {
    if (!node || r <= 0 || l >= size(node)) {
        return;
    }
    int L = (size(node) - 1) >> 1;
    clever_out(node->lt, l, r);
    if (l <= L && L < r) {
        cout << node->val << ' ';
    }
    clever_out(node->rt, l - L - 1, r - L - 1);
}

void out(int l, int r) {
    // auto resAB_C = split_kth(tree, r);
    // auto resA_B = split_kth(resAB_C.first, l);
    // print(resA_B.second);
    clever_out(tree, l, r);
    cout << endl;
}
 
int new_value[int(1e6)];
int it;
void visit(Node *node) {
    if (!node)
        return;
    visit(node->lt);
    new_value[it++] = node->val;
    visit(node->rt);
}

Node *build(int *el, int n) {
    if (n == 0) {
        return nullptr;
    }
    Node *lt = build(el, (n - 1) >> 1);
    int mid = el[((n - 1) >> 1)];
    Node *rt = build(el + ((n - 1) >> 1) + 1, (n - 1) - ((n - 1) >> 1));
    return new_node(lt, rt, mid);
}

void rebuild() {
    if (MEM_SZ - sz > 125 * LOG) return;
    it = 0;
    visit(tree);
    sz = 0;
    tree = build(new_value, it);
}
 
void solve() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    cin >> _x1 >> _a >> _b >> _m;
    tree = make_tree(n);
 
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        string s;
        cin >> s;
        if (s == "out") {
            int sz0 = sz;
            int l, r;
            cin >> l >> r;
            --l;
            out(l, r);
            sz = sz0;
        } else if (s == "sum") {
            int sz0 = sz;
            int l, r;
            cin >> l >> r;
            --l;
            cout << sum(l, r) << endl;
            sz = sz0;
        } else {
            int l1, l2, len;
            cin >> l1 >> l2 >> len;
            --l1; --l2;
            copy(l1, l2, len);
        }

        rebuild();
    }
}
 
signed main() {
    freopen("in", "r", stdin);
    solve();
    return 0;
}
