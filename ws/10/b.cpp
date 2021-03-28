//#pragma comment(linker, "/STACK:16777216")
#include <bits/stdc++.h>
 
#define all(a) (a).begin(), (a).end()
 
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
    int val;
    int sz;
};
Node buf[N * LOG * 3];
int sz = 0;
 
int size(Node *t) {
    return (t ? t->sz : 0);
}
 
Node *new_node(Node *lt, Node *rt, int val) {
    buf[sz] = {lt, rt, val, -1};
    buf[sz].sz = 1 + size(lt) + size(rt);
    return &buf[sz++];
}
 
Node *set_pos(Node *t, int pos, int val) {
    if (size(t->lt) == pos) {
        return new_node(t->lt, t->rt, val);
    } else if (size(t->lt) > pos) {
        auto *ans = set_pos(t->lt, pos, val);
        return new_node(ans, t->rt, t->val);
    } else {
        auto *ans = set_pos(t->rt, pos - 1 - size(t->lt), val);
        return new_node(t->lt, ans, t->val);
    }
}
 
int get(Node *t, int pos) {
    if (size(t->lt) == pos) {
        return t->val;
    } else if (size(t->lt) > pos) {
        return get(t->lt, pos);
    } else {
        return get(t->rt, pos - size(t->lt) - 1);
    }
}
 
Node *make_tree(int n) {
    if (n == 0) {
        return nullptr;
    }
    auto *lt = make_tree((n - 1) / 2);
    int x;
    cin >> x;
    auto *rt = make_tree(n - 1 - (n - 1) / 2);
    return new_node(lt, rt, x);
}
 
Node *vers[N + 10];
 
void solve() {
    int n;
    cin >> n;
    vers[0] = make_tree(n);
    int q;
    cin >> q;
    int k = 1;
    for (int i = 0; i < q; ++i) {
        string s;
        cin >> s;
        if (s == "create") {
            int pr, pos, x;
            cin >> pr >> pos >> x;
            --pr; --pos;
            vers[k++] = set_pos(vers[pr], pos, x);
        } else {
            int pr, pos;
            cin >> pr >> pos; --pr; --pos;
            cout << get(vers[pr], pos) << '\n';
        }
    }
}
 
signed main() {
#ifdef LOCAL_DEFINE
    freopen("input.txt", "r", stdin);
#else
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    cout.tie(nullptr);
    set_file("parray");
#endif
    solve();
    return 0;
}
