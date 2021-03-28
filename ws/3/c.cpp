#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Edge {
    int v, u;
    ll f;
    ll c;
    ll s;
    ll real_s;
    int nxt;
    Edge(int v = 0, int u = 0, ll f = 0, ll c = 0, ll s = 0, int nxt = -1) : v(v), u(u), f(f), c(c), s(s), real_s(s), nxt(nxt) {}
};
const int V = 10000 + 50;
const int E = 100000;
int S = V - 1;
int T = V - 2;

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

void apply_potentials() {
    for (int i = 0; i < sz_ed; ++i) {
        if (d[ed[i].v] < LLONG_MAX && d[ed[i].u] < LLONG_MAX)
            ed[i].s = ed[i].s + d[ed[i].v] - d[ed[i].u];
    }
}

void push_flow(ll &ans) {
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
        ans += val * e.real_s;
        v = e.v;
    }
}

bool dijkstra() {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push(pair<ll, int>{0LL, S});
    fill(d, d + V, LLONG_MAX);
    d[S] = 0;
    while (!pq.empty()) {
        // cout << 1;
        int v = pq.top().second;
        ll cur_d = pq.top().first;
        pq.pop();
        if (cur_d > d[v]) {
            continue;
        }
        for (int i = h[v]; i != -1; i = ed[i].nxt) {
            Edge &e = ed[i];
            if (e.c - e.f > 0 && d[e.u] > d[e.v] + e.s) {
                d[e.u] = d[v] + e.s;
                fb_p[e.u] = i;
                pq.push(pair<ll, int>{d[e.u], e.u});
            }
        }
    }
    return d[T] < LLONG_MAX;
}

ll max_flow() {
    ll ans = 0;
    if (!fb_cool()) {
        return ans;
    }
    apply_potentials();
    while (dijkstra()) {
    // while (fb_cool()) {
        push_flow(ans);
        apply_potentials();
    }
    return ans;
}
typedef array<int, 3> a3;
const int N = 1000;
a3 stc[N];
int vals[N * 2];

int main() {
    // freopen("in", "r", stdin);
    init();
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        int s;
        cin >> s;
        stc[i] = {a, a + b, s};
        vals[i << 1] = a;
        vals[i << 1 | 1] = a + b;
    }
    sort(vals, vals + 2 * n);
    int vs = unique(vals, vals + 2 * n) - vals;
    for (int i = 0; i < n; ++i) {
        int a = lower_bound(vals, vals + vs, stc[i][0]) - vals;
        int b = lower_bound(vals, vals + vs, stc[i][1]) - vals;
        add_oriented_edge(a, b, 1, -stc[i][2]);
    }
    add_oriented_edge(S, 0, k, 0);
    add_oriented_edge(vs - 1, T, k, 0);
    for (int i = 0; i < vs - 1; ++i) {
        add_oriented_edge(i, i + 1, k, 0);
    }
    max_flow();
    for (int i = 0; i < n; ++i) {
        assert(ed[i << 1].f >= 0 && ed[i << 1].f <= 1);
        cout << ed[i << 1].f << ' ';
    }
    return 0;
}
