//#pragma comment(linker, "/STACK:16777216")
// #define _GLIB_CXX_DEBUG
#include <bits/stdc++.h>

#define all(a) (a).begin(), (a).end()
#define mid(l, r) (((r) + (l)) >> 1)

using namespace std;
typedef long long ll;
#define int ll


void set_file(string s) {
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
}

struct Node {
    Node *lt = nullptr, *rt = nullptr;
    int t = 0;
    Node(Node *lt = nullptr, Node *rt = nullptr, int t = 0) :
        lt(lt), rt(rt), t(t) {}
};

int mn(Node *node) {
    return (node ? node->t : INT_MAX);
}

void upd(Node *node) {
    if (node && node->lt) {
        node->t = min(mn(node->lt), mn(node->rt));
    }
}

const int MEM = (int)0.75e7;
Node buf[MEM];
int sz = 0;

Node *new_node(Node *lt, Node *rt, int t) {
    while (sz >= MEM)
        {}
    buf[sz] = Node{lt, rt, t};
    return &buf[sz++];
}

Node *make_tree(int n, int t) {
    if (n == 1) {
        return new_node(nullptr, nullptr, t);
    }
    auto *lt = make_tree(n >> 1, t);
    auto *rt = make_tree(n - (n >> 1), t);
    Node *res = new_node(lt, rt, t);
    upd(res);
    return res;
}

Node *upd(Node *node, int n, int i, int t) {
    if (n == 1) {
        // while (i != 0)
        //     {}
        Node *res = new_node(nullptr, nullptr, t);
        return res;
    }
    // while (!node)
    //     {}
    if (i < (n >> 1)) {
        Node *res = new_node(upd(node->lt, n >> 1, i, t), node->rt, 0);
        upd(res);
        return res;
    } else {
        Node *res = new_node(node->lt, upd(node->rt,
            n - (n >> 1), i - (n >> 1), t), 0);
        upd(res);
        return res;
    }
}

int query(Node *node, int n, int a) {
    while (!node)
        {}
    if (mn(node) > a) {
        return INT_MIN;
    }
    if (n == 1) {
        return 0;
    }
    int L = (n >> 1);
    if (mn(node->lt) <= a) {
        return query(node->lt, L, a);
    } else {
        return L + query(node->rt, n - L, a);
    }
}

void print(Node *node) {
    if (!node->lt) {
        cerr << node->t << ' ';
    } else {
        print(node->lt);
        print(node->rt);
    }
}

typedef tuple<int, int, int> a3;
const int N = 1e6 + 10;
Node *nodes[N];
a3 scan[N * 2];
int tmp[N * 2];

void solve() {
    int n, s, m;
    int s0;
    cin >> n >> s >> m;
    s0 = s;
    nodes[0] = make_tree(s, 0);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> c >> a >> b;
        // assert(c <= s && c >= 1);
        scan[i * 2] = a3{a + 1, -1, c - 1};
        scan[i * 2 + 1] = a3{b, 1, c - 1};
    }
    sort(scan, scan + m * 2);
    int it = 0;
    // if (n >= 500) {
    //     while (true)
    //         {}
    // }
    // if (n >= 500) {
    //     while (true)
    //         {}
    // }
    for (int i = 1; i <= n; ++i) {
        nodes[i] = nodes[i - 1];
        while (it < 2 * m && get<0>(scan[it]) == i) {
            int tp = get<1>(scan[it]);
            int c = get<2>(scan[it]);
            // while (c < 0)
            //     {}
            while (c >= s0)
                {}
            it++;
            tp = -tp;
            tmp[c] += tp;
            if (tmp[c] == 0 && tp < 0) {
                nodes[i] = upd(nodes[i], s, c, i);   
            } else if (tmp[c] == 1 && tp > 0) {
                nodes[i] = upd(nodes[i], s, c, INT_MAX);
            }
        }
    }


    int q;
    cin >> q;
    int p = 0;


    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        a = a + p;
        b = b + p;
        while (a > b)
            {}
        while (a < 1)
            {}
        while (b < 1)
            {}
        while (a > n)
            {}
        while (b > n)
            {}
        int res = query(nodes[b], s, a);
        cout << max(0LL, 1 + res) << '\n';
        p = max(0LL, 1 + res);
    }
}

signed main() {
    // freopen("in", "r", stdin);
    solve();
    return 0;
}
