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
 
const int N = 4.5e5;
const int LOG = 19;
struct Node {
    Node *lt = nullptr, *rt = nullptr;
    int sum = 0;
    int sz = 0;
    Node(Node *e1 = nullptr, Node *e2 = nullptr, int e3 = 0, int e4 = 0) :
        lt(e1), rt(e2), sum(e3), sz(e4) {}
};
Node buf[N * LOG * 2];
int sz = 0;
 
int size(Node *t) {
    return (t ? t->sz : 0);
}
 
int sum(Node *t) {
    return (t ? t->sum : 0);
}
 
Node *new_node(Node *lt, Node *rt, int sum) {
    buf[sz] = Node{lt, rt, sum, -1};
    buf[sz].sz = 1;
    return &buf[sz++];
}
 
Node *new_node(Node *lt, Node *rt) {
    buf[sz] = {lt, rt, -1, -1};
    buf[sz].sz = size(lt) + size(rt);
    buf[sz].sum = lt->sum + rt->sum;
    return &buf[sz++];
}
 
Node *add_pos(Node *t, int pos, int val) {
    if (size(t) == 1) {
        return new_node(nullptr, nullptr, t->sum + val);
    } else if (size(t->lt) > pos) {
        auto *ans = add_pos(t->lt, pos, val);
        return new_node(ans, t->rt);
    } else {
        auto *ans = add_pos(t->rt, pos - size(t->lt), val);
        return new_node(t->lt, ans);
    }
}
 
Node *make_tree(int n) {
    if (n == 1) {
        int x;
        x = 0;
        return new_node(nullptr, nullptr, x);
    }
    auto *lt = make_tree(n / 2);
    auto *rt = make_tree(n - n / 2);
    return new_node(lt, rt);
}
 
Node *nodes[N + 10];
int a[N];
int coord[N];
 
int get_r(Node *t, int l, int r, int k) {
    if (k > sum(t)) {
        return -1;
    }
    if (l + 1 == r) {
        return l;
    }
    if (sum(t->lt) >= k) {
        return get_r(t->lt, l, mid(l, r), k);
    } else {
        return get_r(t->rt, mid(l, r), r, k - sum(t->lt));
    }
}
 
int get_kth_plus_one(Node *tr, Node *tl, int l, int r, int k) {
    if (k > sum(tr) - sum(tl)) {
        return -1;
    }
    if (l + 1 == r) {
        return l;
    }
    if (sum(tr->lt) - sum(tl->lt) >= k) {
        return get_kth_plus_one(tr->lt, tl->lt, l, mid(l, r), k);
    } else {
        return get_kth_plus_one(tr->rt, tl->rt, mid(l, r), r, k - (sum(tr->lt) - sum(tl->lt)));
    }
}

void print(Node *t) {
    if (size(t) == 1) {
        cout << t->sum << ' ';
        return;
    }
    print(t->lt);
    print(t->rt);
}
 
void solve() {
    int n;
    cin >> n;
    int l, m;
    cin >> a[0] >> l >> m;
    for (int i = 1; i < n; ++i) {
        a[i] = (ll(a[i - 1]) * l + m) % int(1e9);
    }
    for (int i = 0; i < n; ++i) {
        coord[i] = a[i];
    }
    sort(coord, coord + n);
    int sz_coord = unique(coord, coord + n) - coord;
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(coord, coord + sz_coord, a[i]) - coord;
    }
 
    nodes[0] = make_tree(sz_coord);
    for (int i = 0; i < n; ++i) {
        nodes[i + 1] = add_pos(nodes[i], a[i], 1);
    }
 
    int B;
    cin >> B;
    ll sum = 0;
    for (int i = 0; i < B; ++i) {
        int G;
        cin >> G;
        ll x1, lx, mx, y1, ly, my, k1, lk, mk, ig, jg;
        cin >> x1 >> lx >> mx >> y1 >> ly >> my >> k1 >> lk >> mk;
        ig = min(x1, y1);
        jg = max(x1, y1);
        for (int i_ = 0; i_ < G; ++i_) {
            ig--;
            int ans = get_kth_plus_one(nodes[jg], nodes[ig], 0, sz_coord, k1);
            sum += coord[ans];
//            cout << ans << '\n';
            ig++;
            x1 = ((ig - 1) * lx + mx) % n + 1;
            y1 = ((jg - 1) * ly + my) % n + 1;
            ig = min(x1, y1);
            jg = max(x1, y1);
            k1 = (((k1 - 1) * lk + mk) % (jg - ig + 1)) + 1;
        }
    }
    cout << sum << '\n';
}
 
signed main() {
#ifdef LOCAL_DEFINE
    freopen("input.txt", "r", stdin);
#else
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cout.tie(nullptr);
//    set_file("parray");
#endif
    solve();
    return 0;
}
