#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
namespace Flow {
const int V = int(5e5);
const int E = int(5e5);
int S = V - 1;
int T = V - 2;
const int LOG = 30;
struct Edge {
	int v;
	ll c, f;
	int nxt = -1;
	Edge() {}
	Edge(int e1, ll e2, ll e3, int e4 = -1) {
		v = e1;
		c = e2;
		f = e3;
		nxt = e4;
	}
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
	e[m] = Edge(u, c, 0LL, h[v]);
	h[v] = m++;

	e[m] = Edge(v, 0, 0LL, h[u]);
	h[u] = m++;
}

void add_unoriented_edge(int v, int u, ll c) {
	e[m] = Edge(u, c, 0LL, h[v]);
	h[v] = m++;

	e[m] = Edge(v, c, 0LL, h[u]);
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

char u[V];
void get_used(int v, vector<int> &ans) {
	u[v] = 1;
	ans.push_back(v);
	for (int i = h[v]; i != -1; i = e[i].nxt) {
		if (e[i].c - e[i].f && !u[e[i].v]) {
			get_used(e[i].v, ans);
		}
	}
}

bool decompose_1(int v, vector<int> &ans) {
	if (v == T) {
		ans.push_back(v);
		return 1;
	}
	u[v] = 1;
	for (int i = h[v]; i != -1; i = e[i].nxt) {
		if (e[i].f > 0 && !u[e[i].v] && decompose_1(e[i].v, ans)) {
			ans.push_back(v);
			e[i].f -= 1;
			e[i ^ 1].f += 1;
			return 1;
		}
	}
	return 0;
}

// namespace Flow
}; // namespace Flow
// namespace Flow

char f[51][51];

int n, m;
bool ok(int i, int j) {
	return i >= 0 && j >= 0 && i < n && j < m && f[i][j] != '.';
}

int main() {
	cin >> n >> m;
	Flow::init();
	// 0->1, 2->3, .. 2n-2->2n-1

	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		strcpy(f[i], s.c_str());
	}
	ll sum = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			int v = i * m + j;
			string g = ".HONC";
			int val = g.find(f[i][j]);
			sum += val;
			if (val) {
				if ((i + j) & 1) {
					Flow::add_oriented_edge(Flow::S, v, val);
				} else {
					Flow::add_oriented_edge(v, Flow::T, val);
				}
				if ((i + j) & 1) {
					if (ok(i - 1, j)) {
						Flow::add_oriented_edge(v, (i - 1) * m + (j), 1);
					}
					if (ok(i + 1, j)) {
						Flow::add_oriented_edge(v, (i + 1) * m + (j), 1);
					}
					if (ok(i, j - 1)) {
						Flow::add_oriented_edge(v, (i) * m + (j - 1), 1);
					}
					if (ok(i, j + 1)) {
						Flow::add_oriented_edge(v, (i) * m + (j + 1), 1);
					}
				}
			}
		}
	}
	ll g = Flow::scale();
	// cout << g << ' ' << sum << '\n';
	if (g > 0 && g * 2 == sum) {
		cout << "Valid";
	} else {
		cout << "Invalid";
	}
}
