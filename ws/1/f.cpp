#include <bits/stdc++.h>

using namespace std;

typedef long double ld;
typedef array<int, 2> a2;
typedef long long ll;
const int N = 2e5;
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

const int LOG = 18;
ll sum_w[N];
int w[N];
int anc[N];

void dfs0(int v, int p) {
	sum_w[v] = w[v];
	for (auto u : g[v]) {
		if (p == u[0])
			continue;
		if (used[u[0]]) {
			sum_w[v] += sum_w[u[0]];
		} else {
			dfs0(u[0], v);
			sum_w[v] += sum_w[u[0]];
		}
	}
}

ld calc_ans(int v, int p, ll d) {
	ld ans = w[v] * d * sqrt((ld)d);
	for (auto u : g[v]) {
		if (u[0] == p) {
			continue;
		}
		ans += calc_ans(u[0], v, d + u[1]);
	}
	return ans;
}

ld gg[N];
void dfs_choose(int v, int p, ll d) {
	gg[v] = w[v] * sqrt(d);
	for (auto u : g[v]) {
		if (u[0] != p) {
			dfs_choose(u[0], v, d + u[1]);
			gg[v] += gg[u[0]];
		}
	}
}

pair<ld, int> ans = {numeric_limits<ld>::infinity(), -1};

void solve(int v) {
	ans = min(ans, make_pair(calc_ans(v, -1, 0), v));
	dfs0(v, -1);
	sizes(v, -1);
	used[v] = 1;
	pair<ld, int> mx_sz = {-1L, -1};
	dfs_choose(v, -1, 0);
	for (auto u : g[v]) {
		if (used[u[0]])
			continue;
		mx_sz = max(mx_sz, pair<ld, int>{gg[u[0]], u[0]});
	}
	int u = mx_sz.second;
	if (u >= 0) {
		int c = centroid(u, -1, s[u]);
		anc[c] = v;
		solve(c);
	}
}

mt19937 gen(229);

int main() {
	int n;
	cin >> n;
	fill(anc, anc + n, -1);
	for (int i = 0; i < n; ++i) {
		cin >> w[i];
	}
	for (int i = 1; i < n; ++i) {
		int a, b, l;
		cin >> a >> b >> l;
		--a;
		--b;
		g[a].push_back({b, l});
		g[b].push_back({a, l});
	}
	for (int i = 0; i < n; ++i) {
		shuffle(g[i].begin(), g[i].end(), gen);
	}

	sizes(0, -1);
	solve(centroid(0, -1, s[0]));
	cout << ans.second + 1 << ' ' << fixed << setprecision(20) << ans.first;

	return 0;
}
