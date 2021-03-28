#include <bits/stdc++.h>

using namespace std;

const int LOG = 19;
const int N = 1 << LOG;
vector<int> g[N];
int s[N], anc[N], tin[N], tout[N], tcur;
int d[N];
int cp[N];
bool used[N];

void sizes(int v, int p) {
	anc[v] = p;
	s[v] = 1;
	for (int &u : g[v]) {
		if (u == p && !used[u])
			continue;
		d[u] = d[v] + 1;
		sizes(u, v);
		s[v] += s[u];
	}
}

bool is_parent(int p, int v) {
	return tin[p] <= tin[v] && tout[v] <= tout[p];
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

void solve(int v) {
	used[v] = 1;
	for (int u : g[v]) {
		if (used[u])
			continue;
		sizes(u, -1);
		int c = centroid(u, -1, s[u]);
		cp[c] = v;
	}
}

int main() {
	// freopen("in", "r", stdin);
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		cin >> a >> b;
		--a;
		--b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	sizes(0, 0);
	cout << "Ok";
	int c = centroid(0, -1, s[0]);
	cout << "Ok";
	cp[c] = -1;
	solve(c);
	cout << "OK";
	for (int i = 0; i < n; ++i) {
		cout << cp[i] + 1 << ' ';
	}
	return 0;
}
