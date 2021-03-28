#include <bits/stdc++.h>

using namespace std;

const int N = 5e5;
map<char, int> to[N];
bool ct[N];
int sz = 1;
int lk[N];

int add_string(const string &s) {
	int v = 0;
	for (char c : s) {
		if (to[v].count(c) == 0) {
			to[v][c] = sz++;
			while (sz >= N)
				{}
		}
		v = to[v][c];
	}
	ct[v] = 1;
	return v;
}

int q[N];
void bfs() {
	int l = 0, r = 1;
	lk[0] = -1;
	while (r - l) {
		int v = q[l++];
		for (auto cu : to[v]) {
			int u = cu.second;
			char c = cu.first;
			int j = lk[v];
			while (j != -1 && to[j].count(c) == 0) {
				j = lk[j];
			}
			if (j >= 0) {
				lk[u] = to[j][c];
			}
			if (ct[lk[u]]) {
				ct[u] = 1;
			}
			q[r++] = u;
		}
	}
}

int go(int v, char c) {
	while (v != 0 && to[v].count(c) == 0) {
		v = lk[v];
	}
	if (to[v].count(c)) {
		v = to[v][c];
	}
	return v;
}

int main() {
	int n;
	cin >> n;
	cin.get();
	for (int i = 0; i < n; ++i) {
		string s;
		getline(cin, s);
		if (!s.empty() && s.back() == '\n') {
			s.pop_back();
		}
		// cout << "\"" << s << "\"\n";
		// cout << "\"" << s << "\"" << endl;
		// cin.get();
		add_string(s);
	}
	// cout << "Ok";
	bfs();
	// cout << "Ok";
	string s;
	while (getline(cin, s)) {
		if (!s.empty() && s.back() == '\n') {
			s.pop_back();
		}
		int v = 0;
		bool ok = 0;
		for (char c : s) {
			v = go(v, c);
			if (ct[v]) {
				ok = 1;
				break;
			}
		}
		if (ok) {
			cout << s << '\n';
		}
	}
	return 0;
}
