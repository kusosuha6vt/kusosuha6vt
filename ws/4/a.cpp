#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>

using namespace std;
// using __gnu_pbds;

const int N = 3e5 + 10;
// gp_hash_table<int, int> to;
map<char, int> to[N];
// random_device rd;
// const size_t RANDOM = uniform_int_distribution<size_t>(0, INT_MAX)(rd);
int sz = 1;
int term[N];

int add_string(const string &s) {
	int v = 0;
	for (char c : s) {
		if (to[v].count(c) == 0) {
			to[v][c] = sz++;
		}
		v = to[v][c];
		term[v]++;
	}
	return v;
}

void get_kth(int v, int k) {
	for (auto cu : to[v]) {
		char c = cu.first;
		int u = cu.second;
		if (k >= term[u]) {
			k -= term[u];
		} else {
			if (c != 0)
				cout << c;
			get_kth(u, k);
			return;
		}
	}
}

int main() {
	int n;
	cin >> n;
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		s.push_back(0);
		if (s[0] <= '9' && s[0] >= '0') {
			get_kth(0, stoi(s) - 1);
			cout << endl;
		} else {
			add_string(s);
		}
		// cout << to[ic(0, 'p')];
	}
	return 0;
}
