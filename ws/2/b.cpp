#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
namespace Flow {
const int V = 1000;
const int E = 20000;
int S = V - 1;
int T = V - 2;
const int LOG = 30;
struct Edge {
	int v;
	ll c, f;
	int nxt = -1;
};
Edge e[E];
int d[V], q[V];
int h[V];
int m;

void init() {
	m = 0;
	memset(h, -1, sizeof(h));
}

void add_edge(int v, int u, ll c) {
	e[m] = Edge{u, c, 0LL, h[v]};
	h[v] = m++;

	e[m] = Edge{v, 0, 0LL, h[u]};
	h[u] = m++;
}

bool bfs(ll x) {
	memset(d, -1, sizeof(d));
	int l = 0, r = 1;
	d[S] = 0;
	q[0] = S;
	while (l < r) {
		int v = q[l++];
		for (int i = h[v]; i != -1; i = e[i].nxt) {
			Edge &c = e[i];
			if (c.c - c.f >= x && d[c.v] == -1) {
				d[c.v] = d[v] + 1;
				q[r++] = c.v;
			}
		}
	}
	return d[T] != -1;
}

int p[V];
ll dfs(int v, ll val, ll sc) {
	if (v == T) {
		return val;
	}
	for (; p[v] != -1; p[v] = e[p[v]].nxt) {
		Edge &c = e[p[v]];
		if (c.c - c.f >= sc && d[c.v] > d[v]) {
			ll x = dfs(c.v, min(val, c.c - c.f), sc);
			if (x) {
				c.f += x;
				e[p[v] ^ 1].f -= x;
				return x;
			}
		}
	}
	return 0;
}

ll step(ll sc) {
	memcpy(p, h, sizeof(p));
	ll ans = 0;
	if (bfs(sc)) {
		for (ll x; (x = dfs(S, LLONG_MAX, sc)); ans += x)
			{}
	}
	return ans;
}

ll dinic() {
	ll ans = 0;
	for (ll x; (x = step(1)); ans += x)
		{}
	return ans;
}

ll scale() {
	ll ans = 0;
	for (int h = LOG; h >= 0; --h) {
		for (ll x; (x = step(1ull << h)); ans += x)
			{}
	}
	return ans;
}
// namespace Flow
}; // namespace Flow
// namespace Flow


int main() {
	int n, m;
	cin >> n >> m;
	Flow::S = 0;
	Flow::T = n - 1;
	Flow::init();
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		--a; --b;
		Flow::add_edge(a, b, c);
	}
	cout << Flow::scale() << '\n';
	for (int i = 0; i < m; ++i) {
		cout << Flow::e[i << 1].f << '\n';
	}
}
