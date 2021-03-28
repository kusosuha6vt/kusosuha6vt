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
 
mt19937 gen;
typedef uniform_int_distribution<int> uid;
int rnd(int l, int r) {
    return uid(l, r - 1)(gen);
}
 
const int N = 30000 + 1;
 
struct S;
typedef S * V;
struct S {
    V to[2] = {nullptr};
    V link = nullptr;
    int len = -1;
    bool term = 0;
    int used = 0;
};
S t[N]; int sz = 1;
 
void init() {
    t->len = 0;
    t->link = t;
}
 
V add(const string &s) {
    V v = t;
    for (char c : s) {
        c -= '0';
        if (!v->to[c]) {
            v->to[c] = t + sz++;
            v->to[c]->len = v->len + 1;
        }
        v = v->to[c];
    }
    v->term = 1;
    return v;
}
 
V que[N];
void push_links() {
    int l = 0, r = 1;
    que[0] = t;
    while (l < r) {
        V v = que[l++];
        V suff = v->link;
        v->term = v->term || suff->term;
        for (int i = 0; i < 2; ++i) {
            if (v->to[i]) {
                v->to[i]->link = v == t ? v : suff->to[i];
                que[r++] = v->to[i];
            } else {
                v->to[i] = suff->to[i];
            }
        }
    }
}
 
bool dfs(V v) {
    if (v->term || v->used == 2) {
        return false;
    }
    if (v->used == 1) {
        return true;
    }
    v->used = 1;
    for (int i = 0; i < 2; ++i) {
        if (dfs(v->to[i])) {
            return true;
        }
    }
    v->used = 2;
    return false;
}
 
void solve() {
    init();
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        add(s);
    }
    push_links();
    cout << (dfs(t) ? "TAK\n" : "NIE\n");
}
 
signed main() {
#ifdef LOCAL_DEFINE
    freopen("input.txt", "r", stdin);
#else
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
//    set_file("memory");
#endif
    solve();
//stress();
    return 0;
}
