#include <bits/stdc++.h>

using namespace std;

const int LOG = 17;
const int N = 1 << LOG;
vector<int> g[N];
int s[N];
int cp[N];
bool used[N];

void sizes(int v, int p) {
	s[v] = 1;
	for (int &u : g[v]) {
		if (u == p || used[u])
			continue;
		sizes(u, v);
		s[v] += s[u];
	}
}

int centroid(int v, int p, int n) {
	for (int u : g[v]) {
		if (u == p)
			continue;
		if (!used[u] && s[u] > n / 2) {
			return centroid(u, v, n);
		}
	}
	return v;
}

int q[N];
int nxt[N];
int c[N];
int h[N];
int ans[N];
int dist_color[N];

void dfs0(int v, int p, int d) {
	dist_color[c[v]] = min(dist_color[c[v]], d);
	for (int u : g[v]) {
		if (used[u] || p == u)
			continue;
		dfs0(u, v, d + 1);
	}
}

void dfs1(int v, int p) {
	dist_color[c[v]] = INT_MAX;
	for (int u : g[v]) {
		if (used[u] || p == u) {
			continue;
		}
		dfs1(u, v);
	}
}

void query_update(int v, int p, int d) {
	for (int i = h[v]; i != -1; i = nxt[i]) {
		if (dist_color[q[i]] < INT_MAX)
			ans[i] = min(ans[i], d + dist_color[q[i]]);
	}
	for (int u : g[v]) {
		if (used[u] || p == u) {
			continue;
		}
		query_update(u, v, d + 1);
	}
}

void solve(int v) {
	dfs0(v, -1, 0);
	query_update(v, -1, 0);
	dfs1(v, -1);
	used[v] = 1;
	for (int u : g[v]) {
		if (used[u])
			continue;
		sizes(u, -1);
		int c = centroid(u, -1, s[u]);
		cp[c] = v;
		// dfs0(u, -1, 1);
		// query_update(u, -1, 1);
		// dfs1(u, -1);
		solve(c);
	}
}

int main() {
	// freopen("in", "r", stdin);
	fill(dist_color, dist_color + N, INT_MAX);
	memset(h, -1, sizeof(h));
	fill(ans, ans + N, INT_MAX);
	int n;
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int p;
		cin >> p;
		g[p].push_back(i);
		g[i].push_back(p);
	}
	for (int i = 0; i < n; ++i) {
		cin >> c[i];
	}
	// cout << "Ok";
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		int v;
		cin >> v >> q[i];
		nxt[i] = h[v];
		h[v] = i;
	}
	// cout << "Ok";

	sizes(0, -1);
	int c = centroid(0, -1, s[0]);
	cp[c] = -1;
	solve(c);
	for (int i = 0; i < m; ++i) {
		cout << (ans[i] == INT_MAX ? -1 : ans[i]) << ' ';
	}
	// cout << endl;
	return 0;
}
