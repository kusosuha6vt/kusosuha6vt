#include <bits/stdc++.h>

using namespace std;

typedef array<int, 2> a2;
const int N = 3e5;
vector<a2> g[N];
bool used[N];
int s[N];

void sizes(int v, int p) {
	s[v] = 1;
	for (auto u : g[v]) {
		if (u[0] == p || used[u[0]])
			continue;
		sizes(u[0], v);
		s[v] += s[u[0]];
	}
}

int centroid(int v, int p, int n) {
	for (auto u : g[v]) {
		if (used[u[0]] || u[0] == p)
			continue;
		if (s[u[0]] > (n >> 1))
			return centroid(u[0], v, n);
	}
	return v;
}

// sum(w)

const int LOG = 19;
int hd[N];  // head in f-tree
int sz[N];  // size in subtree
int lg[N];  // level of centroid
int pos[LOG][N];  // index of vertex in h-level centroid
int t[LOG][N];  // f-tree
int y[LOG];  // current head of tree
int p[N];  // parent of centroid
a2 dist[LOG][N];  // {distance, vertex} of subtree

void dfs0(int v, int p, int d, int c) {
	dist[lg[c]][hd[c] + (sz[c]++)] = {d, v};
	for (auto u : g[v]) {
		if (used[u[0]] || p == u[0])
			continue;
		dfs0(u[0], v, d + u[1], c);
	}
}

void solve(int v, int h = 0) {
	lg[v] = h;
	hd[v] = y[h];
	sz[v] = 0;
	dfs0(v, -1, 0, v);
	sort(dist[h] + hd[v], dist[h] + hd[v] + sz[v]);
	for (int i = 0; i < sz[v]; ++i) {
		pos[h][dist[h][hd[v] + i][1]] = i;
	}
	y[h] += sz[v];

	sizes(v, -1);
	used[v] = 1;
	for (auto u : g[v]) {
		if (used[u[0]])
			continue;
		int c = centroid(u[0], -1, s[u[0]]);
		p[c] = v;
		solve(c, h + 1);
	}
}

void upd(int v, int val) {
	for (int c = v; c != -1; c = p[c]) {
		int i = pos[lg[c]][v];
		for (; i < sz[c]; i |= (i + 1)) {
			t[lg[c]][hd[c] + i] += val;
		}
	}
	// cout << "upd ok\n";
}

int find_first_1(int *a, int n) {
	// cout << "find_first: sz=" << n << ", ";
	// for (int i = 0; i < n; ++i)
	// 	cout << a[i];
	// cout << '\n';
	int k = 0;
	a--;
	for (int h = 20; h >= 0; --h) {
		if (k + (1 << h) <= n && a[k + (1 << h)] == 0) {
			k += (1 << h);
		}
	}
	return k;
}

int query(int v) {
	int ans = INT_MAX;
	for (int c = v; c != -1; c = p[c]) {
		int dv = dist[lg[c]][hd[c] + pos[lg[c]][v]][0];
		int id = find_first_1(t[lg[c]] + hd[c], sz[c]);
		// cout << "find_first of " << c << " = " << id << '\n';
		if (id < sz[c]) {
			ans = min(ans, dv + dist[lg[c]][hd[c] + id][0]);
		}
	}
	return (ans == INT_MAX ? -1 : ans);
}

int main() {
	int n;
	cin >> n;
	memset(p, -1, sizeof(int) * n);
	for (int i = 1; i < n; ++i) {
		int a, b, l;
		cin >> a >> b >> l;
		--a;
		--b;
		g[a].push_back({b, l});
		g[b].push_back({a, l});
	}

	sizes(0, -1);
	solve(centroid(0, -1, s[0]));
	upd(0, 1);
	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		char tp;
		cin >> tp;
		if (tp == '?') {
			int v;
			cin >> v;
			--v;
			cout << query(v) << '\n';
		} else if (tp == '+') {
			int v;
			cin >> v;
			--v;
			upd(v, 1);
		} else {
			int v;
			cin >> v;
			--v;
			upd(v, -1);
		}
	}
	return 0;
}
