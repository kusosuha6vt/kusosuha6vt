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
 
const int N = 1e5;
const int LOG = 17;
struct Node {
    Node *lt, *rt;
    int sum;
    int sz;
};
Node buf[N * LOG * 6];
int sz = 0;
 
int size(Node *t) {
    return (t ? t->sz : 0);
}
 
int sum(Node *t) {
    return (t ? t->sum : 0);
}
 
Node *new_node(Node *lt, Node *rt, int sum) {
    buf[sz] = {lt, rt, sum, -1};
    buf[sz].sz = 1;
    return &buf[sz++];
}
 
Node *new_node(Node *lt, Node *rt) {
    buf[sz] = {lt, rt, -1, -1};
    buf[sz].sz = size(lt) + size(rt);
    buf[sz].sum = lt->sum + rt->sum;
    return &buf[sz++];
}
 
Node *set_pos(Node *t, int pos, Node *val) {
    if (size(t) == 1) {
        return val;
    } else if (size(t->lt) > pos) {
        auto *ans = set_pos(t->lt, pos, val);
        return new_node(ans, t->rt);
    } else {
        auto *ans = set_pos(t->rt, pos - size(t->lt), val);
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
 
Node *vers[N + 10];
int last[N];
int a[N];
 
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
 
void print(Node *t) {
    if (size(t) == 1) {
        cout << t->sum << ' ';
        return;
    }
    print(t->lt);
    print(t->rt);
}
 
void solve() {
    new_node(nullptr, nullptr, 0);
    new_node(nullptr, nullptr, 1);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> a[i], a[i]--;
    fill(last, last + m, -1);
 
    vers[n] = make_tree(n);
    for (int i = n - 1; i >= 0; --i) {
        Node *t = vers[i + 1];
        if (last[a[i]] >= 0) {
            t = set_pos(t, last[a[i]], &buf[0]);
        }
        last[a[i]] = i;
        t = set_pos(t, last[a[i]], &buf[1]);
        vers[i] = t;
    }
//    for (int i = 0; i <= n; ++i) {
//        cout << "vers[" << i << "] = ";
//        print(vers[i]);
//        cout << '\n';
//    }
    int q;
    cin >> q;
    int p = 0;
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        int l = (x + p) % n;
        int k = (y + p) % m + 1;
        p = 1 + get_r(vers[l], 0, n, k);
        cout << p << '\n';
    }
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
