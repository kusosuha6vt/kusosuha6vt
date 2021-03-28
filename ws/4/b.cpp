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
 
const int N = 1e5 + 1;
const int A = 'z' - 'a' + 1;
int nxt1[N][A];
int link1[N];
int n;
 
int q1[N];
void push_links1() {
    int l = 0, r = 1;
    while (r - l) {
        int v = q1[l++];
        int lk = link1[v];
        for (int c = 0; c < A; ++c) {
            if (nxt1[v][c]) {
                link1[nxt1[v][c]] = v ? nxt1[lk][c] : 0;
                q1[r++] = nxt1[v][c];
            } else {
                nxt1[v][c] = nxt1[lk][c];
            }
        }
    }
}
 
int q2[N];
int nxt2[N][A];
int link2[N];
int term2[N];
int sz = 1;
int add2(const string &s) {
    int v = 0;
    for (char c : s) {
        c -= 'a';
        if (!nxt2[v][c]) {
            nxt2[v][c] = sz++;
        }
        v = nxt2[v][c];
    }
    term2[v]++;
    return v;
}
 
void push_links2() {
    int l = 0, r = 1;
    while (r - l) {
        int v = q2[l++];
        int lk = link2[v];
        for (int c = 0; c < A; ++c) {
            if (nxt2[v][c]) {
                link2[nxt2[v][c]] = v ? nxt2[lk][c] : 0;
                q2[r++] = nxt2[v][c];
            } else {
                nxt2[v][c] = nxt2[lk][c];
            }
        }
    }
}
 
ll ans;
bool used[N];
 
void dfs(int v, int u) { /// 1-st
    if (used[v]) return;
    used[v] = 1;
    for (int c = 0; c < A; ++c) {
        dfs(nxt1[v][c], nxt2[u][c]);
    }
    ans += term2[u];
}
 
void solve() {
    cin >> n;
    for (int v = 0; v < n; ++v) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int u;
            char c;
            cin >> u >> c; --u;
            nxt1[v][c - 'a'] = u;
        }
    }
 
//    push_links1();
 
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        add2(s);
    }
    push_links2();
 
    for (int i = 0; i < sz; ++i) {
        int v = q2[i];
        int lk = link2[v];
        term2[v] += term2[lk];
    }
 
    dfs(0, 0);
    cout << ans;
}
 
signed main() {
#ifdef LOCAL_DEFINE
    freopen("input.txt", "r", stdin);
#else
//    set_file("game");
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
//    set_file("memory");
#endif
    solve();
    return 0;
}
