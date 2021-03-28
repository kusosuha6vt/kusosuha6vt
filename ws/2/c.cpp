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

void add_oriented_edge(int v, int u, ll c) {
	e[m] = Edge{u, c, 0LL, h[v]};
	h[v] = m++;

	e[m] = Edge{v, 0, 0LL, h[u]};
	h[u] = m++;
}

void add_unoriented_edge(int v, int u, ll c) {
	e[m] = Edge{u, c, 0LL, h[v]};
	h[v] = m++;

	e[m] = Edge{v, c, 0LL, h[u]};
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

bool u[V];
void get_used(int v, vector<int> &ans) {
	u[v] = 1;
	ans.push_back(v);
	for (int i = h[v]; i != -1; i = e[i].nxt) {
		if (e[i].c - e[i].f && !u[e[i].v]) {
			get_used(e[i].v, ans);
		}
	}
}

// namespace Flow
}; // namespace Flow
// namespace Flow

int main() {
	int n;
	cin >> n;
	Flow::S = 0;
	Flow::init();
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		for (int j = i + 1; j < n; ++j) {
			if (s[j] - '0') {
				Flow::add_unoriented_edge(i, j, ll(1));
			}
		}
	}
	pair<ll, int> ans;
	ans.first = LLONG_MAX;
	for (int t = 1; t < n; ++t) {
		Flow::T = t;
		ll g = Flow::scale();
		ans = min(ans, pair<ll, int>{g, t});
		for (int j = 0; j < Flow::m; ++j) {
			Flow::e[j].f = 0;
		}
	}
	vector<int> cur;
	Flow::T = ans.second;
	Flow::scale();
	Flow::get_used(0, cur);
	for (int u : cur) {
		cout << (u + 1) << ' ';
	}
	cout << '\n';
	for (int i = 0; i < n; ++i) {
		if (count(cur.begin(), cur.end(), i) == 0) {
			cout << (i + 1) << ' ';
		}
	}
}