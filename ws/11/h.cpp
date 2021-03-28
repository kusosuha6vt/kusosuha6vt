#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int n, m, g;
ll ppow(int a, int p) {
	if (p == 0) {
		return 1;
	}
	ll res = ppow(a, p / 2);
	res = res * res % m;
	if (p % 2) {
		res = res * a % m;
	}
	return res;
}

int main() {
	cin >> n >> m >> g;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	if (n <= 1000) {
		ll res = 1;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (j == i)
					continue;
				res = res * ppow(g, a[i]);
			}
			cout << res << ' ';
		}
		return 0;
	}
	return 0;
}