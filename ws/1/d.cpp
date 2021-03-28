#include <bits/stdc++.h>

using namespace std;

const int N = 2e5;
vector<int> g[N];
int tin[N], tout[N], tcur;
bool used[N];
int s[N];
// int dc[N];
// void add(int i, int v) {
// 	for (; i < N; i |= (i + 1)) {
// 		dc[i] += v;
// 	}
// }

// int get(int i) {
// 	int ans = 0;
// 	for (; i >= 0; i = (i & (i + 1)) - 1) {
// 		ans += dc[i];
// 	}
// 	return ans;
// }

// int get(int l, int r) {
// 	return get(r - 1) - get(l - 1);
// }

void sizes(int v, int p) {
	s[v] = 1;
	for (int u : g[v]) {
		if (u == p || used[u])
			continue;
		sizes(u, v);
		s[v] += s[u];
	}
}

int centroid(int v, int p, int n) {
	for (int u : g[v]) {
		if (used[u] || u == p)
			continue;
		if (s[u] > (n >> 1))
			return centroid(u, v, n);
	}
	return v;
}

int ans[N];
typedef array<int, 2> a2;
a2 sv[N];
int it;

void dfs0(int v, int p, int d) {
	sv[it++] = {v, d};
	for (int u : g[v]) {
		if (used[u] || p == u)
			continue;
		dfs0(u, v, d + 1);
	}
}

void solve(int v) {
	it = 0;
	dfs0(v, -1, 0);
	sort(sv, sv + it);
	int cur_mn = sv[it - 1][1];
	for (int i = it - 2; i >= 0; --i) {
		ans[sv[i][0]] = min(ans[sv[i][0]], sv[i][1] + cur_mn);
		cur_mn = min(cur_mn, sv[i][1]);
	}
	
	sizes(v, -1);
	used[v] = 1;
	for (int u : g[v]) {
		if (used[u])
			continue;
		int c = centroid(u, -1, s[u]);
		solve(c);
	}
}

int main() {
	int n;
	cin >> n;
	fill(ans, ans + n, INT_MAX);
	for (int i = 1; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		--a;
		--b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	sizes(0, -1);
	solve(centroid(0, -1, s[0]));
	for (int i = 0; i < n - 1; ++i) {
		cout << ans[i] << '\n';
	}
	return 0;
}
