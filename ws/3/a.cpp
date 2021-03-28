#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Edge {
    int v, u;
    ll f;
    ll c;
    ll s;
    int nxt;
    Edge(int v = 0, int u = 0, ll f = 0, ll c = 0, ll s = 0, int nxt = -1) : v(v), u(u), f(f), c(c), s(s), nxt(nxt) {}
};
const int V = 1000, E = 2 * 10000;
int S = V - 1;
int T = V - 2;
int n_;

Edge ed[E];
int sz_ed;
int h[V];

void init() {
    sz_ed = 0;
    memset(h, -1, sizeof(h));
}

void add_oriented_edge(int a, int b, ll c, ll s) {
    ed[sz_ed] = Edge(a, b, 0, c, s, h[a]);
    h[a] = sz_ed++;
    ed[sz_ed] = Edge(b, a, 0, 0, -s, h[b]);
    h[b] = sz_ed++;
}

void add_unoriented_edge(int a, int b, ll c, ll s) {
    ed[sz_ed] = Edge(a, b, 0, c, s, h[a]);
    h[a] = sz_ed++;
    ed[sz_ed] = Edge(b, a, 0, c, -s, h[b]);
    h[b] = sz_ed++;
}


int tp_q[V];  // 0 <=> not in queue, 1 <=> in q, 2 <=> good
int dq[V * 3], fb_p[V];
ll d[V];
int pop_front(int &l, int &r) {
    int res = dq[l++];
    if (l > V * 3) {
        l = 0;
    }
    return res;
}

void push_front(int &l, int &r, int val) {
    dq[--l] = val;
    if (l == -1) {
        l = V * 3 - 1;
    }
}

void push_back(int &l, int &r, int val) {
    dq[r++] = val;
    if (r == V * 3) {
        r = 0;
    }
}

bool fb_cool() {
    fill(d, d + V, LLONG_MAX);
    fill(fb_p, fb_p + V, -1);
    fill(tp_q, tp_q + V, 0);
    int l = V, r = V;
    push_back(l, r, S);
    d[S] = 0;
    fb_p[S] = S;
    while (l < r) {
        int v = pop_front(l, r);
        tp_q[v] = 2;
        for (int i = h[v]; i != -1; i = ed[i].nxt) {
            Edge &e = ed[i];
            if (e.c - e.f > 0 && d[e.u] > d[v] + e.s) {
                d[e.u] = d[v] + e.s;
                fb_p[e.u] = i;
                if (tp_q[e.u] == 0) {
                    push_back(l, r, e.u);
                } else if (tp_q[e.u] == 2) {
                    push_front(l, r, e.u);
                }
                tp_q[e.u] = 1;
            }
        }
    }
    return fb_p[T] != -1;
}

ll max_flow() {
    while (fb_cool()) {
        int v = T;
        ll val = LLONG_MAX;
        while (v != S) {
            Edge &e = ed[fb_p[v]];
            val = min(val, e.c - e.f);
            v = e.v;
        }
        v = T;
        while (v != S) {
            Edge &e = ed[fb_p[v]], &er = ed[fb_p[v] ^ 1];
            e.f += val;
            er.f -= val;
            v = e.v;
        }
    }
    ll ans = 0;
    for (int i = 0; i < sz_ed; i += 2) {
        ans += ed[i].f * ed[i].s;
    }
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    S = 0;
    n_ = n;
    T = n - 1;
    init();
    for (int i = 0; i < m; ++i) {
        int a, b;
        ll c, s;
        cin >> a >> b >> c >> s;
        --a;
        --b;
        add_oriented_edge(a, b, c, s);
    }
    cout << max_flow();
    return 0;
}
